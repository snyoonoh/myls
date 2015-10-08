/* 
 * Filename: displayGroupName.s
 * Author: Seung Yoon Oh
 * Date: Dec 9, 2014
 * Sources of Help:
 */
        .global displayGroupName
	.section ".data"
STR_GNAME:
	.asciz "%-8s "
STR_GID:
	.asciz "%-8ld "
        .section ".text"         

/*
 * Function name: displayGroupName()
 * Function prototype: int displayGroupName( const gid_t gid );
 * Description: This routine will call getgrgid() to get a pointer to the struct
 * group for this gid so we can get the group's name as a string 
 * (gr_name member). If the group entry cannot be found, just print the numeric 
 * value of the gid.
 *       arg1 -- const gid_t gid: the group id 
 * Side Effects: None
 * Error Conditions: None
 * Return Value: prints the gr_name but if there is error, it just prints out
 *               int value of gid
 * Registers Used:
 *      %i0 = gid_t gid
 */

displayGroupName:
        save    %sp,	-96,	%sp
	mov	%i0,	%o0

	call	getgrgid		!call getgrgid
	nop

	cmp	%o0,	%g0
	be	error
	nop

        ld	[%o0],	%l0		!load the result
	set	STR_GNAME,	%o0	!print Group Name if successful
	mov	%l0,	%o1
	call	printf
	nop

	ba	end
	nop

error:
	set	STR_GID,	%o0	!print GID if there was an error
	mov	%i0,	%o1
	call	printf
	nop

end:
	ret
	restore
