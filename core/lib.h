#ifndef _HEADERS_
#define _HEADERS_

#include <stdio.h>
#include <stdbool.h>

#include "lib.c"
//#include "struct-device.h"

void led_blinks (int, int, int);
void config(struct device *alpha);
void connectNetwork(struct device *, bool);
void initPeripherals(long *); 
void pnp_sensors();
void getData(struct device *,long *);
void generateJson(struct device *);
void t_delay(long, long); 
long take_time();
bool init_socket(const char*, int,bool);
void init_LEDs();
void led_GPIO(int, int);
bool read_GPIO(int);
void config(struct device *alpha);
struct device {
   const char *id;
   const char *address;
   int address_port;
   const char *top;
   const char *ssid_wifi;
   const char *pass_wifi;
   bool isEnable[12];
   char d[12][10];    /* Sensors Data String */
   const char *s_name[30];    /* Sensors Names */
   bool isConnected[12];
   long interv;
   char json[1023];
};

#endif

