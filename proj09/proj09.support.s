            .section   ".text"
            .align      4

.global     add                                       ! add function, adds A + B
                                                      ! error conditions (returns 0x80000000)
                                                      ! - overflow
add:

            save        %sp,-96,%sp
            addcc       %i1, %i0, %i0
            bvs         add_overflow
            nop
            ba          done
            nop

add_overflow:                                         ! NZVC V bit is set, error condition
            call        iu_window
            nop                                       ! DEBUG

            ba          error
            nop

.global     sub                                       ! sub function, subtracts A - B
                                                      ! error conditions (returns 0x80000000)
                                                      ! - overflow
sub:
            save        %sp,-96,%sp
            subcc       %i0, %i1, %i0
            bvs         sub_overflow
            nop

            ba          done
            nop


sub_overflow:                                         ! NZVC V bit is set, error condition
            call        iu_window
            nop                                       ! DEBUG

            ba          error
            nop 


.global     absolute                                  ! absolute function
absolute:
            save        %sp,-96,%sp
            
            cmp         %g0, %i0
            bgt         neg_value
            nop
            
            ba          done
            nop

neg_value:
            smulcc      %i0,-1,%i0
            bvs         error
            nop

            ba          done 
            nop


.global     negate                                    ! negate function
negate: 

            save        %sp,-96,%sp

            set         0x80000000, %l7
            cmp         %i0, %l7                      ! check for error condition
            be          error
            nop

            smulcc      %i0,-1,%i0
            bvs         error
            nop

            ba          done 
            nop

.global     mul                                       ! mul function
                                                      ! error conditions (returns 0x80000000)
mul:
            save        %sp,-96,%sp
            smulcc      %i0,%i1,%i0
            bvs         mul_overflow
            nop

            ba          done
            nop

mul_overflow:
            call        iu_window
            nop

            ba          error
            nop

.global     divide                                    ! divide function
                                                      ! error conditions (returns 0x80000000)
divide:
            save        %sp,-96,%sp
            cmp         %i1,%g0
            blt         error                         ! Dividend is 0, illegal operation
            nop

            sdivcc      %i0,%i1,%i0

            ba          done
            nop

.global     remain                                    ! remain function
                                                      ! x - (x/y)*y 
                                                      ! result can be negative
                                                      ! error conditions (returns 0x80000000)
                                                      ! - overflow
                                                      ! - dividend == 0 (divide by 0)
remain:
            save        %sp,-96,%sp

            cmp         %i1,%g0
            blt         error                         ! Dividend is 0, illegal operation
            nop

            sdivcc      %i0,%i1,%l7                   ! %l7 <-- (x/y)
            bvs         error
            nop

            smulcc      %l7,%i1,%l7                   ! %l7 <-- (x/y)*y
            bvs         error
            nop

            subcc       %i0,%l7,%i0                   ! out <-- x - (x/y)*y 
            bvs         error
            nop

            ba          done
            nop


.global     power                                     ! power function
                                                      ! error conditions (returns 0x80000000)
                                                      ! - negative input (specification defined)
power:
            save        %sp,-96,%sp

            cmp         %i0,0
            blt         error 
            nop

            cmp         %i0,1
            be          done
            nop

            cmp         %i1,%g0
            be          is_one
            nop

            cmp         %i1,1
            be          done
            nop

            mov         %i1,%l0                       ! count = exponent
            mov         %i0,%l1                       ! base

power_loop:
            sub         %l0,1,%l0
            cmp         %l0,0
            be          done
            nop

            smulcc      %i0,%l1,%i0                   ! %i0 <-- running_total*x
            bvs         error

            ba          power_loop
            nop

is_one:
            set         0x0000001,%i0                 ! x^0 = 1
            ba          done
            nop

.global     factorial                                 ! factorial function
                                                      ! error conditions (returns 0x80000000)
                                                      ! - negative input (specification defined)
factorial:
            save        %sp,-96,%sp

            cmp         %i0,%g0
            blt         error 
            nop

            mov         %i0,%l0                       ! counter = starting number

factorial_loop:
            cmp         %l0,1
            ble         done
            nop

            sub         %l0,1,%l0                     ! *(n-1)

            smulcc      %i0,%l0,%i0
            bvs         error
            nop

            ba          factorial_loop
            nop

error:                                                ! sets error bit and continues to done
            set         0x80000000, %i0
done:
            ret
            restore


! ADD FORMATTING