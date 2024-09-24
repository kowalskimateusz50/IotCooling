#include "task_WebServer.h"

void task_WebServer(void*) {
    
    httpd_init();
    ssi_init();
    printf("Http server initialized.\n");

    while(true)
    {
    };

}