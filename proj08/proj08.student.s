		.global main

		.section ".text"
		.align   4

main: 	save 	%sp, -96, %sp

		clr		%r24             ! total count
        clr     %r16             ! number of blanks (0x09, 0x0A and 0x20)
        clr     %r17             ! number of newline characters (0x0A)
        clr     %r18             ! number of decimal digits (in the set {0-9})
        clr     %r19             ! number of hex digits (in the set {0-9,a-f,A-F})
        clr     %r20             ! number of letters (in the set {A-Z,a-z})
        clr     %r21             ! number of upper case letters (in the set {A-Z})
        clr     %r22             ! number of lower case letters (in the set {a-z})
        clr     %r23             ! number of control characters

loop:	call	getchar    	
        nop

if:     cmp     %r8, 0x1F        ! if the character is a control character, inc control
        bgt     check
        nop

then:    inc     %r23
        ba      if1
        nop

check:  cmp     %r8,0x7F         ! esc character checking
        bne     if1              ! not control, continue if/then
        nop

esc:    inc     %r23             ! character is esc, skip to endif
        ba      endif
        nop

if1:    cmp     %r8, 0x20        ! checks for blanks
        be      then1
        nop
        cmp     %r8, 0x0A
        be      then1
        nop
        cmp     %r8, 0x09
        bne     if3              ! skips to check for digits
        nop


then1:  inc     %r16
        cmp     %r8, 0x20
        be      if3              ! skips inc if not newline as well
        nop

then2:  inc     %r17             ! newline character as well as blank


if3:    cmp     %r8,0x30         ! check for digits
        blt     if4
        nop
        cmp     %r8,0x39
        bgt     if4
        nop

then3:  inc     %r18

if4:    cmp     %r8,0x41        ! checks for hex, start at 0x41 <=> A
        blt     if4p2
        nop
        cmp     %r8,0x46
        bgt     if4p2
        nop

then4:  inc     %r19
        ba      if5

if4p2:  cmp     %r8,0x61        ! checks for hex, not in A-F, so check a-f
        blt     if4p3
        nop
        cmp     %r8,0x66
        bgt     if4p3
        nop

the4p2: inc     %r19
        ba      if5
        nop

if4p3:  cmp     %r8,0x30        ! checks for hex, finally check set {0-9}
        blt     if5
        nop
        cmp     %r8,0x39
        bgt     if5
        nop

the4p3: inc     %r19

if5:    cmp     %r8,0x41        ! checks for letters, will also increment %r21 and %r22 for upper/lower resp.
        blt     if5p2
        nop
        cmp     %r8,0x5A
        bgt     if5p2
        nop

then5:  inc     %r20            ! in set {A-Z}
        inc     %r21
        ba      endif
        nop

if5p2:  cmp     %r8,0x61        ! not in set {A-Z}, check {a-z}
        blt     endif
        nop
        cmp     %r8,0x7A
        bgt     endif
        nop

the5p2: inc     %r20            ! in set {a-z}
        inc     %r22

endif:  cmp     %r8, -1
        beq     end
        nop
        
        inc     %r24
		ba		loop
		nop

end:	set 	fmt, %r8        ! end step, print out all the stuff
		mov		%r24, %r9
		call	printf
        nop

        set     fmt1, %r8       ! whitespace characters
        mov     %r16, %r9
        call    printf
		nop

        set     fmt2, %r8       ! newline characters
        mov     %r17, %r9
        call    printf
        nop

        set     fmt3, %r8       ! decimal digits
        mov     %r18, %r9
        call    printf
        nop

        set     fmt4, %r8       ! hex digits
        mov     %r19, %r9
        call    printf
        nop

        set     fmt5, %r8       ! all letters
        mov     %r20, %r9
        call    printf
        nop

        set     fmt6, %r8       ! upper case letters
        mov     %r21, %r9
        call    printf
        nop

        set     fmt7, %r8       ! lower case letters
        mov     %r22, %r9
        call    printf
        nop

        set     fmt8, %r8       ! control characters
        mov     %r23, %r9
        call    printf
        nop




        call    iu_window
        nop

		ret
		restore

fmt:	.asciz	"\ncharacters      = %d\n"
fmt1:   .asciz  "blanks            = %d\n"
fmt2:   .asciz  "newlines          = %d\n"
fmt3:   .asciz  "digits {0-9}      = %d\n"
fmt4:   .asciz  "hex digits        = %d\n"
fmt5:   .asciz  "letters (a-z,A-Z} = %d\n"
fmt6:   .asciz  "upper case        = %d\n"
fmt7:   .asciz  "lower case        = %d\n"
fmt8:   .asciz  "control char      = %d\n"
