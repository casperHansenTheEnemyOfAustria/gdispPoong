#include "debug.h"
#include "startup.h"
#include "systick.h"
#include "ascii.h"
static int systick_flag;
static int delay_count;


char timer_flag;

int count;

char ticks;
char seconds;

void delay_1micro_systick(){
	systick_flag = 0;
	*STK_LOAD = (168);
	*STK_VAL = 0;
	*STK_CTRL = 7;
}

void interrupt_delay(int ms){
	delay_count = ms;
	delay_1micro_systick();
}

void systick_irq_handler(){
	// kill();
	*STK_CTRL = 0;
	delay_count = delay_count-1;
	if(delay_count > 0){
		delay_1micro_systick();
	}else{
		systick_flag = 1;
	}
}

void timer6_interrupt_handler(){

		//  GPIO_E.ODR_LOW =  0xff;
	TIM6.SR &= ~UIF;
	ticks++;
	if(ticks > 9){
		ticks = 0;
		seconds++;
		char * string_seconds = &seconds;
		ascii_write_text_at(string_seconds,1,2  );
	}
	if(seconds > count){
		timer_flag = 1;
		TIM6.CR1 &= ~CEN;
	}
}

char get_timer_flag(){
	return timer_flag;
}

void timer6_init(){
	ticks = 0;
	seconds = 0;

	TIM6.CR1 &= ~CEN;
	*((void (**)(void))0x2001C118) = timer6_interrupt_handler;
	// int * iser_test = &(*NVIC_TIM6_ISER);
	*NVIC_TIM6_ISER |=  TIMER6_IRQ;
	// *NVIC_TIM6_ICER |= TIMER6_IRQ;
	TIM6.PSC = 83;
	TIM6.ARR = 9999;
	TIM6.DIER |= UIE;
	TIM6.CR1 |= CEN;
}

void timer6_start(int seconds){
	count = count;
	TIM6.PSC = 839*seconds;
	TIM6.ARR = 9999;
	TIM6.DIER |= UIE;
	TIM6.CR1 |= CEN;
}


void init_systick_handler(){
		*((void (**)(void))0x2001C03c) = systick_irq_handler;
		systick_flag = 0;
}
