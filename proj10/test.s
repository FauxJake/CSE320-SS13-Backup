	.file	"test.c"
	.section	".rodata"
	.align 8
.LLC0:
	.asciz	"Firstname,_LastName"
	.skip 5
	.section	".text"
	.align 4
	.global main
	.type	main, #function
	.proc	04
main:
	!#PROLOGUE# 0
	save	%sp, -152, %sp
	!#PROLOGUE# 1
	sethi	%hi(.LLC0), %g1
	or	%g1, %lo(.LLC0), %o3
	ldd	[%g1+%lo(.LLC0)], %o4
	std	%o4, [%fp-48]
	ldd	[%o3+8], %o4
	std	%o4, [%fp-40]
	ld	[%o3+16], %g1
	st	%g1, [%fp-32]
	st	%g0, [%fp-28]
	stb	%g0, [%fp-24]
	mov	2, %g1
	st	%g1, [%sp+92]
	mov	88, %o1
	add	%fp, -48, %o2
	mov	12, %o3
	mov	2, %o4
	call	insert, 0
	mov	2, %o5
	ret
	restore %g0, 0, %o0
	.size	main, .-main
	.global .div
	.section	".rodata"
	.align 8
.LLC1:
	.asciz	"\nNUMBER: %d\nNAME:%s\nGAMES: %s\nBASK2: %d\nBASK3: %d\nFREE: %d\nTOTAL: %d\nPPG: %d\n"
	.section	".text"
	.align 4
	.global insert
	.type	insert, #function
	.proc	020
insert:
	!#PROLOGUE# 0
	save	%sp, -136, %sp
	!#PROLOGUE# 1
	ld	[%fp+92], %l1
	add	%i5, %i5, %l0
	add	%l0, %i5, %l0
	add	%l1, %i4, %g1
	add	%g1, %g1, %g1
	add	%l0, %g1, %l0
	sll	%l0, 16, %l0
	sra	%l0, 16, %l0
	mov	%l0, %o0
	call	.div, 0
	mov	%i3, %o1
	st	%o0, [%fp-20]
	ld	[%fp-20], %f9
	fitos	%f9, %f8
	st	%l1, [%sp+92]
	st	%l0, [%sp+96]
	fstod	%f8, %f8
	st	%f8, [%sp+100]
	st	%f9, [%sp+104]
	sethi	%hi(.LLC1), %o0
	or	%o0, %lo(.LLC1), %o0
	mov	%i1, %o1
	mov	%i2, %o2
	mov	%i3, %o3
	mov	%i4, %o4
	call	printf, 0
	mov	%i5, %o5
	nop
	ret
	restore
	.size	insert, .-insert
	.ident	"GCC: (GNU) 3.4.6"
