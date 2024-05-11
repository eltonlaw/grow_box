#define STM32G070xx
#include "stm32g0xx.h"

volatile uint32_t uw_tick = 0;

void SysTick_Handler(void) {
    uw_tick++;
}

void delay(uint32_t delay) {
    uint32_t tickstart = uw_tick;
    while ((uw_tick - tickstart) < delay);
}

int main(void) {
    SysTick_Config(16000);
    while (1) {
        delay(1000);
    }
}
