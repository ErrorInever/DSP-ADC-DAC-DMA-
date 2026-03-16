# STM32 ADC-DAC Loopback via DMA

This project demonstrates a real-time analog signal processing pipeline using the STM32F446RET6. 
It features an autonomous data acquisition system where analog input is captured, processed by the CPU, and output back as an analog signal.
---

### Overview
The system creates a "Digital Wire" with the following flow:
1. Input: Analog signal is captured via ADC1 (Channel 1, Pin PA1).
2. Transport: DMA2 (Stream 0) automatically moves raw data from the ADC to a memory variable (adc_val) without CPU intervention.
3. Processing: The CPU reads adc_val in the main loop, allowing for real-time mathematical manipulation (e.g., filtering, scaling, or inversion).
5. Output: The processed value is sent to DAC1 (Channel 1, Pin PA4) to recreate the analog voltage.


### Hardware Configuration

| Peripheral | Pin     | Mode     | Description                         |
|------------|---------|----------|-------------------------------------|
| ADC1       | PA1     | Analog   | Signal Input (0V - 3.3V)            |
| DAC1       | PA4     | Analog   | Signal Output                       |
| USART2     | PA2/PA3 | AF7      | Telemetry / Debugging (115200 baud) | 
| DMA2       | N/A     | Stream 0 | ADC-to-Memory transfer              |
