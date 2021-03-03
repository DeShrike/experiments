/* Stars */

.data

max_stars    = 50
sizeof_star  = 4
start_x      = 100
delay_ms     = 20
total_frames = 2000

.balign 4

stars:	          .skip sizeof_star * max_stars
next_free_star:   .word stars
star_types:       .asciz "Ox+."
str_draw_star:    .asciz "\033[%d;%dH%c"
str_clear_screen: .asciz "\033[H\033[J"
str_hide_cursor:  .asciz "\033[?25l"
str_show_cursor:  .asciz "\033[?25h"
str_linefeed:     .asciz "\n"

.text

.globl main
.globl printf
.globl usleep
.globl rand

draw_star:
	push {lr}
	ldr  r0,[r0]
	mov  r1, r0, LSR #16
	and  r1, r1, #0xFF
	mov  r2, r0, LSR #24
	and  r3, r0, #0xFF
	ldr  r0, =str_draw_star
	bl   printf
    pop  {lr}
    bx   lr

update_star:
	push {lr}
	ldr  r2, [r0]
	lsl  r1, r2, #16
	asr  r1, r1, #24
	add  r1, r1, r2, LSR #24
	cmp  r1, #1
	bge  _in_limits
_out_of_bonds:
    bl   generate_random_star_values
    b    _update_end
_in_limits:
	and  r2, r2, #0xFFFFFF
	orr  r2, r2, r1, LSL #24
	str  r2, [r0]
_update_end:
    pop {lr}
    bx	lr

generate_random_u8:
	push {r1, r2, r3, lr}
	bl   rand
	and  r0, r0, #0xFF
	pop  {r1, r2, r3, lr}
	bx   lr

generate_new_star:
	push {lr}
	ldr  r2, =next_free_star
	ldr	 r0, [r2]
	cmp  r0, r2
	beq  _do_not_generate
	add  r3, r0, #sizeof_star
	str  r3, [r2]
	bl   generate_random_star_values
_do_not_generate:
    pop  {lr}
    bx   lr

generate_random_star_values:
	push {lr}
	mov  r2, #start_x
	lsl  r2, r2, #24
	push {r0}
	bl   generate_random_u8
	and  r0, r0, #0x3
	ldr  r1, =star_types
	ldr  r1, [r1, r0]
	and  r1, r1, #0xFF
	orr	 r2, r1
	sub  r1, r0, #4
	and  r1, r1, #0xFF
	orr  r2, r2, r1, LSL #8
	bl   generate_random_u8
	and  r1, r0, #0x1F
	and  r1, r1, #1
	orr  r2, r2, r1, LSL #16
	pop  {r0}
	str  r2, [r0]
	pop  {lr}
	bx   lr

main:
	push {r4, r3, r2, r1}
	ldr  r0, =str_hide_cursor
	bl   printf
	mov  r6, #total_frames
_next_frame:
    subs r6, r6, #1
    beq  _frames_ended
    ldr  r0, =str_linefeed
    bl   printf
    mov  r0, #delay_ms
    mov  r0, r0, LSL #10
    bl   usleep
    ldr  r0, =str_clear_screen
    bl   printf
    bl   generate_new_star
    ldr  r4, =stars
    ldr  r5, =next_free_star
    ldr  r5, [r5]
_stars_loop:
    cmp  r4, r5
    beq  _next_frame
    mov  r0, r4
    bl   update_star
    mov  r0, r4
    bl   draw_star
    add  r4, r4, #sizeof_star
    b    _stars_loop

_frames_ended:
    ldr  r0, =str_show_cursor
    bl   printf
    pop	 {r4, r5, r6, lr}
    mov  r0, #0
    bx	 lr

    