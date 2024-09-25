#include "FreeRTOS.h"
#include "task.h"

#include <string.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include <cstdio>
#include "hardware/gpio.h"

#include "task_ReadTemperature.h"
#include "task_WebServer.h"


//Wifi credentials
char ssid[] = "MatLan";
char pass[] = "janrouter3"; 

const uint32_t timeout = 1000 * 60 * 10;// 10min


int main() {

    //Initialize standard peripherials
    stdio_init_all();

    //Initialize wifi chip
    if (cyw43_arch_init()) {
        printf("\ncyw43 failed to initialise");
        return 1;
    }

    cyw43_arch_enable_sta_mode();

    cyw43_wifi_pm(&cyw43_state, cyw43_pm_value(CYW43_NO_POWERSAVE_MODE, 20, 1, 1, 1));

    //Attempt to connect to WiFi network 
    if (cyw43_arch_wifi_connect_timeout_ms(ssid, pass, CYW43_AUTH_WPA2_AES_PSK, timeout)) {
        printf("\nfailed to connect, resp: ");
        return 1;
    }
    else {
        //print success message 
        printf("Connected success\n");
        extern cyw43_t cyw43_state;
        auto ip_addr = cyw43_state.netif[CYW43_ITF_STA].ip_addr.addr;
        printf("IP Address: %lu.%lu.%lu.%lu\n", ip_addr & 0xFF, (gip_addr >> 8) & 0xFF, (ip_addr >> 16) & 0xFF, ip_addr >> 24);
        // turn on LED to signal connected
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    }

    //Create temperature reading task
    xTaskCreate(task_ReadTemperature, "read_temperature", 1024, NULL, 2, NULL);

    //Create web server task
    xTaskCreate(task_WebServer, "run_server", 1024, NULL, 1, NULL);


    vTaskStartScheduler();   

    return 0;
}
