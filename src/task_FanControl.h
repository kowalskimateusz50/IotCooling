#pragma once 

#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"
#include "hardwaretimer.h"

#define FAN_PIN 20
#define WRAP_BASE 16384
#define FAN_SPEED 20

void task_FanControl(void *);

void CountPulsesInSec();

void SpeedConntrol();