/**
*	delay.S
*	creates a delay in ms for an given n as parameter
**/
	.global delay

	.section .text

one_ms_clks:
	.word 14745

delay: 
	str	lr,[sp,#-4]!

dl_ms:

	

	
	add	sp,sp,#4
	ldr	pc,[sp]
	
	


one_ms:
	str	lr,[sp,#-4]!

	ldr	pc,[sp,#4]!
/*

dm:

	mov	ip, sp
	stmfd	sp!, {fp, ip, lr, pc}
	sub	fp, ip, #4

	sub	sp, sp, #8

	str	r0, [fp, #-16]
	
	sub	sp, fp, #12
	ldmfd	sp, {fp, sp, lr}
	bx	lr



*/	


/*

subs    r0,r0,#1	
	bne     dl_ms	


	ldr 	r1,=one_ms_clks
	ldr	r1,[r1]
loop:
	subs 	r1,r1,#1
	bne	loop
*/
	.end

