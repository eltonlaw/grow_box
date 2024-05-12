#define STM32G070xx
#include "stm32g0xx.h"
#include "gpio.h"

volatile uint32_t uw_tick = 0;

void SysTick_Handler(void) {
    uw_tick++;
}

void delay(uint32_t delay) {
    uint32_t tickstart = uw_tick;
    while ((uw_tick - tickstart) < delay);
}

int main(void) {
    int x = add(1, 2);
    /* 16Mhz internal clock, 1ms per systick tick */
    SysTick_Config(16000);
    while (1) {
        delay(1000);
    }
}
