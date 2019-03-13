/*
 * Filename: printChar.s
 * Author: Yishan Li
 * Userid: cs30xdp
 * Description: It will take in a user input and print out that char
 * Date: April 24th 2018
 * Sources of Help: Pushpak Gautam
 */

 @ Raspberry Pi directives
 	.cpu		cortex-a53	@ Version of our Pis
	.syntax		unified		@ Modern syntax  

	.equ		FP_OFFSET, 4	@ Offset to set fp to base of saved regs
	.equ		SP_OFFSET, 8	@ Offset to set sp for local variable

	.section	.rodata 

fmt:	
	.asciz		"%c"
	.global		printChar
	.text			@ Switch to Text segment
	.align	2		@ Align on evenly divisible by 4 byte address;
				@  .align n where 2^n determines alignment
/*
 * Function Name: printChar()
 * Function Prototype: void printChar( char ch );
 * Description: This fuction will takes in a string as parameter, the input
 *              will be a char that is going to fill the bowtie.
 * Parameters: ch - the char that is going to be printed out
 * Side Effects: None
 * Error Conditions: None
 * Return value: Not applicable in this function
 *
 * Registers used: 
 *     r0 - arg 1 -- the ch which is the input string
 *     r1 - arg 2 -- the second argument of printf
 */

printChar:
	@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr on the stack
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
	
	mov	r1, r0			@ Move the input string to r1 as the
					@  actul argument of printf
	ldr	r0, =fmt		@ Loads the string into r0
	bl	printf			@ Call function r0

	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore ler into pc for 
					@  return 
	



