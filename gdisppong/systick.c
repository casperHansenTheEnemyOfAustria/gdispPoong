#include "debug.h"
#include "startup.h"
#include "systick.h"
static int systick_flag;
static int delay_count;
void kill(){
	*GPIO_ODR_LOW = 0x00;
	while(1){
	}
}


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




void init_systick_handler(){
		*((void (**)(void))0x2001C03c) = systick_irq_handler;
		systick_flag = 0;
}
