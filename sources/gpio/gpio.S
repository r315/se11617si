/**
*	gpio.S
*	functions to access port 0
**/

			.global GPIO_Init
			.global GPIO_Read
			.global GPIO_Write
			.global GPIO_Set
			.global GPIO_Clr
			.global GPIO_Pin

			.section .text


GPIO_Init:
			mov		ip, sp
			push	{fp,ip,lr,pc}
			sub		fp, ip, #4
			ldr		r2, =gpio_dir
			ldr		r3, =gpio_pin
			ldr		r2, [r2]
			ldr		r3, [r3]
			str		r0, [r2]
			str		r1, [r3]
			ldmdb	fp, {fp,sp,pc}

GPIO_Read:
			ldr		r0,=gpio_pin
			ldr		r0, [r0]
			ldr		r0, [r0]
			mov		pc, lr

GPIO_Write:
			ldr		r1,=gpio_pin
			ldr		r1, [r1]
			str		r0, [r1]
			mov		pc, lr

GPIO_Set:
GPIO_Clr:
GPIO_Pin:
			mov		pc,lr

gpio_pin:
.word 0xE0028000       /* GPIO PIN */
gpio_dir:
.word 0xE0028008	   /* GPIO DIR */



	.end


