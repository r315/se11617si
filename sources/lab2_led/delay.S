/**
*	delay.S
*	creates a delay in ms for an given n as parameter
**/
	.global delay

	.section .data

one_ms_clks:
	.word 14745	/* one milisecond reload value for r1 */

	.section .text


delay: 
	str	lr,[sp,#-4]!	/* decrement sp and save lr */

dl_ms:	bl	one_ms
	subs    r0,r0,#1	
	bne     dl_ms	

	ldr	lr,[sp],#4	/* restore ls and increment sp */
	mov	pc,lr		/* return to caller */
	
	


one_ms:
	str	lr,[sp,#-4]!

	ldr 	r1,=one_ms_clks
	ldr	r1,[r1]
loop:
	subs 	r1,r1,#1
	bne	loop

	ldr	lr,[sp],#4
	mov	pc,lr
	
	.end

