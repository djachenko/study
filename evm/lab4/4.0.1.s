	.arch armv5te
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"4.c"
	.section	.rodata
	.align	2
.LC0:
	.ascii	"%d\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	.fnstart
.LFB0:
	@ args = 0, pretend = 0, frame = 200016
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}				положить в стек fp и lr. ! - чтобы указатель обновлялся.
	.save {fp, lr}					создание "описания" регистров, чтобы правильно восстановить
	.setfp fp, sp, #4 				связать описания с местом в sp
	add	fp, sp, #4				fp=sp+4
	.pad #199680					занять место в стеке
	sub	sp, sp, #199680				сдвинуть стек
	.pad #336					еще раз (теперь 200016 байт)
	sub	sp, sp, #336
	ldr	r3, .L11					-200012
	sub	r0, fp, #4				r0=fp+4=sp в прошлом +4
	add	r3, r0, r3				r3=начало стека. в принципе, прям sp
	ldr	r2, .L11+4				r2=размер массива в байтах
	mov	r0, r3					r0=r3=sp+размер+8
	mov	r1, #0					r1=0
	mov	r3, r2					r3=r2=строка+4
	mov	r2, r3					-"-
	bl	memset					вызов. но с какими параметрами?
	mov	r3, #0					r3=0
	str	r3, [fp, #-8]				*(fp-8)=r3
	b	.L2
.L3:
	sub	r3, fp, #199680				r3=fp+199680 (i?) чтение
	sub	r3, r3, #4				r3+=4
	sub	r3, r3, #332				r3+=332. r3==fp+200016==sp
	ldr	r2, [fp, #-8]				r2=i
	mov	r2, r2, asl #2				r2=i*sizeof(int)
	add	r3, r3, r2				r3+=r2. r3==a[i]
	ldr	r0, .L11+8				r0=строка
	mov	r1, r3					r1=a[i]
	bl	scanf					scanf("%d",&a[i])
	ldr	r3, [fp, #-8]				r3=i
	add	r3, r3, #1				r3++
	str	r3, [fp, #-8]				i=r4=i+1
.L2:				внешний цикл
	ldr	r2, [fp, #-8] 				r2=i
	ldr	r3, .L11+12				r3=N 
	cmp	r2, r3					сравнить
	movgt	r3, #0
	movle	r3, #1
	and	r3, r3, #255				
	cmp	r3, #0					сравнить результат сравнения
	bne	.L3					если i<N
	mov	r3, #0					r3=0
	str	r3, [fp, #-8]				i=0
	b	.L4
.L8:			старт внутреннего цикла
	mov	r3, #1					r3=1
	str	r3, [fp, #-12]				j=1?
	b	.L5
.L7:
	ldr	r1, .L11					r1=-200012
	ldr	r3, [fp, #-12]				r3=j
	mov	r3, r3, asl #2				r3=j*sizeof(int)
	sub	ip, fp, #4				ip=fp-4=a+fp
	add	r2, ip, r3				r2=fp-4+r3=&a[j]+fp
	mov	r3, r1					r3=-200012
	add	r3, r2, r3				r3=&a[j] (теперь-то точно хороший адрес)
	ldr	r2, [r3, #0]				r2=a[j]
	ldr	r3, [fp, #-12]				r3=j
	sub	r3, r3, #1				r3=j+1
	ldr	r0, .L11					r0=-200012
	mov	r3, r3, asl #2				
	sub	ip, fp, #4
	add	r1, ip, r3
	mov	r3, r0			
	add	r3, r1, r3
	ldr	r3, [r3, #0]				r3=a[j]
	cmp	r2, r3
	bge	.L6					swap не нужен	
	ldr	r1, .L11					r1=-200012
	ldr	r3, [fp, #-12]				r3=j
	mov	r3, r3, asl #2				r3=j*sizeof(int)
	sub	r0, fp, #4				r0=fp-4=a+x
	add	r2, r0, r3				r2="a+j"
	mov	r3, r1					r3=-200012
	add	r3, r2, r3				r3=&a[j]
	ldr	r3, [r3, #0]				r3=a[j]
	str	r3, [fp, #-16]				"b=a[j]"
	ldr	r3, [fp, #-12]				r3=j
	sub	r3, r3, #1				r3=j+1
	ldr	r1, .L11					r1=-200012
	mov	r3, r3, asl #2				r3=(j+1)*sizeof(int)
	sub	ip, fp, #4				ip=a+fp
	add	r2, ip, r3				r2=&a[j+1]+fp
	mov	r3, r1					r3=-200012
	add	r3, r2, r3				r3=&a[j+1]
	ldr	r2, [r3, #0]				r2=a[j+1]
	ldr	r0, .L11					r0=-200012
	ldr	r3, [fp, #-12]				r3=j
	mov	r3, r3, asl #2				r3=j*sizeof(int)
	sub	ip, fp, #4				ip=a
	add	r1, ip, r3				r1=&a[j]+fp
	mov	r3, r0					r3=r0
	add	r3, r1, r3				r3=&a[j]
	str	r2, [r3, #0]				r2=a[j]
	ldr	r3, [fp, #-12]				r3=j
	sub	r3, r3, #1				r3=j+1
	ldr	r1, .L11					r1=-200012
	mov	r3, r3, asl #2				r3=j*sizeof(int)
	sub	r0, fp, #4				r0=a+fp
	add	r2, r0, r3				r2=&a[j]+fp
	mov	r3, r1					r3=-200012
	add	r3, r2, r3				r3=&a[j]
	ldr	r2, [fp, #-16]				r2=b
	str	r2, [r3, #0]				a[j]=b
.L6:
	ldr	r3, [fp, #-12]
	add	r3, r3, #1			j++
	str	r3, [fp, #-12]
.L5:
	ldr	r2, [fp, #-12] 			r2=j
	ldr	r3, .L11+12			r3=N
	cmp	r2, r3				сравнить
	movgt	r3, #0
	movle	r3, #1
	and	r3, r3, #255			
	cmp	r3, #0
	bne	.L7				запустить тело внутреннего цикла
	ldr	r3, [fp, #-8]
	add	r3, r3, #1			i++
	str	r3, [fp, #-8]
.L4:
	ldr	r2, [fp, #-8]
	ldr	r3, .L11+12
	cmp	r2, r3
	movgt	r3, #0
	movle	r3, #1
	and	r3, r3, #255
	cmp	r3, #0
	bne	.L8				перезапустить цикл по j (с 1)
	mov	r3, #0				
	str	r3, [fp, #-8]			сохранить i
	b	.L9
.L10:
	sub	r3, fp, #199680
	sub	r3, r3, #4
	sub	r3, r3, #332
	ldr	r2, [fp, #-8]
	mov	r2, r2, asl #2
	add	r3, r3, r2
	ldr	r0, .L11+8
	mov	r1, r3
	bl	printf
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L9:
	ldr	r2, [fp, #-8]
	ldr	r3, .L11+12
	cmp	r2, r3
	movgt	r3, #0
	movle	r3, #1
	and	r3, r3, #255
	cmp	r3, #0
	bne	.L10
	mov	r3, #0
	mov	r0, r3
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L12:
	.align	2
.L11:
	.word	-200012
	.word	200000
	.word	.LC0
	.word	49999
	.fnend
	.size	main, .-main
	.ident	"GCC: (Sourcery CodeBench Lite 2012.03-57) 4.6.3"
	.section	.note.GNU-stack,"",%progbits
