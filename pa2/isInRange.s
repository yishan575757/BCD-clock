/*
 * Filename: isInRange.s
 * Author: Yishan Li
 * Userid: cs30xdp
 * Description: Check if the value as the input parameter is in range
 * Date: April 16th 2018
 * Sources of Help: Piazza, Sean Powers, Aniket Mathur
 */

 @ Raspberry Pi directives
 	.cpu	cortex-a53	@ Version of our Pis
	.syntax	unified	@ Modern syntax  

	.equ	FP_OFFSET, 4	@ Offset to set fp to base of saved regs
	.equ	SP_OFFSET, 8	@ Offset to set sp for local variable

	.text			@ Switch to Text segment
	.global	isInRange	@ Specify isInRange as a global symbol
	.align	2		@ Align on evenly divisible by 4 byte address;
				@  .align n where 2^n determines alignment
/*
 * Function Name: isInRange()
 * Function Prototype: long isInRange(long value, long minRange, long maxRange)
 * Description: This fuction will test if the value as input parameter is 
 *              within the range between minRange, which is inclusive, and
 *              maxRange, which is exclusive.
 * Parameters: value - the value to be tested if in the range
 *             minRange - the minimum value of the range (inclusive)
 *             maxRange - the maximum value of the range (exclusive)
 * Side Effects: None
 * Error Conditions: When the minRange is greater or equal maxRange
 * Return value: -1 - if an error occurred
 *               1 - value is in range
 *               0 - value is not in range
 *
 * Registers used: 
 *     r0 - arg 1 -- value
 *     r1 - arg 2 -- minRange
 *     r2 - arg 3 -- maxRange
 *     r3 - local var -- holds the return value of the function
 */
isInRange:
	@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr on the stack
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
	sub	sp, sp, SP_OFFSET	@ Make space for the local variable 
	
	@ Incoming parameters in r0, r1, r2
	cmp	r1, r2			@ Check the value between r1 and r2
	blt	else			@ Falls to the else statement, which 
					@  implies minRange < maxRange
	
	/* Instructions from if statements */
	mov	r3, -1			@ -1 when an error occurred
	b	end_if			@ Branch always over else block

	/* Instructions from else statements */
else:	
	cmp	r0, r1			@ Compare value with minRange
					@  r0 >= r1
	blt	else_for_value		@ Opposite logic to branch over if 
					@  statements fall thr 
					@  if (value >= minRange)
	
	cmp	r0, r2			@ Compare value with maxRange 
					@  r0 < r2
	bge	else_for_value		@ Opposite logic to branch over if 
					@  statements

	/* Instructions from if statements within the else statements */
	mov	r3, 1			@ 1 when the value is within range
	b	end_if_else		@ Branch always over else block

else_for_value:
	mov	r3, 0			@ One or both of the expressions are
					@ false

end_if_else:

end_if: 
	mov	r0, r3			@ Return value goes to r0

	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore ler into pc for 
					@  return 
	



