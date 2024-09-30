#include "task_FanControl.h"

void task_FanControl(void *){

    // Initialize pin
   gpio_set_function(FAN_PIN, GPIO_FUNC_PWM);
  
   // Wyznacz slice i kanał
   uint slice = pwm_gpio_to_slice_num(FAN_PIN);
   uint channel = pwm_gpio_to_channel(FAN_PIN);

   pwm_set_wrap(slice, WRAP_BASE); // 1.9kHz * (X)/WRAP_BASE  

   //Calculate fan speed in %
   uint FanSpeedPercent = (FAN_SPEED* (WRAP_BASE/ 100));


   pwm_set_chan_level(slice, channel, FanSpeedPercent); // 50%

   pwm_set_enabled(slice, true); // Aktywuj PWM

   printf("\nFan is running with speed: %d %", FAN_SPEED);

   uint SecondCounter = 0;


    while(true){

        if(SecondCounter < 100) {
            SecondCounter++;
        }
        else {
            //Function for counting revolutions per second
            CountPulsesInSec();
            //Reset second counter
            SecondCounter=0;
        }
        vTaskDelay(10);
    }

}

void CountPulsesInSec(){
    printf("\nFan speed monitoring 1 second elapsed: ");
}

void SpeedConntrol() {
    
}