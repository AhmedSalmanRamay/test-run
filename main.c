
#include <stdio.h>
#include "boards.h"
#include "app_util_platform.h"
#include "app_error.h"
#include "nrf_drv_twi.h"

/* TWI instance ID. */
#if TWI0_ENABLED
#define TWI_INSTANCE_ID     0
#elif TWI1_ENABLED
#define TWI_INSTANCE_ID     1
#endif

 /* Number of possible TWI addresses. */
 #define TWI_ADDRESSES      127

/* TWI instance. */
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);


/**
 * @brief TWI initialization.
 */
ret_code_t twi_init(void)
{
    ret_code_t err_code;

    const nrf_drv_twi_config_t twi_config = {
       .scl                = 22,
       .sda                = 25,
       .frequency          = NRF_DRV_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    err_code = nrf_drv_twi_init(&m_twi, &twi_config, NULL, NULL);
    if (err_code != NRF_SUCCESS) {
        printf("Error initializing TWI. Error code: 0x%x\r\n", err_code);
    }

    return err_code;
}


/**
 * @brief Function for main application entry.
 */
int main(void)
{
    ret_code_t err_code;
    uint8_t address;
    uint8_t sample_data;
    bool detected_device = false;

  

   printf("TWI scanner started loop.\r\n");
    
   // Initialize TWI
    err_code = twi_init();
    if (err_code != NRF_SUCCESS)
    {
        printf("Error initializing TWI. Error code: 0x%x\r\n", err_code);
        return 1;
    }

   for (address = 1; address <= TWI_ADDRESSES; address++)
{
    err_code = nrf_drv_twi_rx(&m_twi, address, &sample_data, sizeof(sample_data));
    if (err_code == NRF_SUCCESS)
    {
        detected_device = true;
        printf("TWI device detected at address 0x%x.\n", address);
    }
    else if (err_code == NRF_ERROR_NOT_FOUND)
    {
        // No device found at this address, continue scanning
    }
    else
    {
        // Some other error occurred, handle it as needed
        printf("Error scanning address 0x%x, error code: 0x%x\n", address, err_code);
    }
}

if (!detected_device)
{
    printf("No device was found.\r\n");
}

    while (true)
    {
        
   printf("TWI scanner started.\r\n");
    
    

    for (address = 1; address <= TWI_ADDRESSES; address++)
    {
        err_code = nrf_drv_twi_rx(&m_twi, address, &sample_data, sizeof(sample_data));
        if (err_code == NRF_SUCCESS)
        {
            detected_device = true;
            printf("TWI device detected at address 0x%x.\n", address);
        }
        if (!detected_device)
    {
        printf("No device was found.\r\n");
        
    }
       
    }

    }
}


