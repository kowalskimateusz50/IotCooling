#pragma once 

#include "one_wire.h"
#include "GlobalWebServerData.h"


void task_ReadTemperature(void *);

void ReadingsFiltration(float* FilteredRead, float RawRead); 