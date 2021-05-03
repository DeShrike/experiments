@ ARM Stacks

.text
.global main
.global _start

_start:
main:
   bl hello_world

   mov r7, #3	@ input
   mov r0, #0	@ stdin
   mov r2, #10	@ length to read
   ldr r1, =msg1
   swi 0

   bl hello_world

   mov r1, #10
   mov r2, #20
   mov r3, #30
   mla r0, r1, r2, r3	@ r0 = (r1 * r2) + r3

   mov r1, #15
   mov r0, r1, lsl #1	@ r0 = r1 << 1
   mov r0, r1, lsr #1	@ r0 = r1 >> 1


   bl exit


hello_world:
   push {r4-r11, lr}
   mov fp, sp
   sub sp, sp, #0x40  @ 64 bytes stack space for local data
   ldr r1, =#0x1337
   str r1, [fp, #-0x10]

   mov r7, #4	@ write to screen
   mov r0, #1	@ stdout
   ldr r1, =msg1
   mov r2, #32	@ length of string
   swi 0

   mov sp, fp
   pop {r4-r11, pc}

exit:
   push {fp, lr}
   mov r7, #1	@ exit to terminal
   mov r0, #65	@ return value: ./hello ; echo $?
   swi 0
   pop {fp, pc}

addr_msg2: .word msg2

.data
.balign 4
msg1: 	.ascii "Hello World ! \nThis is line 2.\n"
a:	.word 33
b:	.word 44
c:	.word 0
msg2:	.asciz "NULL terminated string \n"
