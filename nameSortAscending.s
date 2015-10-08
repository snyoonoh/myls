/* 
 * Filename: nameSortAscending.s
 * Author: Seung Yoon Oh
 * Userid: cs30xiy
 * Date: Dec 3, 2014
 * Sources of Help:
 */
        .global nameSortAscending    
        .section ".text"         

/*
 * Function name: nameSortAscending()
 * Function prototype: int nameSortAscending( const void* p1, const void* p2 );
 * Description: sorts from low values to high values by name.
 *       arg1 -- const void* p1:
 *       arg2 -- const void* p2:
 * Side Effects: None
 * Error Conditions: None
 * Return Value: 0 if p1 and p2 are equal
 *               1 if p1 is after p2
 *              -1 if p1 is before p2
 *
 * Registers Used:
 *      %o0 - p1
 *      %o1 - p2
 *      %o0 (modified) - p1 + offset
 *      %o1 (modified) - p2 + offset
 *      %o5 - offset
 */

nameSortAscending:
	save	%sp,	-96,	%sp

	mov	%i0,	%o0                     !load p1 
	mov	%i1,	%o1              	!load p2

	call	strcmp				!call strcmp to do the 
	nop					!comparation

	mov	%o0,	%i0

	ret
	restore




