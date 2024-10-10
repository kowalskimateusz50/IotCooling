#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

//Temperature data to webserver display
extern float gTemperature;
extern uint RotationCounter;
//Mutex wchich locking this variable
//static SemaphoreHandle_t TemperatureMutex;