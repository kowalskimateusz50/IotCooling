#include "ssi.h"

// max length of the tags defaults to be 8 chars
// LWIP_HTTPD_MAX_TAG_NAME_LEN
const char* ssi_example_tags[] = {
    "temp",     // 0
    "fanspd"    // 1
};

u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen)
{
    size_t printed;
    switch (iIndex) {
        case 0: /* "temp */
        {
            //Read temperature from global data and display on webserver
            float temperature = gTemperature;
            printed = snprintf(pcInsert, iInsertLen, "Temperature: %.2f", temperature);
        }
        break;
        case 1: /* "fanspd*/
        {
            //Read fan rotation speed and display on webserver
            uint FanSpeedRpm = gFanSpeedRpm;
            printed = snprintf(pcInsert, iInsertLen, "Fan speed: %d rpm", FanSpeedRpm);
        }
        break;        
        default: /* unknown tag */
            printed = 0;
            break;
    }
      LWIP_ASSERT("sane length", printed <= 0xFFFF);
      return (u16_t)printed;
}

void ssi_init()
{
    for (size_t i = 0; i < LWIP_ARRAYSIZE(ssi_example_tags); i++) {
        LWIP_ASSERT("tag too long for LWIP_HTTPD_MAX_TAG_NAME_LEN",
                    strlen(ssi_example_tags[i]) <= LWIP_HTTPD_MAX_TAG_NAME_LEN);
    }

      http_set_ssi_handler(ssi_handler,
                           ssi_example_tags, LWIP_ARRAYSIZE(ssi_example_tags)
      );
}