#include "task_ReadTemperature.h"

//Temperature data
float gTemperature = 69;

void task_ReadTemperature(void *) {

    stdio_init_all();
    printf("\nPeripherals initialized: "); 

    One_wire one_wire(22); //GP22 - Pin 29 on Pi Pico
    one_wire.init();
    rom_address_t address{};

    /* Block for 1000ms. */
    const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;

    printf("\nProgram is starting reading temperature: "); 
    float FilteredTemperature = 0;

    while(1) {
        one_wire.single_device_read_rom(address);
        one_wire.convert_temperature(address, true, false);
        ReadingsFiltration(&FilteredTemperature, one_wire.temperature(address));

        printf("Temperature: %3.1foC\n", FilteredTemperature);
        gTemperature = FilteredTemperature;

       vTaskDelay(1000);
    };
}

void ReadingsFiltration(float* FilteredRead, float RawRead) {

    if(RawRead < 100 && RawRead > -100) {
        *FilteredRead = RawRead;
    }

}