#pragma once

#include "hardware/gpio.h"
#include "FreeRTOS.h"
#include "task.h"

#include <string.h>
#include <stdlib.h>

#include "lwip/apps/httpd.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"


#define TIMER_NUM 0

void timer_us_initialize(uint32_t delay_us);

bool timer_us_elapsed();
