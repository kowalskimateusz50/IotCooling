#pragma once

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwipopts.h"
#include "ssi.h"
#include "lwip/apps/httpd.h"


void task_WebServer(void*);