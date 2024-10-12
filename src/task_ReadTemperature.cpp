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
    const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;

    #ifdef debug
        //Display value on webserver 
        printf("\nProgram is starting reading temperature: ");
    #endif 
    //Temperature data
    float FilteredTemperature = 0;
    uint FanSpeedValue = 0;

    while(1) {
        one_wire.single_device_read_rom(address);
        one_wire.convert_temperature(address, true, false);
        ReadingsFiltration(&FilteredTemperature, one_wire.temperature(address));

        #ifdef debug
            //Display value on webserver 
            //printf("Temperature: %3.1foC\n", FilteredTemperature);
        #endif

        //Send temperature reading to WebServer
        gTemperature = FilteredTemperature;

        //Control fan speed 
        FanSpeedValue = CalculateRequestedFanSpeed(FilteredTemperature);
        xQueueSend(QRequestedFanSpeed,&FanSpeedValue, 0U);



       vTaskDelay(xDelay);
    };
}

void ReadingsFiltration(float* FilteredRead, float RawRead) {

    if(RawRead < 100 && RawRead > -100) {
        *FilteredRead = RawRead;
    }

}

uint CalculateRequestedFanSpeed(float Temperature) {
    //Temperature lower than treshold
    if (Temperature < TEMPERATURE_LOW_RANGE) {
        return 0;
    }
    else if (Temperature >= TEMPERATURE_LOW_RANGE && Temperature <= TEMPERATURE_HIGH_RANGE) {
        uint RetVal = (60 + ((40/(TEMPERATURE_HIGH_RANGE - TEMPERATURE_LOW_RANGE))* (Temperature - TEMPERATURE_LOW_RANGE)));
        printf("\nFan requested speed %d %:", RetVal);
        return RetVal;
    }
    else if (Temperature > TEMPERATURE_HIGH_RANGE) {
        return 100;
    }

    return 0;
}