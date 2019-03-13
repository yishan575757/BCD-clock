/*
 * Filename: myRemainder.s
 * Author: Yishan Li
 * Userid: cse30xdp
 * Description: Calculate and return the reminder of division between divisor
 *              and devidend, works same as % in C 
 * Date: April 17th 2018
 * Sources of Help: Lecture notes
 */

@ Raspberry Pi directives
	.cpu	cortex-a53	@ Version of our Pis
	.syntax	unified		@ Modern syntax 

	.equ	FP_OFFSET, 4	@ Offset to set fp to base of saved regs

	.text			@ Switch to Text segment
	.global	myRemainder	@ Specify myRemainder as a global symbol
	.align	2		@ Align on evenly divisible by 4 byte address;
				@ .align n where 2^n determines alignment

/* 
 * Function Name: myRemainder.s
 * Function prototype: long myRemainder(long dividend, long divisor)
 * Description: works same as % operator in C, it will return the remainder of
 *              the dividend and divisior
 * Parameters: dividend - the value to be divided
 *             divisor - the value used to divide the dividend
 * Side Effects: None
 * Error Conditions: When the divisor is 0
 * Return Value: The remainder as a 32-bit signed integer
 * 
 * Registers used:
 *     r0 - arg 1 -- dividend
 *     r1 - arg 2 -- divisor
 *     r2 - local val -- holds the quotient
 *     r3 - local val -- holds the temperary result  
 */

myRemainder:
	@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr on the stack
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers

	@ Incoming parameters 
	sdiv	r2, r0, r1		@ quotient(r2)=dividend(r0)/divisor(r1)
	mul	r3, r2, r1		@ tmpResult(r3)=
					@ 	quotient(r2)*divisor(r1)
	sub	r2, r0, r3		@ remainder(r2)=
					@ 	dividend(r0)-tmpResult(r3)
	mov	r0, r2			@ Put return value in r0

	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore lr into pc for
					@  return

