#ifndef __SSI_H__
#define __SSI_H__

#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "lwipopts.h"
#include "GlobalWebServerData.h"

u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen);
void ssi_init();

#endif // __SSI_H__