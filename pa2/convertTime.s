/*
 * Filename: convertTime.s
 * Author: Yishan Li
 * Userid: cs30xdp
 * Description:
 * Date: May 4th 2018
 * Sources of Help: Avinash Kondareddy, Piazza, Lecture Notes 
 */

 @ Raspberry Pi directives
 	.cpu	cortex-a53	@ Version of our Pis
	.syntax	unified		@ Modern syntax  

	.equ	FP_OFFSET, 4	@ Offset to set fp to base of saved regs
	.equ	SP_OFFSET, 12	@ Offset for the sp
	.equ	OURTIME_OFF, -8 @ Offset for the first param ourTime 
	.equ	PTR_OFF, -12	@ Offset for the second param tmPtr
	.equ	HR_LIMIT, 12	@ To determine whether it should be am or pm
	.equ	AM, 65		@ Character 'A'
	.equ	PM, 80		@ Character 'P'

	.global	convertTime
	.text			@ Switch to Text segment
	.align	2		@ Align on evenly divisible by 4 byte address;
				@  .align n where 2^n determines alignment
/*
 * Function Name: convertTime.s
 * Function Prototype: 
 *     void convertTime( struct tInfo * ourTime, const struct tInfo * tmPtr);
 * Description: 
 *     This function will use the time information from tmPtr to converted it
 *     in the ourTime.
 * Parameters: 
 *            ourTime - The tInfo struct pointer to store the converted time 
                        information
 *            tmPtr - the struct that contains the information of time
 * Side Effects: None
 * Error Conditions: None
 * Return value: None
 *
 * Registers used: 
 *                r0 - first param of the function, also for temporarily store
 *                r1 - second param of the function, also for temporarily store
 *                r2 - local variable 
 *                r3 - lcoal variable 
 */

convertTime:
	@ Standard prologue
	push	{fp, lr}		@ Save registers: fp, lr on the stack
	add	fp, sp, FP_OFFSET	@ Set fp to base of saved registers
	add	sp, sp, SP_OFFSET	@ Set sp to the top of structure

	@ Allocate the formal param on RTS
	str	r0, [fp, OURTIME_OFF]	@ Store the ourTime on the RTS
	str	r1, [fp, PTR_OFF]	@ Store the tmPtr on the RTS

	@ Store the value of sec from the struct pointed by tmPtr to ourTime
	ldr	r3,=tm_sec_offset	@ Load memory address of tm_sec_offset
	ldr	r3, [r3]		@ Load the actual value of offset
	ldr	r2, [r1, r3]		@ Get the value of sec to r2

	ldr	r1,=tInfo_secOffset	@ Load memory address of sec in ourTime
	ldr	r1, [r1]		@ Get the actual value of offset
	str	r2, [r0, r1]		@ Store the hour to ourTime
	
	@ Store the value of min from the struct pointed by tmPtr to ourTime
	ldr	r3,=tm_min_offset	@ Load memory address of min
	ldr	r3, [r3]		@ Load value of offset
	ldr	r1, [fp, PTR_OFF]	@ Load the tmPtr
	ldr	r2, [r1,r3]		@ Get the value of min to r2

	ldr	r1,=tInfo_minOffset	@ Load memory address of min 
	ldr	r1, [r1]		@ Get the actual value of offset
	ldr	r0, [fp, OURTIME_OFF]	@ Load ourtime
	str	r2, [r0, r1]		@ Store the value of min to ourTime

	@ Store the value of hour from the struct pointed by tmPtr to ourTime
	ldr	r3,=tm_hour_offset	@ Load memory address of hour
	ldr	r3, [r3]		@ Load the actual value of offset 
	ldr	r1, [fp, PTR_OFF]	@ Load the tmPtr	
	ldr	r2, [r1, r3]		@ Get the value of hour to r2

	mov	r1, HR_LIMIT		@ Move 12 to r1
	cmp	r2, r1			@ tm_hour < 12
	blt	else			@ Opposite logic to branch to over if

	/* If statements for am_pm*/
	mov	r3, PM			@ Move 'P' to r3

	cmp	r2, r1			@ tm_hour != 12
	bne	else_hr			@ Opposite logic to skip over if
	
	/* If statements for hour */
	mov	r2, r1			@ If tm_hour == 12
	b	end_ifhr		@ Branch over else block

else_hr:
	/* Else statements for hour */
	sub	r2, r2, r1		@ tm_hour = tm_hour - 12

end_ifhr:
	
	b	end_if			@ branch over else block for am_pm

else:	
	/* Else statements for am_pm */		
	mov	r3, AM			@ Store 'A' to r3

end_if:
	/* Instructurions following if block */

	ldr	r0, [fp, OURTIME_OFF]	@ Load ourTime to r0
	ldr	r1,=tInfo_hourOffset	@ Load memory address of hour
	ldr	r1, [r1]		@ Get the actual value of offset
	str	r2, [r0, r1]		@ Store the value of hour to ourTime

	@ Store the value of am_pm
	ldr	r1,=tInfo_ampmOffset	@ Load memory address of hour	
	ldr	r1, [r1]		@ Get the actual value of offset
	strb	r3, [r0, r1]		@ Store the am_pm character

	@ Standard epilogue
	sub	sp, fp, FP_OFFSET	@ Set sp to top of saved registers
	pop	{fp, pc}		@ Restore fp; restore ler into pc for 
					@  return 
	



