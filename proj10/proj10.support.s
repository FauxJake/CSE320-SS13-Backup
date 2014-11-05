		.global		search
		.global		delete
		.global		insert

		.section	".text"
		.align		4

search:
		save		%sp,-96,%sp

		set 		1,%i0
		ba			end
		nop

delete:
		save		%sp,-96,%sp

		set 		0,%i0
		ba			end
		nop

insert:
		save		%sp,-112,%sp
		clr			%l0				! points
		clr			%l1				
		set 		25,%l1			! 25 char in name 

		call		iu_window
		nop

		set 	debug, %o0

		umul	%i4, 2, %i4
		umul	%i5, 3, %i5

		add		%i4,%i5,%l0
		ld		[%fp+92],%l1
		add		%l0,%l1,%l7

		! get cap and count
		lduh 	[%i0+0], %l6		! cap
		lduh 	[%i0+2], %l5		! count

		ld 		[%i0+4], %l4		! address of array, use for stuh and st

		st 		%i1, [%l4+0]		! store jersey number
		st 		%i2, [%l4+4]		! Name
		stuh	%i3, [%l4+24]		! Games played
		stuh	%i4, [%l4+28]  		! bask2
		stuh	%i5, [%l4+32]  		! bask3
		stuh	%l1, [%l4+36]  		! free
		stuh	%i7, [%l4+40] 		! total points
		st 		%g0, [%l4+44]		! points per game (needs to be fixed)

		call 	iu_window
		nop

		mov 	%l4,%o0
		set 	0x, %o1
		call	memory
		nop

		set 		0x00022fff,%i0
		ba			end
		nop

end:
		ret
		restore
		
debug:
		.asciz		"\nppg: %d\nTotal Points: %d\nGAMES: %d\nBASK2: %d\nBASK3: %d\n"
