		.global		absolute
		.global		modulo
		.global		factorial
		.global		power
		.global 	sine

		.section	".text"
		.align		4


absolute:								! DONE, uses fp registers [%f28-%f31]
		save		%sp,-128,%sp

		std 		%f28, [%sp+96]		! Store old Values
		std 		%f30, [%sp+104]

		std			%i0,[%sp+112]		! store parameters (64 bits, so input comes in %i0 and %i1)
		ldd 		[%sp+112], %f30		! double precision value

		set 		-1,%l0				! -1 
		std 		%l0, [%sp+120]
		ld 			[%sp+120], %f28
		fitod 		%f28,%f28			! convert to dp

		fcmpd		%f30,%f28			! jump ahead if greater than -1 (GOOD TILL HERE)
		fbg			not_neg
		nop

		fmuld 		%f30,%f28,%f0		! sp * sp = dp value into %f0

		ldd 		[%sp+96], %f28		! restore old Values
		ldd 		[%sp+104], %f30

		ret
		restore

not_neg:

		fmovd		%f30,%f0

		ret
		restore

modulo:									! DONE EXCEPT FOR INF AND NAN, uses registers [%f22-%f24]
		save		%sp,-128,%sp

		std 		%f22, [%sp+96]		! Store old Values
		std 		%f24, [%sp+104]

		std 		%i0, [%sp+112]		! Get Input params into dp_registers
		ldd 		[%sp+112],%f24		! Param 1

		std			%i2, [%sp+120]
		ldd			[%sp+120], %f22		! Param 2  (WORKS TIL HERE)

		set 		zero,%l0
		ldd			[%l0],%f0

		fcmpd 		%f22,%f0
		fbe			error
		nop

		fdivd		%f24,%f22,%f0  		! divide x by y and store into register %f0
										! CONVERT TO INT AND THEN BACK INTO DOUBLE
		fdtoi		%f0,%f0				! to int
		fitod 		%f0,%f0 			! back to dp, hopefully w/o the trailing stuff
		fmuld 		%f22,%f0,%f0		! multiply by y, store in %f0

		fsubd 		%f24,%f0,%f0 		! subtract from x, return

		ldd 		[%sp+96], %f22		! restore old values
		ldd 		[%sp+104], %f24

		ret 
		restore

factorial:								! DONE, EXCEPT FOR SPECIAL CASES
		save		%sp,-128,%sp

		std 		%f20,[%sp+96]		! store old values
		std 		%f18,[%sp+104]
		std 		%f16,[%sp+112]

		std 		%i0,[%sp+120]		! convert param into dp and store in fp reg
		ldd			[%sp+120], %f20
		fitod 		%f20, %f20

		set 		zero,%l0
		ldd 		[%l0],%f18

		fcmpd 		%f20,%f18			! param is 0
		fbe 		is_zero
		nop

		set 		inf,%l0				
		ldd 		[%l0],%f18

		fcmpd 		%f20,%f18			! param is inf
		fbe 		INF
		nop

		set 		nan,%l0				
		ldd 		[%l0],%f18

		fcmpd 		%f20,%f18			! param is nan
		fbe 		NAN
		nop

		fmovd 		%f20,%f16 			! counter == param

		set 		one,%l0				! the constant 1 into %f18
		ldd 		[%l0],%f18

loop:
		fcmpd 		%f16,%f18
		fble		loop_end
		nop

		fsubd 		%f16,%f18,%f16 		! decrement counter by 1

		fmuld 		%f20,%f16,%f20		! *(n-1)

		ba 			loop
		nop

loop_end:
		fmovd 		%f20,%f0

		ba 			fact_end
		nop

is_zero:
		set 		one,%l0
		ldd 		[%l0],%f20

		fmovd		%f20,%f0 			! argument is 0 => return value 1

fact_end:
		ldd 		[%sp+96],%f20		! restore old values
		ldd 		[%sp+104],%f18

		ret
		restore



power:									! DONE EXCEPT FOR SPECIAL CASES
		save		%sp,-144,%sp

		std 		%f14, [%sp+96]		! Store old Values
		std 		%f12, [%sp+104]
		std 		%f10, [%sp+112]
		std 		%f8, [%sp+120]

		std 		%i0, [%sp+128]		! Get Input params into dp_registers
		ldd 		[%sp+128],%f14		! Param 1

		std			%i2, [%sp+136]
		ldd			[%sp+136], %f12		! Param 2  (WORKS TIL HERE)
		fitod 		%f12,%f12

		call 		dp_registers
		nop

		set 		one,%l0			! check against one on both args
		ldd 		[%l0],%f10		

		fcmpd 		%f14,%f10		! if x is 1, move it to %f0 and return
		fbe 		pow_end
		nop

		fcmpd 		%f12,%f10		! if n is 1, move x to %f0 and return 
		fble 		pow_end
		nop

		fmovd 		%f14,%f0 		! running total

pow_loop:
		fsubd 		%f12, %f10, %f12		! decrement exponent by 1
		fcmpd 		%f12, %f10
		fbl 		pow_end_for_realz
		nop

		fmuld 		%f0,%f14,%f0

		ba 			pow_loop
		nop

pow_end:							! no loop, either base is 1 or exponent is 1 or 0
		set 		zero,%l0			
		ldd 		[%l0],%f10

		fcmpd 		%f12,%f10
		fbe 		is_one
		nop

		fmovd 		%f14,%f0 	

		ba 			pow_end_for_realz
		nop

is_one:
		set 		one,%l0			! x^0 == 1
		ldd 		[%l0],%f0

pow_end_for_realz:
		ldd 		[%sp+96], %f14		! restore old Values
		ldd 		[%sp+104], %f12
		ldd 		[%sp+112], %f10
		ldd 		[%sp+120],%f8

		ret
		restore



sine:									! STUB
		save		%sp,-136,%sp

		std 		%f6, [%sp+96]		! Store old Values
		std 		%f4, [%sp+104]
		std 		%f30, [%sp+112]

		std 		%i0, [%sp+128]		! Get Input params into dp_registers
		ldd 		[%sp+128],%f6		! Param 1

		set 		zero, %l0
		ldd			[%l0], %f4

		fcmpd 		%f4,%f6 			! arg is 0, return x
		fbe 		sine_done
		nop

		set 		nan, %l0
		ldd			[%l0], %f4

		fcmpd 		%f4,%f6 			! arg is NAN, return NAN
		fbe 		NAN
		nop

		set 		inf, %l0
		ldd			[%l0], %f4

		fcmpd 		%f4,%f6 			! arg is +INF, return NAN
		fbe 		INF
		nop

		set 		0, %l0 				! a counter

sine_loop:								! term *= x*x/(2*n*(2*n+1))
										! sum  += n%2 ? -term : term;
										! loop
		smul 		%l0,2,%l1			! 2*n+1 --> %l1
		add 		%l1,1,%l1			

		smul		%l1,%l0,%l1 		! n*(2*n+1) --> %l1
		smul		%l1,2,%l1 			! 2*n*(2*n+1) --> %l1

		ld 			[%l1], %f2 			! store result of above calculations in dp format
		fitod 		%f2, %f2 			! divisor

		fmuld 		%f6,%f6,%f30 		! dividend

		fdivd 		%f30,%f2,%f30 		! x*x/(2*n*(2*n+1)) --> %f30 (TERM)

		set 		sine_acc, %l6			
		ldd			[%l6], %f4

		fcmpd 		%f30, %f4 			! BREAK CONDITION
		fbl 		sine_done
		nop

		mov 		%l0,%i0				! 1st arg to modulo --> n
		set 		2, %i2				! second arg --> 2

		call 		modulo				! should place n%2 in register %f0
		nop

		set 		zero, %l0			
		ldd			[%l0], %f4

		fcmpd 		%f0, %f4 			! even or odd term?
		fbne 		odd_term
		nop

		faddd 		%f6,%f30,%f6			! even n => add term to total

		ba 			sine_loop
		nop

odd_term:
		fsubd 		%f6,%f30,%f6			! odd n => subtract term from total

		ba 			sine_loop
		nop

sine_done:
		fmovd 		%f6,%f0

		ldd 		[%sp+96], %f6		! restore old Values
		ldd 		[%sp+104], %f4
		ldd 		[%sp+112], %f30

		ret
		restore

error:
		set 		0x7ff00000,%i0
		set 		0x00000000,%i1

		std 		%i0,[%sp+96]
		ldd 		[%sp+96], %f0

		ba			end
		nop
INF:
		set 		inf,%l0
		ldd 		[%l0],%f0

		ba 			end
		nop

NAN:
		set 		nan,%l0
		ldd			[%l0],%f0

end:
		ret 
		restore

		.section	".data"
		.align		8

zero:	.double 	0r0
nan: 	.double 	0rnan
one: 	.double 	0r1
inf: 	.double 	0rinf
neg_inf:
		.double 	0r-inf
sine_acc:
		.double 	0r1.0e-9