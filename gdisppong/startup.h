/// startup.h

#pragma once

__attribute__((naked)) __attribute__((section(".start_section"))) void
startup(void);
/// startup.h

#pragma once

__attribute__((naked)) __attribute__((section(".start_section"))) void
startup(void);

#define STK_CTRL ((volatile unsigned int *)(0xE000E010))  
#define STK_LOAD ((volatile unsigned int *)(0xE000E014))  
#define STK_VAL ((volatile unsigned int *)(0xE000E018))  


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
#define GPIO_D_MODER ((volatile unsigned int*) (GPIO_D))
#define GPIO_D_OTYPER ((volatile unsigned short *) (GPIO_D+0x4))
#define GPIO_D_OSPEEDR ((volatile unsigned int *) (GPIO_D+0x8))
#define GPIO_D_PUPDR ((volatile unsigned int *) (GPIO_D+0xC))
#define GPIO_D_IDR_LOW ((volatile unsigned short *) (GPIO_D+0x10))
#define GPIO_D_IDR_HIGH ((volatile unsigned char *) (GPIO_D+0x11))
#define GPIO_D_ODR_LOW ((volatile unsigned char *) (GPIO_D+0x14))
#define GPIO_D_ODR_HIGH ((volatile unsigned char *) (GPIO_D+0x14+1))

#define SYSCFG_EXTICR1 ((volatile unsigned int*) (0x40013808))
#define SCB 0xE000ED00
#define SCB_VTOR ((volatile unsigned long *)SCB + 0x8)
 
#define EXTI 0x40013C00
#define EXTI_IMR ((volatile unsigned int*)(EXTI)) 
#define EXTI_RTSR ((volatile unsigned int*)(EXTI + 8))
#define EXTI_FTSR ((volatile unsigned int*)(EXTI + 0xC))
#define EXTI_PR ((volatile unsigned int*) (EXTI + 0x14))

#define EXTI0_IRQ_BPOS 1
#define EXTI1_IRQ_BPOS (1<<1)
#define EXTI2_IRQ_BPOS (1<<2)

// #define TIM6_IRQVEC ((void (**)(void)) 0x2001C118 )
#define NVIC_TIM6_IRQ_BPOS (1<<22);
// #define NVIC_TIM6_ISER ((volatile unsigned int *) 0xE000E104)

#define NVIC 0xE000E100
#define NVIC_ISER0 ((volatile unsigned int*)(NVIC))
#define NVIC_EXTI2_IRQ_BPOS 1<<8
#define NVIC_EXTI1_IRQ_BPOS 1<<7
#define NVIC_EXTI0_IRQ_BPOS 1<<6

#define EXTI2_IRQVEC ((void(**)(void))0x2001C060)
#define EXTI1_IRQVEC ((void(**)(void))0x2001C05C)
#define EXTI0_IRQVEC ((void(**)(void))0x2001C058)


// #define TIM6 (*((TIM *)0x40001000))
#define TIM7 (*((TIM *)0x40001400))
#define UDIS (1<<1)
#define CEN (1<<0)
#define UIF (1<<0)
#define UIE (1<<0)
#define TIMER6_IRQ (1<<22)
#define TIM6_IRQVEC ((void (**)(void))0x2001C118)
#define NVIC_TIM6_ISER ((volatile unsigned int *)0xE000E104)
#define NVIC_TIM6_ICER ((volatile unsigned int *)0xE000E184)


typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
typedef volatile struct tag_tim{
    uint32_t CR1;
    uint32_t CR2;
    uint32_t Empty1;
    uint32_t DIER;
    uint32_t SR;
    uint32_t EGR;
    uint32_t Empty2;
    uint32_t Empty3;
    uint32_t Empty4;
    uint32_t CNT;
    uint32_t PSC;
    uint32_t ARR;
}TIM;


#define TIM6 0x40001000
#define TIM6_CR1 ((volatile unsigned int *)(TIM6)) 
#define TIM6_CR2 ((volatile unsigned int *)(TIM6 + 4))
#define TIM6_DIER  ((volatile unsigned int *)(TIM6 + 0xC))
#define TIM6_SR ((volatile unsigned int *)(TIM6 + 0x10))
#define TIM6_EGR  ((volatile unsigned int *)(TIM6 + 0x14))
#define TIM6_CNT ((volatile unsigned int *)(TIM6 + 0x24))
#define TIM6_PSC ((volatile unsigned int *)(TIM6 + 0x28))
#define TIM6_ARR ((volatile unsigned int *)(TIM6 + 0x2C))
#define UIE (1<<0)
#define UIF (1<<0)



__attribute__((naked)) void graphic_initialize();

__attribute__((naked)) void graphic_clear_screen();

__attribute__((naked)) void graphic_pixel_set(int x, int y);

__attribute__((naked)) void graphic_pixel_clear(int x, int y);
