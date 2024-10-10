#pragma once 

#include "hardware/gpio.h"
#include "pico/time.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/timer.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include "FreeRTOS.h"
#include "task.h"
#include "GlobalWebServerData.h"
#include "settings.h"
#include "taskshared.h"

#define FAN_PIN_OUT 20
#define FAN_PIN_IN 21
#define WRAP_BASE 16384
#define FAN_SPEED 60
#define Rising_Edge 1
#define Falling_Edge 2

void task_FanControl(void *);
bool EdgeDetection(bool iGPIO, int iEdgeConfig);
void SpeedConntrol();
static void hardware_gpio_timer_handler(void);
void timer_gpio_initialize(uint32_t delay_us);