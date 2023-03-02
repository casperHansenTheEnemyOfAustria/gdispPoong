#include "ascii.h"
#include "startup.h"
#include "main.h"

volatile char seconds;
volatile char ten_seconds;
volatile char minutes;





void timer6_init(){
	time.seconds = 0;
	*TIM6_CR1 &= ~CEN;
	*TIM6_IRQVEC = timer6_interrupt;
	*NVIC_TIM6_ISER |= NVIC_TIM6_IRQ_BPOS;
	
	*TIM6_PSC = 8399;
	*TIM6_ARR = 999;
	*TIM6_DIER |= UIE;
	*TIM6_CR1 |= CEN;
}

int get_current_time(){
	return time.seconds+ time.ten_seconds*10 + time.minutes*60;
}

void tim6_disable(){
	*TIM6_CR1 &= ~CEN;
}

void tim6_enable(){
	*TIM6_CR1 |= CEN;
}

void gpio_init(){
	*SCB_VTOR = 0x2001c000;
	*GPIO_E_MODER = 0x55555555;
	*GPIO_E_OTYPER = 0x0;
    *GPIO_E_OSPEEDR = 0xffffffff;
}


