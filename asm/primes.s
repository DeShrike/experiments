.data
primes:
	.word 2
	.word 3
	.word 5
	.word 7

numbers:
	.byte 1, 2, 3, 4, 5
	.hword 20, 56, 45

.align 2
nums:	.word 1, 2, 3, 4

.text
.global main
.global _start
.func main

_start:
main:
	ldr r3, =primes
	ldr r0, [r3, #4]    @ r0 = [r3 + 4]
	ldr r0, [r3, #8]    @ r0 = [r3 + 8]

	ldr r3, =numbers
	ldrb r0, [r3, #1]
	ldrb r0, [r3, #2]
	ldrb r0, [r3, #3]

	ldr r3, =nums
	ldmia r3, {r5-r8}

end:
	mov r7, #1
	swi 0

