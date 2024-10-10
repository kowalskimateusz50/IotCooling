#pragma once 

#include "one_wire.h"
#include "settings.h"
#include "GlobalWebServerData.h"
#include "taskshared.h"

void task_ReadTemperature(void *);

void ReadingsFiltration(float* FilteredRead, float RawRead); 