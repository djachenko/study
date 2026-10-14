	.arch armv5te
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 2
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"4.c"
	.section	.text.startup,"ax",%progbits
	.align	2
	.global	main
	.type	main, %function
main:
	.fnstart
.LFB12:
	@ args = 0, pretend = 0, frame = 200000
	@ frame_needed = 0, uses_anonymous_args = 0
	stmfd	sp!, {r4, r5, r6, lr}			сохранение регистров
	.save {r4, r5, r6, lr}
	.pad #199680
	sub	sp, sp, #199680				сдвиг стека
	.pad #320
	sub	sp, sp, #320
	mov	r0, sp					
	mov	r1, #0
	ldr	r2, .L8					размер
	bl	memset
	ldr	r6, .L8+4				N
	mov	r4, #0
.L2:
	add	r5, sp, #0				r5=sp. наверное, а
	add	r1, r5, r4, asl #2			r1=sp+0
	ldr	r0, .L8+8				форматная строка
	bl	scanf
	add	r5, r4, #1				r5=r4+1
	add	ip, sp, #0				ip=sp
	add	r1, ip, r5, asl #2			r1=sp+4
	ldr	r0, .L8+8				
	bl	scanf
	add	r0, r4, #2
	add	r2, sp, #0
	add	r1, r2, r0, asl #2			r1=sp+8
	ldr	r0, .L8+8
	bl	scanf
	add	r1, r4, #3				r1=3
	add	r3, sp, #0
	ldr	r0, .L8+8
	add	r1, r3, r1, asl #2			r1=sp+12=&a[2]
	add	r4, r4, #4				r4+=4
	bl	scanf
	cmp	r4, r6
	bne	.L2					зациклиться. чтение по 4 приема
	mov	r0, #0
	add	sp, sp, #3392				
	add	sp, sp, #196608
	ldmfd	sp!, {r4, r5, r6, pc}
.L9:
	.align	2
.L8:
	.word	200000
	.word	50000
	.word	.LC0
	.fnend
	.size	main, .-main
	.section	.rodata.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"%d\000"
	.ident	"GCC: (Sourcery CodeBench Lite 2012.03-57) 4.6.3"
	.section	.note.GNU-stack,"",%progbits
