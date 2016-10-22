
	.text	
	.global _start


# r2-r4 input parameters
# r0 retunr

_start: mov r2,# 4
	mov r3,# 2
	mov r4,# 3
	bl  maior
	b   .


maior:	cmp r2,r3
	bhs big_2

	cmp r3,r4
	bhs big_3

big_4:
	mov r0,r4
	mov r15,r14


big_2:	cmp r2,r4
	blo big_4
	mov r0,r2
	mov r15,r14


big_3:	mov r0,r3
	mov r15,r14

	.end

