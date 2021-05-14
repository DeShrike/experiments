@ -------------------------------------------------------
@ See https://www.rose-hulman.edu/class/csse/csse132/1718a/examples/assembly/arm-asm.pdf
@ -------------------------------------------------------
@ CODE SECTION

.text
.global sum_arr_asm

@ -------------------------------------------------------
@ r0 = addr of int array
@ r1 = array length
@ returns sum of ints in r0
sum_arr_asm:
  push {r4-r11, lr}
  mov fp, sp

  mov r5, r1  @ store array length in r5
  mov r1, r0  @ store array address in r1
  mov r2, #0  @ init counter
  mov r0, #0  @ init sum
loop: 
  ldr r4, [r1, #4]!   @ auto-increment ???
  add r0, r0, r4
  add r2, r2, #1
  cmp r2, r5
  ble loop

  mov sp, fp
  pop {r4-r11, pc}
@ -------------------------------------------------------
