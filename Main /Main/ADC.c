/*
 * ADCtest.c
 *
 * Created: 19/09/2019 14:37:13
 *  Author: tedes
 */ 
#include "ADC.h"


char adc_read(uint8_t channel) {
	if (channel <= 4 && channel > 0) {
		char *p = ADC_OFFSET;
		*p = channel+3;
		_delay_us(60);
		int a=*p;
		//printf("%d",a,"/n");
		return *p;
		} else {
		return 0;
	}
}