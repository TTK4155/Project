/*
 * ADCtest.h
 *
 * Created: 19/09/2019 14:37:41
 *  Author: tedes
 */ 


#ifndef ADC_H_
#define ADC_H_
#define F_CPU 4915200
#define ADC_OFFSET 0x1400
#include <util/delay.h>

// Takes a integer from 1 to 4 and returns the analog value of the corresponding
// channel of the ADC
char adc_read(uint8_t channel);

#endif /* ADC_H_ */