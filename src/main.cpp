#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "one_wire.h"


void led_task(void* dummy)
{   
//Debug message
printf("\nLed task started: ");

    while (true) {

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        vTaskDelay(1000);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        vTaskDelay(1000);
    }
}

int main()
{
    //Initialize cyw_43
    stdio_init_all();
    if (cyw43_arch_init()) {
        printf("\nWi-Fi init failed");
        return -1;
    }

    //Thread handling
    //xTaskCreate(led_task, "LED_Task", 256, NULL, 1, NULL);
    //vTaskStartScheduler();

    One_wire one_wire(22); //GP22 - Pin 29 on Pi Pico
    one_wire.init();
    rom_address_t address{};

    printf("\nProgram is starting reading temperature: "); 

    while(1){

        one_wire.single_device_read_rom(address);
        printf("Device Address: %02x%02x%02x%02x%02x%02x%02x%02x\n", address.rom[0], address.rom[1], address.rom[2], address.rom[3], address.rom[4], address.rom[5], address.rom[6], address.rom[7]);
        one_wire.convert_temperature(address, true, false);
        printf("Temperature: %3.1foC\n", one_wire.temperature(address));
        sleep_ms(1000);
        
    };
}