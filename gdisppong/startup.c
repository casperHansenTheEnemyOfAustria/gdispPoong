/// startup.c

#include "startup.h"

__attribute__((naked)) __attribute__((section(".start_section"))) void
startup(void) {
	__asm__ volatile(" LDR R0,=0x2001C000\n"); /* set stack */
	__asm__ volatile(" MOV SP,R0\n");
	__asm__ volatile(" BL main\n");   /* call main */
	__asm__ volatile(".L1: B .L1\n"); /* never return */
}





__attribute__((naked)) void graphic_initialize(){
	__asm__ volatile(".HWORD  0xDFF0\n");
	__asm__ volatile("BX LR\n");
}


__attribute__((naked)) void graphic_clear_screen(){
	__asm__ volatile(".HWORD  0xDFF1\n");
	__asm__ volatile("BX LR\n");
}

__attribute__((naked)) void graphic_pixel_set(int x, int y){	
	__asm__ volatile(".HWORD  0xDFF2\n");
	__asm__ volatile("BX LR\n");
}


__attribute__((naked)) void graphic_pixel_clear(int x, int y){
	__asm__ volatile(".HWORD  0xDFF3\n");
	__asm__ volatile("BX LR\n");
}


__attribute__((naked )) void enable_interrupt(){
	__asm__ volatile(" CPSIE I\n");
	__asm__ volatile(" BX LR\n");
}

__attribute__((naked )) void disable_interrupt(){
	__asm__ volatile(" CPSID I\n");
	__asm__ volatile(" BX LR\n");
}