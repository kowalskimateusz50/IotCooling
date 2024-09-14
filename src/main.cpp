#include "FreeRTOS.h"
#include "task.h"

#include <string.h>
#include <stdlib.h>

#include "lwip/apps/httpd.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwipopts.h"
#include "cgi.h"
#include "ssi.h"

#include "one_wire.h"

//Wifi credentials
char ssid[] = "MatLan";
char pass[] = "janrouter3"; 

const uint32_t timeout = 1000 * 60 * 10;// 10min

void run_server(void *) {
    
    httpd_init();
    ssi_init();
    cgi_init();
    printf("Http server initialized.\n");

    while(true)
    {
    };

}

int main()
 {

    //Initialize standard peripherials
    stdio_init_all();

    //Initialize wifi chip
    if (cyw43_arch_init())
    {
        printf("\ncyw43 failed to initialise");
        return 1;
    }

    cyw43_arch_enable_sta_mode();

    cyw43_wifi_pm(&cyw43_state, cyw43_pm_value(CYW43_NO_POWERSAVE_MODE, 20, 1, 1, 1));

    //Attempt to connect to WiFi network 
    if (cyw43_arch_wifi_connect_timeout_ms(ssid, pass, CYW43_AUTH_WPA2_AES_PSK, timeout))
    {
        printf("\nfailed to connect, resp: ");
        return 1;
    }
    else {
        //print success message 
        printf("Connected success\n");
        extern cyw43_t cyw43_state;
        auto ip_addr = cyw43_state.netif[CYW43_ITF_STA].ip_addr.addr;
        printf("IP Address: %lu.%lu.%lu.%lu\n", ip_addr & 0xFF, (ip_addr >> 8) & 0xFF, (ip_addr >> 16) & 0xFF, ip_addr >> 24);
        // turn on LED to signal connected
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    }


    

    //Thread handling

    //Create web server task
    xTaskCreate(run_server, "run_server", 256, NULL, 1, NULL);

    //Create temperature measurement task

    vTaskStartScheduler();
    
    //One_wire one_wire(22); //GP22 - Pin 29 on Pi Pico
    //one_wire.init();
    //rom_address_t address{};

    printf("\nProgram is starting reading temperature: "); 

    while(1){

        //one_wire.single_device_read_rom(address);
        //printf("Device Address: %02x%02x%02x%02x%02x%02x%02x%02x\n", address.rom[0], address.rom[1], address.rom[2], address.rom[3], address.rom[4], address.rom[5], address.rom[6], address.rom[7]);
        //one_wire.convert_temperature(address, true, false);
        //printf("Temperature: %3.1foC\n", one_wire.temperature(address));
        printf("Temperature: is dummy ");

        
    };
    

}
