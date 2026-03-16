#include "main.h"
#include "adc.h"
#include "stm32f446xx.h"
#include <stdint.h>



void ADC1_init(void) {
    // RCC
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    (void)RCC->APB2ENR;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    (void)RCC->AHB1ENR;
    // Enable analog mode (11)
    GPIOA->MODER |= (3 << GPIO_MODER_MODER1_Pos); // PA1 в Analog Mode (11)
    // Setup ADC frequency
    ADC->CCR &= ~ADC_CCR_ADCPRE; // reset prescaler
    ADC->CCR |= (2 << ADC_CCR_ADCPRE_Pos); // prescaler 4
    // Setup resolution and work mode
    ADC1->CR1 &= ~ADC_CR1_RES; // resolution 12 bit (00)
    ADC1->CR2 |= ADC_CR2_CONT; // continuous mode
    // Select which channel to measure. If there is only one channel, write its number in the first slot SQR3
    ADC1->SQR3 = (1 << ADC_SQR3_SQ1_Pos); // channel 1 - first in queue
    ADC1->SMPR2 |= (3 << ADC_SMPR2_SMP1_Pos); // Sampling time is 56 cycles for channel 1
    // enable and start
    ADC1->CR2 |= ADC_CR2_ADON; // enable ADC
    ADC1->CR2 |= ADC_CR2_SWSTART; // start 
}

void ADC2_init(void) {
    // RCC
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    (void)RCC->APB2ENR;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    (void)RCC->AHB1ENR;
    // Enable analog mode (11)
    GPIOA->MODER |= (3 << GPIO_MODER_MODER1_Pos); // PA1 в Analog Mode (11)
    // Setup ADC frequency
    ADC->CCR &= ~ADC_CCR_ADCPRE; // reset prescaler
    ADC->CCR |= (2 << ADC_CCR_ADCPRE_Pos); // prescaler 4
    // Setup resolution and work mode
    ADC1->CR1 &= ~ADC_CR1_RES; // resolution 12 bit (00)
    ADC1->CR2 |= ADC_CR2_CONT; // continuous mode
    // Select which channel to measure. If there is only one channel, write its number in the first slot SQR3
    ADC1->SQR3 = (1 << ADC_SQR3_SQ1_Pos); // channel 1 - first in queue
    ADC1->SMPR2 |= (3 << ADC_SMPR2_SMP1_Pos); // Sampling time is 56 cycles for channel 1
    // Allow DMA request generation
    ADC1->CR2 |= ADC_CR2_DMA;
    // Allow continuous generation of requests (DDS = DMA Disable Selection)
    ADC1->CR2 |= ADC_CR2_DDS;
    // enable and start
    ADC1->CR2 |= ADC_CR2_ADON; // enable ADC
    ADC1->CR2 |= ADC_CR2_SWSTART; // start 
}

uint16_t ADC1_raw_read(void) {
    // pooling
    while(!(ADC1->SR & ADC_SR_EOC)); // waiting for the measurement to be completed.
    return (uint16_t)ADC1->DR; // read data (EOC flag auto-reset)
}