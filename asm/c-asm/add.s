@ -------------------------------------------------------
@ DATA SECTION

.data
.balign 4
stringA: .asciz "Address of Array = 0x%X\n"


@ -------------------------------------------------------
@ CODE SECTION

.text
.global add
.global sum_arr
.extern printf

@ -------------------------------------------------------
@ r0 = number 1
@ r1 = number 2
@ returns sum in r0
add:
  push {r4-r11, lr}
  mov fp, sp
  sub sp, sp, #32  @ 32 stack bytes

  add r0, r0, r1

  mov sp, fp
  pop {r4-r11, pc}


@ -------------------------------------------------------
@ r0 = addr of int array
@ r1 = int count
@ returns sum of ints in r0
sum_arr:
  push {r4-r11, lr}
  mov fp, sp
  sub sp, sp, #32  @ 32 stack bytes

  mov r6, r0
  mov r5, r1

  mov r1, r0
  ldr r0, =stringA     @ get address of string in r0
  bl  printf
  
  mov r1, r6
  mov r2, #0
  mov r0, #0
loop: 
  ldr r4, [r1] 
  add r0, r0, r4
  add r2, r2, #1
  add r1, r1, #4
  cmp r2, r5
  bne loop

  mov sp, fp
  pop {r4-r11, pc}

@ -------------------------------------------------------
