/*
 * Filename: incrementClockValue.s
 * Author: Yishan Li
 * Userid: cs30xdp
 * Description: It will increment the nibble by 1
 * Date: May 2nd 2018
 * Sources of Help: Writeup, lecture notes
 */

 @ Raspberry Pi directives
 	.cpu	cortex-a53	@ Version of our Pis
	.syntax	unified		@ Modern syntax  

	.equ	FP_OFFSET, 4	@ Offset to set fp to base of saved regs

	.global	incrementClockValue
	.text			@ Switch to Text segment
	.align	2		@ Align on evenly divisible by 4 byte address;
				@  .align n where 2^n determines alignment
/*
 * Function Name: incrementClockValue
 * Function Prototype:
 *          unsigned char incrementClockValue( unsigned char BCDbits,
 *                                             const unsigned int maxValue);
 * Description: This function will increment the nibble by 1 and return the
 *              value after the increment
 *             
 * Parameters: BCDbits - the bits that is going to be increment 
 *             maxValue - maximum value that the BCDbits can be after increment
 *                        
 * Side Effects: The BCDbits incremented by 1
 * Error Conditions: if incremented BCDbits > maxValue
 * Return value: 0 - if incremented BCDbits > maxValue
 *               incremented BCDbits - if is within range
 *
 * Registers used: 
 *                r0 - arg 1 -- BCDbits 
 *                r1 - arg 2 -- maxValue   
 */

incrementClockValue:
	@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr on the stack
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
	
	cmp	r0, r1			@ Compare two parameters 
	bge	else			@ Use opposite logic skip to else

	/* If statements */
	add	r0, r0, 1		@ Add 1 to BCDbits if within range
	b	end_if			@ Branch to end_if

else:
	/* Else Statements */
	mov	r0, 0			@ If not in range, return 0

end_if:
	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore ler into pc for 
					@  return 
	



