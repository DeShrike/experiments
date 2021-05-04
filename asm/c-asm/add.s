.text
.global add

add:
  push {r4-r11, lr}
  mov fp, sp
  sub sp, sp, #32  @ 32 stack bytes

  add r0, r0, r1

  mov sp, fp
  pop {r4-r11, pc}


bytes_addr: .word bytes


@ r0 = addr of byte array
@ r1 = byte count
@ returns sum of bytes
get_arr:
  push {r4-r11, lr}
  mov fp, sp

  xor r4,r4
  


  mov sp, fp
  pop {r4-r11, pc}



.data
.balign 4
bytes: .byte 1, 2, 3, 4, 5, 6, 7, 8, 9, 10

