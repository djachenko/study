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
	stmfd	sp!, {r4, r5, r6, r7, lr}		сохранение
	.save {r4, r5, r6, r7, lr}
	.pad #199680
	sub	sp, sp, #199680
	.pad #324
	sub	sp, sp, #324				занять 200004 байта
	mov	r0, sp					
	mov	r1, #0
	ldr	r2, .L42				размер
	bl	memset
	ldr	r7, .L42+4				N
	mov	r5, #0					r5=0
	add	r4, sp, #320				r4=sp+320?
.L2:
	add	lr, sp, #0				адрес возврата. зачем?
	add	r1, lr, r5, asl #2			r1=sp+r5*4
	ldr	r0, .L42+8				форматная строка
	bl	scanf					и так 4 раза...
	add	r6, r5, #1
	add	ip, sp, #0
	add	r1, ip, r6, asl #2			
	ldr	r0, .L42+8
	bl	scanf
	add	r0, r5, #2
	add	r2, sp, #0
	add	r1, r2, r0, asl #2
	ldr	r0, .L42+8
	bl	scanf
	add	r1, r5, #3
	add	r3, sp, #0
	ldr	r0, .L42+8
	add	r1, r3, r1, asl #2
	add	r5, r5, #4				как бы i++ (за все 4 раза сразу)
	bl	scanf
	cmp	r5, r7
	bne	.L2					
	add	r1, sp, #199680
	add	lr, r1, #320				lr=sp+200000
.L3:
	sub	r2, r4, #312				r2=sp+8=&a[3]
	rsb	ip, r4, lr				ip=lr-r4=sp+200000-sp-320=200000-320
	ldr	r1, [r4, #-316]				r1=*(sp+4)=a[1] 
	ldr	r0, [r2, #-8]				r0=*(sp)=a[0]
	add	r6, ip, #312				r6=200 000-8=199 992
	mov	r3, r6, lsr #2				r3=r6*4
	cmp	r1, r0					сравнить a[0] и a[1]
	and	r3, r3, #3				последние два бита? кстати, 0 должен быть. оригинальное зануление?
	strlt	r0, [r2, #-4]				если меньше, то обмен
	strlt	r1, [r2, #-8]
.L14:
	cmp	r2, lr
	beq	.L39					сделается r5-- (j--, наверное)
	cmp	r3, #0
	beq	.L5					
	cmp	r3, #1
	beq	.L35
	cmp	r3, #2
	beq	.L36
	add	r2, r2, #4
	ldr	r6, [r4, #-312]
	ldr	r1, [r2, #-8]
	cmp	r6, r1
	strlt	r1, [r2, #-4]
	strlt	r6, [r2, #-8]
.L36:
	ldr	r0, [r2], #4
	ldr	r3, [r2, #-8]
	cmp	r0, r3
	strlt	r3, [r2, #-4]
	strlt	r0, [r2, #-8]
.L35:
	ldr	r3, [r2], #4				r3=a[base+0], r2=&a[base+1]
	ldr	r1, [r2, #-8]				r1=a[base-1]
	cmp	r3, r1					
	bge	.L29
	b	.L40
.L5:
	mov	r3, r2					r3=r2=a[base+0]
	ldr	ip, [r3], #4				ip=*(r3)=a[base+0], r3=r3+4=&a[base+1]
	ldr	r0, [r3, #-8]				r0=a[base-1]
	mov	r2, r3					r2=&a[base+1]
	cmp	ip, r0					a[base-1] a[base+0]	1
	strlt	r0, [r3, #-4]				swap
	strlt	ip, [r3, #-8]
	ldr	r1, [r2], #4				r1=a[base+1],r2=&a[base+2]
	ldr	r0, [r2, #-8]				r0=a[base+0]
	cmp	r1, r0					a[base+1] и a[base+0]	2
	strlt	r0, [r2, #-4]				again
	strlt	r1, [r2, #-8]
.L25:
	mov	r6, r3					r6=&a[base+1]
	ldr	r0, [r3, #4]				r0=a[base+2]
	ldr	ip, [r6], #8				ip=a[base+1], r6=&a[base+3] (r2==&a[base+2], r3==&a[base+1])
	add	r2, r3, #12				r2=&a[base+4]
	cmp	r0, ip					a[base+2] и a[base+1]	3
	stmltdb	r6, {r0, ip}				..., r6=&a[base+1]
	ldr	r3, [r3, #8]				r3=a[base+3]
	ldr	r1, [r2, #-8]				r1=a[base+2]
	cmp	r3, r1					a[base+2] и a[base+3]
	bge	.L29					перепрыгнуть обмен, если не надо
.L40:
	str	r1, [r2, #-4]
	str	r3, [r2, #-8]
.L29:
	cmp	r2, lr					r2==&a[base+4]
	bne	.L5
.L39:
	subs	r5, r5, #1			i--
	bne	.L3				если рано, то повторить цикл
	ldr	r6, .L42+4			r6=N
	mov	r4, r5				r4=r5 (должно быть 0)
.L6:
	add	r5, sp, #0			
	add	r1, r5, r4, asl #2
	ldr	r0, .L42+8
	bl	printf
	add	r5, r4, #1
	add	ip, sp, #0
	add	r1, ip, r5, asl #2
	ldr	r0, .L42+8
	bl	printf
	add	r3, sp, #0
	add	r0, r5, #1
	add	r1, r3, r0, asl #2
	ldr	r0, .L42+8
	bl	printf
	add	r2, r4, #3
	add	r1, sp, #0
	ldr	r0, .L42+8
	add	r1, r1, r2, asl #2
	add	r4, r4, #4
	bl	printf
	cmp	r4, r6
	bne	.L6
	mov	r0, #0
	add	sp, sp, #324
	add	sp, sp, #199680
	ldmfd	sp!, {r4, r5, r6, r7, pc}
.L43:
	.align	2
.L42:
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
