@ Stores 2 integers and passes them to a function
@ that add them and stores the result in r0

@ -------------------------------------------------------
@ DATA SECTION

.data
.balign 4
string: .asciz "\n%d + %d = %d\n"
a:      .word 666
b:      .word 42
c:      .word 0      @ will contain A + B

@ -------------------------------------------------------
@ CODE SECTION

.text
.global main
.extern printf

@ -------------------------------------------------------
@ sumFunc: gets 2 ints in r1 and r2, adds them and 
@          saves result in r0

sumFunc:
    push    {ip, lr}
    add     r0, r1, r2
    pop     {ip, pc}

@ -------------------------------------------------------
@ main: passes 2 ints to sumFunc and prints the resulting sum

main:
    push    {ip, lr}    @ push return addr + dummy reg for alignment
    ldr     r1, =a      @ get address of a into r1
    ldr     r1, [r1]    @ get a into r1
    ldr     r2, =b      @ get address of b into r2
    ldr     r2, [r2]    @ get b into r2

    bl      sumFunc     @ pass (r1, r2) to sumFunc
                        @ gets sum back in r0

    ldr     r2, =c      @ get address of c into r2
    str     r0, [r2]    @ store r0 in c

    @printf (..., r1, r2, r3)

    ldr r0, =string @ get address of string in r0
    ldr r1, =a      @ get address of a into r1
    ldr r1, [r1]    @ get a into r1
    ldr r2, =b      @ get address of b into r2
    ldr r2, [r2]    @ get b into r2
    ldr r3, =c      @ get address of c into r3
    ldr r3, [r3]    @ get c into r3
    bl  printf

    @ return to OS

    pop {ip, pc}

