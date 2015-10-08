/* 
 * Filename: sizeSortAscending.s
 * Author: Seung Yoon Oh
 * Userid: cs30xiy
 * Date: Dec 3, 2014
 * Sources of Help:
 */
        .global sizeSortAscending    
        .section ".text"         

/*
 * Function name: sizeSortAscending()
 * Function prototype: int sizeSortAscending( const void* p1, const void* p2 );
 * Description: sorts from low values to high values by size
 *       arg1 -- const void* p1: struct fileInfo pointer
 *       arg2 -- const void* p2: struct fileInfo pointer
 * Side Effects: None
 * Error Conditions: None
 * Return Value: 0 if p1 and p2 are equal
 *               positive if p1 is after p2
 *               negative if p1 is before p2
 *
 * Registers Used:
 *      %o0 - p1
 *      %o1 - p2
 *      %o0 (modified) - p1 + offset
 *      %o1 (modified) - p2 + offset
 *      %o5 - offset
 */

sizeSortAscending:
        set     offset,         %o5             !put offset to %o5
        ld      [%o5],          %o5
	ld	[%o0 + %o5],	%o0             !load p1 with offset (st_size)
	ld	[%o1 + %o5],	%o1             !load p2 with offset (st_size)

        sub     %o0,    %o1,    %o0             !subtract to get return value
                                                !similiar to qsort()

	retl					!return leaf
	nop
