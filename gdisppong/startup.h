/// startup.h

#pragma once

__attribute__((naked)) __attribute__((section(".start_section"))) void
startup(void);
/// startup.h

#pragma once

__attribute__((naked)) __attribute__((section(".start_section"))) void
startup(void);


#define GPIO_E 0x40021000
#define GPIO_E_MODER ((volatile unsigned int*) (GPIO_E))
#define GPIO_E_OTYPER ((volatile unsigned short *) (GPIO_E+0x4))
#define GPIO_E_OSPEEDR ((volatile unsigned int *) (GPIO_E+0x8))
#define GPIO_E_PUPDR ((volatile unsigned int *) (GPIO_E+0xC1))
#define GPIO_E_IDR_LOW ((volatile unsigned short *) (GPIO_E+0x10))
#define GPIO_E_IDR_HIGH ((volatile unsigned char *) (GPIO_E+0x11))
#define GPIO_E_ODR_LOW ((volatile unsigned char *) (GPIO_E+0x14))
#define GPIO_E_ODR_HIGH ((volatile unsigned char *) (GPIO_E+0x14+1)) 

#define GPIO_D 0x40020C00
#define GPIO_D_Moder ((volatile unsigned int*) (GPIO_D))
#define GPIO_D_Otyper ((volatile unsigned short *) (GPIO_D+0x4))
#define GPIO_D_Ospeedr ((volatile unsigned int *) (GPIO_D+0x8))
#define GPIO_D_Pupdr ((volatile unsigned int *) (GPIO_D+0xC))
#define GPIO_D_IdrLow ((volatile unsigned short *) (GPIO_D+0x10))
#define GPIO_D_IdrHigh ((volatile unsigned char *) (GPIO_D+0x11))
#define GPIO_D_OdrLow ((volatile unsigned char *) (GPIO_D+0x14))
#define GPIO_D_OdrHigh ((volatile unsigned char *) (GPIO_D+0x14+1))

#define SYSCFG_EXTICR1 ((volatile unsigned int*) (0x40013808))
 
#define EXTI 0x40013C00
#define EXTI_IMR ((volatile unsigned int*)(EXTI)) 
#define EXTI_RTSR ((volatile unsigned int*)(EXTI + 8))
#define EXTI_FTSR ((volatile unsigned int*)(EXTI + 0xC))
#define EXTI_PR ((volatile unsigned int*) (EXTI + 0x14))

#define EXTI0_IRQ_BPOS 1
#define EXTI1_IRQ_BPOS (1<<1)
#define EXTI2_IRQ_BPOS (1<<2)


#define NVIC 0xE000E100
#define NVIC_ISER0 ((volatile unsigned int*)(NVIC))
#define NVIC_EXTI2_IRQ_BPOS 1<<8
#define NVIC_EXTI1_IRQ_BPOS 1<<7
#define NVIC_EXTI0_IRQ_BPOS 1<<6

#define EXTI2_IRQVEC ((void(**)(void))0x2001C060)
#define EXTI1_IRQVEC ((void(**)(void))0x2001C05C)
#define EXTI0_IRQVEC ((void(**)(void))0x2001C058)


__attribute__((naked)) void graphic_initialize();

__attribute__((naked)) void graphic_clear_screen();

__attribute__((naked)) void graphic_pixel_set(int x, int y);

__attribute__((naked)) void graphic_pixel_clear(int x, int y);
