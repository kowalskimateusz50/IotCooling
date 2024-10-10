#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

//Request from temperature read task to fan control task for speed in %
extern QueueHandle_t QRequestedFanSpeed;