#include "WebServer.h"

void WebServer() {
    
    httpd_init();
    ssi_init();
    printf("Http server initialized.\n");
}