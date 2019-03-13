/*
 * Filename: isEven.s
 * Author: Yishan Li
 * Userid: cs30xdp
 * Description: Check if the value as the input parameter is even
 * Date: April 16th 2018
 * Sources of Help: Zhimin Lin, Christoph Steefel
 */

 @ Raspberry Pi directives
 	.cpu	cortex-a53	@ Version of our Pis
	.syntax	unified	@ Modern syntax  

	.equ	FP_OFFSET, 4	@ Offset to set fp to base of saved regs
	.equ	DIVIDEND, 2	@ DIVIDEND used to test if value is even

	.text			@ Switch to Text segment
	.global	isEven		@ Specify isInRange as a global symbol
	.align	2		@ Align on evenly divisible by 4 byte address;
				@  .align n where 2^n determines alignment
/*
 * Function Name: isEven()
 * Function Prototype: long isEven(long value)
 * Description: This fuction will test if the value as input parameter is 
 *              a even number or odd number 
 * Parameters: value - the value to be tested if it is even or odd 
 * Side Effects: None
 * Error Conditions:  Not applicable 
 * Return value: 
 *               1 - value is even
 *               0 - value is odd
 *
 * Registers used: 
 *     r0 - arg 1 -- value and return value of the function myRemainder
 *     r1 - arg 2 -- the second actual arg of function myRemainder
 *     r2 - local var -- the return value of the function
 */
isEven:
	@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr on the stack
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
	
	@ Incoming parameters in r0
	mov	r1, DIVIDEND		@ Set the second argument of 
					@  myRemainder to 2
	bl	myRemainder		@ Make function call of myRemainder
	
	cmp	r0, 0			@ Compare the return value with 0
	bne	else			@ Opposite logic to branch over if
					@  statements
	/* Instructions from if statements */
	mov	r2, 1			@ When the return value equals to
					@  zero, store the return value as 1
	b	end_if			@ Branch always over else block 

else:
	/* Instructions from else statements */
	mov	r2, 0			@ When the value is odd

end_if:
	mov	r0, r2			@ Return value goes to r0

	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore ler into pc for 
					@ return 
	



