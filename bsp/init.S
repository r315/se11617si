
/*
 * init.S
 *
 *  Created on: 14 Oct 2010
 *      Author: psampaio
 *
 * Modified on : 15 Dec 2016
 *       By: Hugo Reis  
 */

/*****************************************************************
	Module includes the interrupt vectors and start-up code.
 ******************************************************************/

.section .startup, "ax"
.global _start

_vectors:
      ldr      pc,ResetVector
      ldr      pc,UndefinedInstruction
      ldr      pc,SoftwareIntrrupt
      ldr      pc,PrefetchAbort
      ldr      pc,DataAbort
      .word    0xB8A06F58  /* = ~(0xE59FF018 * 7) + 1 */
      ldr      pc,IRQVector
      ldr      pc,FIQVector
   
ResetVector:            .word ResetHandler
UndefinedInstruction:   .word UndefHandler
SoftwareIntrrupt:       .word SWIHandler
PrefetchAbort:          .word PAbortHandler
DataAbort:              .word DAbortHandler
                        .word 0x00000000   
IRQVector:              .word IRQHandler
FIQVector:              .word FIQHandler   
   


ResetHandler:
_start:
    ldr   	r0, =__stack_top__
   	mov   	sp, r0

	/* Clear .bss section */
   	ldr   	r1, =__bss_start__
   	ldr   	r2, =__bss_end__
   	ldr   	r3, =0
bss_clear_loop:
   	cmp   	r1, r2
   	strne 	r3, [r1], #+4
   	bne   	bss_clear_loop

    /* Initialize .data section */
      ldr      r1,=__sdata__
      ldr      r2,=__idata__
      ldr      r3,=__edata__   
   
      cmp      r1,r2          /* if(idata == sdata) section already on place */
      beq      skip_data_copy

data_copy:
      cmp      r1,r3
      ldrne    r4,[r2],#4
      strne    r4,[r1],#4
      bne      data_copy

skip_data_copy:	

   /* Activate High speed GPIO */
      mov      r0,#1             /* High speed GPIO enable for port 0 */
      ldr      r2,=0xE01FC1A0    /* System control status register address*/
      str      r0,[r2]

   /* Configure Memory Accelerator Module for flash memory*/      
      mov      r0,#4             /* By default MAMTIM is set to have 7 clocks in each fetch cycle */
      ldr      r2,=0xE01FC004    /* should be set accordingly before enabled */
      str      r0,[r2]           /* XTAL <20MHz 1cclk */
                                 /* XTAL 20MHz to 40MHz 2cclk */
                                 /* XTAL 40MHz to 60MHz 3cclk */
                                 /* XTAL >60MHz 4cclk */

      mov      r0,#2             /* MAM Functions Fully activated */ 
      ldr      r2,=0xE01FC000    /* MAMCR register address */
      str      r0,[r2]


   /* call main() function */
    mov     fp, #0
    mov     r0, #0
    mov     r1, #0
    bl        main

    b     .                      /* if returns loop */ 
   
UndefHandler:
      b UndefHandler
SWIHandler:
      b SWIHandler
PAbortHandler:
      b PAbortHandler
DAbortHandler:
      b DAbortHandler
IRQHandler:
      b IRQHandler
FIQHandler:
      b FIQHandler   

/****************************************************************************/
/*                         Stack area                                       */
/****************************************************************************/
.section .stack
      .space	1024 * 2
__stack_top__:
      .end
      
