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

/* Setup PA5 as output fro status pin */
void gpio_init() {
    volatile uint32_t tmpreg;

    /* Enable GPIOA clock */
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
    /* Ensure clock is enabled by read op */
    tmpreg = RCC->IOPENR & RCC_IOPENR_GPIOAEN;
    (void) tmpreg;
    /* Configure PA5 as output */
    GPIOA->MODER &= ~GPIO_MODER_MODE5;
    GPIOA->MODER |= GPIO_MODER_MODE5_0;
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT5;
    GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5;
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_0;
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5;
}

int main(void) {
    /* 16Mhz internal clock, 1ms per systick tick */
    // OS_Tick_Enable();
    SysTick_Config(16000);
    SystemCoreClockUpdate();

    gpio_init();
    while (1) {
        GPIOA->BSRR = GPIO_BSRR_BS5;
        delay(500);
        GPIOA->BSRR = GPIO_BSRR_BR5;
        delay(500);
        GPIOA->BSRR = GPIO_BSRR_BS5;
        delay(5000);
        GPIOA->BSRR = GPIO_BSRR_BR5;
        delay(5000);
    }
}
