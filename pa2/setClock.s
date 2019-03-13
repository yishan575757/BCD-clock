/*
 * Filename: setClock.s
 * Author: Yishan Li
 * Userid: cs30xdp
 * Description: It will set the time of the clock array.
 * Date: May 2nd 2018
 * Sources of Help: Eli Qin, Aniket Mathur, lecture notes, Piazza
 */

 @ Raspberry Pi directives
 	.cpu	cortex-a53	@ Version of our Pis
	.syntax	unified		@ Modern syntax  

	.equ	FP_OFFSET, 4	@ Offset to set fp to base of saved regs
	.equ	CLOCK_OFF, -8	@ Offset for the clock[]
	.equ	PTR_OFF, -12	@ Offset for the tmPtr
	.equ	SP_OFFSET, 12	@ Offset for the sp
	.equ	DIVISOR, 10	@ Used to separate the digits								
	.equ	SHIFTL,	4	@ Shift bits

	.global	setClock
	.text			@ Switch to Text segment
	.align	2		@ Align on evenly divisible by 4 byte address;
				@  .align n where 2^n determines alignment
/*
 * Function Name: setClock.s
 * Function Prototype: 
 *         void setClock( unsigned char clock[], const struct tInfo * tmPtr);
 * Description: This function will set the time get from the struct tInfo 
 *              to the clock[] array.
 *             
 * Parameters: 
 *            clock - the array that will store the value of time
 *            tmPtr - the struct that contains the information of time
 * Side Effects: None
 * Error Conditions: None
 * Return value: None
 *
 * Registers used: 
 *                r0 - arg1, also used as the local var to hold the clock 
 *                r1 - arg2, also used as the local var to hold the tmPtr
 *                r2 - local var - used to access the value from struct
 *                                 store the value to array
 *                r3 - local var - used to access the value from struct
 */

setClock:
	@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr on the stack
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
	add	sp, sp, SP_OFFSET	@ Set sp to the top of structure

	str	r0, [fp, CLOCK_OFF]	@ Store the clock[] on the RTS
	str	r1, [fp, PTR_OFF]	@ Store the tmPtr on the RTS

	@ Store the value for hour to array
	ldr	r3,=tInfo_hourOffset	@ Load memory address of 
					@  tInfo_hourOffset
	ldr	r3, [r3]		@ Load tInfo_hourOffset	
	ldr	r2, [r1, r3]		@ Get the value of hour to r2
		
	mov	r3, DIVISOR	
	sdiv	r1, r2, r3		@ Get the tens digit to r1
	mul	r0, r1, r3
	sub	r2, r2, r0		@ Store the ones digit in r2

	lsl	r1, r1, SHIFTL		@ Shift left for four bits 
	orr	r2, r1, r2		@ Set tens digits in upper nibble
					@  and ones digits in lower nibble
	ldr	r0, [fp, CLOCK_OFF]	@ Get the clock array
	strb	r2, [r0, 0]		@ Store the hour to clock[0]
	
	@ Store the value for min to array 
	ldr	r1, [fp, PTR_OFF]	@ Get the tmPtr
	ldr	r3,=tInfo_minOffset	@ Load memory address of 
					@  tInfo_minOffset
	ldr	r3, [r3]		@ Load the actual value of offset
	ldr	r2, [r1, r3]		@ Get the value of min to r2

	mov	r3, DIVISOR
	sdiv	r1, r2, r3		@ Get the tens digit to r1
	mul	r0, r1, r3
	sub	r2, r2, r0		@ Store the ones digit in r2

	lsl	r1, r1, SHIFTL		@ Shift left for four bits 
	orr	r2, r1, r2		@ Set tens digits in upper nibble
					@  and ones digits in lower nibble	
	ldr	r0, [fp, CLOCK_OFF]	@ Get the clock array
	strb	r2, [r0, 1]		@ Store the hour to clock[1]

	@ Store the value for sec to array
	ldr	r1, [fp, PTR_OFF]	@ Get the tmPtr
	ldr	r3,=tInfo_secOffset	@ Load memory address of 
					@  tInfor_secOffset
	ldr	r3, [r3]		@ Load the actual value of offset
	ldr	r2, [r1, r3]		@ Get the value of min to r2
		
	mov	r3, DIVISOR	
	sdiv	r1, r2, r3		@ Get the tens digit to r1
	mul	r0, r1, r3
	sub	r2, r2, r0		@ Store the ones digit in r2
		
	lsl	r1, r1, SHIFTL		@ Shift left for four bits 	
	orr	r2, r1, r2		@ Set tens digits in upper nibble
					@  and ones digits in lower nibble	
	ldr	r0, [fp, CLOCK_OFF]	@ Get the clock array
	strb	r2, [r0, 2]		@ Store the hour to clock[2]

	@ Store the value for am_pm
	ldr	r1, [fp, PTR_OFF]	@ Get the tmPtr
	ldr	r3,=tInfo_ampmOffset	@ Load memory address of 
					@  tInfor_secOffset	
	ldr	r3, [r3]		@ Load the actual value of offset
	ldr	r2, [r1, r3]		@ Get the value of ampm to r2
	
	ldr	r0, [fp, CLOCK_OFF]	@ Get the clock array
	strb	r2, [r0, 3]		@ Store the hour to clock[3]

	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore ler into pc for 
					@  return 
	



