#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

extern volatile uint16_t adc_value;

void ADC1_init(void);
uint16_t ADC1_raw_read(void);
void ADC2_init(void);
#endif
