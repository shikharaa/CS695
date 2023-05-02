#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "struct-device.h"
#include "config.h"
#include "devices.h"
#include "data/internal/internal.h"

void init_LEDs();
void led_GPIO(int, int);
bool read_GPIO(int);

void config(struct device *alpha)
{
    /* User assignments */
    alpha->id = temp;

    #ifdef MICROCONTROLLER
        alpha->ssid_wifi = ssid_WiFi;
        alpha->pass_wifi = pass_WiFi;
    #endif

    alpha->isEnable[0] = isEnable_VoltageIntern;
    alpha->isEnable[1] = isEnable_TemperatureExtern;
    alpha->isEnable[2] = isEnable_Humidity;
    alpha->isEnable[3] = isEnable_Pressure;

    alpha->s_name[0] = "InternalVoltage";
    alpha->s_name[1] = "Temperature";
    alpha->s_name[2] = "Humidity";
    alpha->s_name[3] = "Pressure";


    alpha->interv = intv;

}

void initPeripherals(long* counter)
{
    *counter = 0;		// Init counter

    #ifdef SHELLPRINT
    	welcome_msg();	// Printf in shell
    #endif

    init_LEDs();
    init_bme280(true);
}


void led_blinks(int pin, int iterate, int unit_sec)	// LED Blink function-> led: 0 Green LED, 1 Red LED - iter: iterations quantity - usec: delay time in usec
{
     int i;
     for (i=0;i<iterate;i++)
     {
		 led_GPIO(pin, 1);
		 udelay_basics (unit_sec);
		 led_GPIO(pin, 0);
		 udelay_basics (unit_sec);
     }
}


void pnp_sensors()
{
    init_bme280(false);

}


void getData(struct device *alpha, long *count)
{
    int i;
    ++(*count);

    #ifdef SHELLPRINT	// Printf in shell
	d_collect_msg( count );
	print_sensors_state();
    #endif


    /* GET DATA INTERNAL TEMPERATURE */
    strcpy(alpha->d[0], get_internal());

    /* GET DATA BME280 */
    if (check_bme280())
    {
		for (i=0; i<3; i++)
	   	    strcpy(alpha->d[i+1], get_bme280(i));
    }
    else
    {
		for (i=0; i<3; i++)
			strcpy(alpha->d[i+1], "0");
    }


}


void generateJson(struct device *alpha)
{
    int i, beta;

    strcpy(alpha->json, "{\"Apache server\":[");
    beta = 0;
    strcat(alpha->json, "{\"sensor\":\"Internal\",\"data\":[");
    for (i=0;i<1;i++)
    {
		if (alpha->isEnable[i+0])
		{
			if (beta != i) strcat(alpha->json, ",");
			strcat(alpha->json, "{\"");
			strcat(alpha->json, alpha->s_name[i+0]);
			strcat(alpha->json, "\":\"");
			strcat(alpha->json, alpha->d[i+0]);
			strcat(alpha->json, "\"}");
		}
	else
	    beta++;
    }
    strcat(alpha->json, "]}");

    if (check_bme280())
    {
		beta = 0;
		strcat(alpha->json, ",{\"sensor\":\"Environmental\",\"data\":[");
		for (i=0;i<3;i++)
		{
			if (alpha->isEnable[i+1])
			{
				if (beta != i) strcat(alpha->json, ",");
				strcat(alpha->json, "{\"");
				strcat(alpha->json, alpha->s_name[i+1]);
				strcat(alpha->json, "\":\"");
				strcat(alpha->json, alpha->d[i+1]);
				strcat(alpha->json, "\"}");
			}
			else
			beta++;
		}
		strcat(alpha->json, "]}");
    }

	strcat(alpha->json, "],\"device\": \"");
	strcat(alpha->json, alpha->id);
	strcat(alpha->json, "\",\"timestamp\": \"0\"}");

    #ifdef SHELLPRINT
    	print_json(alpha->json);	// Printf in shell
    #endif
}


void t_delay(long desiredDelay, long actualDelay)
{
	if (actualDelay >= desiredDelay)		/* To prevent crashes */
		actualDelay = desiredDelay;
    udelay_basics ( (desiredDelay - actualDelay) * 1000000 );	/* Time set by user  minus  loss time by operation */
}

long take_time()
{
    return take_time_basics();
}
