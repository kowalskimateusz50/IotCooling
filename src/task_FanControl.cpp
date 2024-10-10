#include "task_FanControl.h"

#define TIMER_NUM 1

uint SecondCounter = 0;
uint PulseCounter = 0;
uint gFanSpeedRpm = 0;

static void hardware_gpio_timer_handler(void) {
    // Clear the alarm irq
    hw_clear_bits(&timer_hw->intr, 1u << TIMER_NUM);

        if(SecondCounter < 200) {
            if (EdgeDetection(gpio_get(FAN_PIN_IN), Falling_Edge)) {
                PulseCounter++;
            }
            SecondCounter++;
        }

    timer_gpio_initialize(5000);

}

void timer_gpio_initialize(uint32_t delay_us) {

    // Enable the interrupt for our alarm (the timer outputs 4 alarm irqs)
    hw_set_bits(&timer_hw->inte, 1u << TIMER_NUM);
    // Set irq handler for alarm irq
    irq_set_exclusive_handler(TIMER_IRQ_1, hardware_gpio_timer_handler);
    // Enable the alarm irq
    irq_set_enabled(TIMER_IRQ_1, true);
    // Enable interrupt in block and at processor

    // Alarm is only 32 bits so if trying to delay more
    // than that need to be careful and keep track of the upper
    // bits
    uint64_t target = timer_hw->timerawl + delay_us;

    // Write the lower 32 bits of the target time to the alarm which
    // will arm it
    timer_hw->alarm[TIMER_NUM] = (uint32_t) target;
}

void task_FanControl(void *){

    // Initialize pin
   gpio_set_function(FAN_PIN_OUT , GPIO_FUNC_PWM);
  
   // Wyznacz slice i kanał
   uint slice = pwm_gpio_to_slice_num(FAN_PIN_OUT);
   uint channel = pwm_gpio_to_channel(FAN_PIN_OUT);

   pwm_set_wrap(slice, WRAP_BASE); 

   //Calculate fan speed in %
   uint FanSpeedPercent  = 60;
   uint RequestedFanSpeed = 0;


   pwm_set_chan_level(slice, channel, FanSpeedPercent); 

   pwm_set_enabled(slice, true); // Activate PWM

   printf("\nFan is running with speed: %d %", FAN_SPEED);

   //Set Fan speed control pin
   gpio_set_dir(FAN_PIN_IN, GPIO_IN);

   const TickType_t xDelay_5ms = 5 / portTICK_PERIOD_MS;

   timer_gpio_initialize(5000);



    while(true){

        if(SecondCounter >= 200) {
            #ifdef debug
                //Display value on webserver 
                printf("\nCounted revolutions in rpm: %d", PulseCounter*30);
            #endif

            gFanSpeedRpm= PulseCounter*30;

            //Reset pulse counter
            PulseCounter=0;
            //Reset second counter
            SecondCounter=0;
        }

        //Control FAN PWM
        if (xQueueReceive(QRequestedFanSpeed,&RequestedFanSpeed, 0U) == pdPASS) {
            FanSpeedPercent = (RequestedFanSpeed * (WRAP_BASE/ 100));
            pwm_set_chan_level(slice, channel, FanSpeedPercent); 
            printf("\nNew requested fan speed:  %d", RequestedFanSpeed);
        }
    }

}

void CountPulsesInSec(){
    printf("\nFan speed monitoring 1 second elapsed: ");
}

void SpeedConntrol() {
    
}

bool EdgeDetection(bool iGPIO, int iEdgeConfig) {

    static bool LastCycleState = false;

    if (iEdgeConfig == 1) {
        if (iGPIO && !LastCycleState) {
                LastCycleState = iGPIO;
                return true;
        }
    }
    else if (iEdgeConfig == 2) {
        if (!iGPIO && LastCycleState) {
            LastCycleState = iGPIO;
            return true;
        }
    }

    LastCycleState = iGPIO;
    return false; 

}