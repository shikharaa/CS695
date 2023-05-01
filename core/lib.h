#ifndef _HEADERS_
#define _HEADERS_
#include <stdio.h>
#include <stdbool.h>
#include "lib.c"
#include "struct-device.h"

void led_blinks (int, int, int);
void config(struct device *alpha);
//void connectNetwork(struct device *, bool);
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
void welcome_msg();
void d_collect_msg(long*);
void print_json(char*);
void udelay_basics (long);
long take_time_basics();
void print_sensors_state(void);
void init_internal(bool);

char* get_internal();

#endif

