#include "main.h"
#include "stm32f446xx.h"
#include <stdint.h>

void DAC1_init(void) {
    // RCC
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    (void)RCC->AHB1ENR;
    RCC->APB1ENR |= RCC_APB1ENR_DACEN;
    (void)RCC->APB1ENR;
    // PA4 to analog mode
    GPIOA->MODER |= (3 << GPIO_MODER_MODER4_Pos);
    // enable channel 1. default 12 bit
    DAC->CR |= DAC_CR_EN1;
}

void DAC1_set(uint16_t val) {
    if(val > 4095) val = 4095;
    DAC->DHR12R1 = (val & 0xFFF); // register DHR12R1 (Data Holding Register 12-bit Right-aligned)
}
