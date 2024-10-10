#include "task_ReadTemperature.h"

//Declare global value
float gTemperature = 0;

void task_ReadTemperature(void *) {

    stdio_init_all();
    printf("\nPeripherals initialized: "); 

    One_wire one_wire(22); //GP22 - Pin 29 on Pi Pico
    one_wire.init();
    rom_address_t address{};

    /* Block for 1000ms. */
    const TickType_t xDelay = 3000 / portTICK_PERIOD_MS;

    #ifdef debug
        //Display value on webserver 
        printf("\nProgram is starting reading temperature: ");
    #endif 
    //Temperature data
    float FilteredTemperature = 0;
    uint FanSpeedValue = 60;

    while(1) {
        one_wire.single_device_read_rom(address);
        one_wire.convert_temperature(address, true, false);
        ReadingsFiltration(&FilteredTemperature, one_wire.temperature(address));
        #ifdef debug
            //Display value on webserver 
            printf("Temperature: %3.1foC\n", FilteredTemperature);
        #endif
        gTemperature = FilteredTemperature;

        //Control fan speed 

        if (FanSpeedValue >= 60 && FanSpeedValue < 100) {
            FanSpeedValue += 10;
        }           
        else if (FanSpeedValue == 100) {
            FanSpeedValue = 60;
        }

        xQueueSend(QRequestedFanSpeed,&FanSpeedValue, 0U);

       vTaskDelay(xDelay);
    };
}

void ReadingsFiltration(float* FilteredRead, float RawRead) {

    if(RawRead < 100 && RawRead > -100) {
        *FilteredRead = RawRead;
    }

}