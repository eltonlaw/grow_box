#include "stm32g0xx.h"
#include "gpio.h"

/* __libc_init_array is part of the C standard lib init process and calls _init */
void _init(void) { }

volatile uint32_t uw_tick = 0;

void SysTick_Handler(void) {
    uw_tick++;
}

void delay(uint32_t delay) {
    uint32_t tickstart = uw_tick;
    while ((uw_tick - tickstart) < delay);
}

int main(void) {
    /* 16Mhz internal clock, 1ms per systick tick */
    SysTick_Config(16000);
    SystemCoreClockUpdate();

    gpio_config_t gpio_cfg = {};
    gpio_open(&gpio_cfg);
    while (1) {
        GPIOA->BSRR = GPIO_BSRR_BS5;
        delay(1000);
        GPIOA->BSRR = GPIO_BSRR_BR5;
        delay(1000);
    }
}
