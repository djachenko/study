	.file "3.c"
	.code32
	.globl main
	.type main, @function
	.globl scanf
	.type scanf, @function
	.local .L102
	.local .L97
	.globl __fsr_init_value
__fsr_init_value = 0

	.ident     "@(#)stdio.h\t1.84\t04/09/28 SMI"
	.ident     "@(#)feature_tests.h\t1.25\t07/02/02 SMI"
	.ident     "@(#)ccompile.h\t1.2\t04/11/08 SMI"
	.ident     "@(#)isa_defs.h\t1.28\t07/02/01 SMI"
	.ident     "@(#)stdio_iso.h\t1.8\t05/08/16 SMI"
	.ident     "@(#)va_list.h\t1.15\t04/11/19 SMI"
	.ident     "@(#)stdio_tag.h\t1.4\t04/09/28 SMI"
	.ident     "@(#)stdio_impl.h\t1.15\t07/03/05 SMI"
	.ident     "@(#)stdio_c99.h\t1.2\t04/03/29 SMI"
	.ident     "acomp: Sun C 5.8 2005/10/13"
	.ident     "ir2hf: Sun Compiler Common 11 2005/10/13"
	.ident     "ube: Sun Compiler Common 11 2005/10/13"

	.section .text,"ax"
	.align 4
main:
	push       %ebp				;/ line : сохранить значение ебп
	movl       %esp,%ebp				;/ line : 6 отмечаем в ебп начало куска для переменных
	subl       $200016,%esp				;/ line : 6 сдвигаем стек на кусок, достаточный для переменных (20 000 на массив и )
	andl       $-16,%esp				;/ line : 6 
	push       %ebx				;/ line : 6 запомнить ебх
.CG1.31:
	leal       4(%esp),%ecx				;/ line : 7 загружаем в ецх адрес сдвига от начала стека на 4
	movl       $.L97,%eax				;/ line : 7 в еах грузится адрес объекта с нулями
	push       $200000				;/ line : 7 зачем-то за
	push       %eax				;/ line : 7
	push       %ecx				;/ line : 7
	call       memcpy				;/ line : 7 и грузим эти нули в кусок для массива
	addl       $12,%esp				;/ line : 7 зачем?
	
	;/цикл
	xorl       %eax,%eax				;/ line : 12 i
	movl       %eax,-16(%ebp)				;/ line : 12 зануление переменной
	leal       -16(%ebp),%eax				;/ line : 12 загрузка ее адреса в еах
	movl       (%eax),%eax				;/ line : 12 а теперь загрузка ее самой в еах (хотя там все равно 0)
	movl       $50000,%ecx				;/ line : 12 N в счетчик
	cmpl       %ecx,%eax				;/ line : 12 сравнить
	jge        .CG3.33				;/ line : 12 если еах(i) больше либо равен счетчику прыгнуть на второй цикл
.LP0.42:
.LB0.43:
.CG2.32:
	movl       $.L102,%ecx				;/ line : 14 в есх адрес объекта (форматной строки)
	leal       -16(%ebp),%eax				;/ line : 14 загружаем адрес i в еах
	movl       (%eax),%eax				;/ line : 14 теперь саму i
	shll       $2,%eax				;/ line : 14 умножение на 4 (ибо сдвиг два раза)
	leal       4(%esp,%eax),%eax				;/ line : 14 загрузка адреса a[eax] в еах
	push       %eax				;/ line : 14 в стек
	push       %ecx				;/ line : 14 кладем адрес форматной строки
	call       scanf				;/ line : 14 записываем куда надо
	addl       $8,%esp				;/ line : 14 спихивать стек ЕЩЕ НА 8?
	leal       -16(%ebp),%eax				;/ line : 12 грузим адрес i
	movl       (%eax),%eax				;/ line : 12 значение
	incl       %eax				;/ line : 12 ++
	movl       %eax,-16(%ebp)				;/ line : 12 выгружаем
.LC0.44:
	leal       -16(%ebp),%eax				;/ line : 12
	movl       (%eax),%eax				;/ line : 12
	movl       $50000,%ecx				;/ line : 12
	cmpl       %ecx,%eax				;/ line : 12 проверка условия
	jl         .LB0.43				;/ line : 12 зачем-то прыжок на метку выше. но все равно сработает
.LX0.45:
.LE0.41:
.CG3.33: как бы шаблон счетчика
	xorl       %eax,%eax				;/ line : 17 зануляем еах (итератор)
	movl       %eax,-16(%ebp)				;/ line : 17 грузим этот ноль в место для переменной 
	leal       -16(%ebp),%eax				;/ line : 17 жонглируем адресами
	movl       (%eax),%eax				;/ line : 17 приходя к исходному
	movl       $50000,%ecx				;/ line : 17 N в счетчик
	cmpl       %ecx,%eax				;/ line : 17 сравниваем
	jge        .CG9.39				;/ line : 17 и по окончании переходим в return 0
.LP2.52:
.LB2.53:
.CG4.34:
	movl       $1,%eax				;/ line : 19 цикл по жи. то же самое
	movl       %eax,-12(%ebp)				;/ line : 19
	leal       -12(%ebp),%eax				;/ line : 19
	movl       (%eax),%eax				;/ line : 19
	movl       $50000,%ecx				;/ line : 19
	cmpl       %ecx,%eax				;/ line : 19
	jge        .CG8.38				;/ line : 19
.LP1.47:
.LB1.48:
.CG5.35:
	leal       -12(%ebp),%eax				;/ line : 21  загрузка j
	movl       (%eax),%eax				;/ line : 21
	leal       (,%eax,4),%ecx				;/ line : 21 ecx=j*sizeof(int)
	movl       4(%esp,%ecx),%edx				;/ line : 21 загрузка a[j]
	decl       %eax				;/ line : 21 j--
	shll       $2,%eax				;/ line : 21 j*sizeof(int)
	movl       4(%esp,%eax),%ebx				;/ line : 21 a[j-1]
	cmpl       %ebx,%edx				;/ line : 21 сравниваем
	jge        .CG7.37				;/ line : 21 если не надо, перепрыгиваем обмен
	movl       %edx,-8(%ebp)				;/ line : 23 edx=j;
	movl       %ebx,4(%esp,%ecx)				;/ line : 24 a[j]=a[j-1]
	leal       -8(%ebp),%ecx				;/ line : 25 ecx=&c;
	movl       (%ecx),%ecx				;/ line : 25  ecx=c
	movl       %ecx,4(%esp,%eax)				;/ line : 25 a[j-1=c
.CG7.37:
	leal       -12(%ebp),%eax				;/ line : 19
	movl       (%eax),%eax				;/ line : 19
	incl       %eax				;/ line : 19				j++
	movl       %eax,-12(%ebp)				;/ line : 19
.LC1.49:
	leal       -12(%ebp),%eax				;/ line : 19
	movl       (%eax),%eax				;/ line : 19
	movl       $50000,%ecx				;/ line : 19
	cmpl       %ecx,%eax				;/ line : 19 сравнение
	jl         .LB1.48				;/ line : 19 если рано, то возврат к началу
.LX1.50:
.LE1.46:
.CG8.38:
	leal       -16(%ebp),%eax				;/ line : 17
	movl       (%eax),%eax				;/ line : 17
	incl       %eax				;/ line : 17 ++ для внешнего цикла
	movl       %eax,-16(%ebp)				;/ line : 17
.LC2.54:
	leal       -16(%ebp),%eax				;/ line : 17
	movl       (%eax),%eax				;/ line : 17
	movl       $50000,%ecx				;/ line : 17
	cmpl       %ecx,%eax				;/ line : 17 сравнение i с N
	jl         .LB2.53				;/ line : 17  
.LX2.55:
.LE2.51:
.CG9.39: return 0
	xorl       %eax,%eax				;/ line : 30 зануляем регистр
	pop        %ebx				;/ line : 30  вытаскиваем начальное значение ебх
	leave      				;/ line : 30 восстановление указателей
	ret        				;/ line : 30 возврат
	.size main, . - main


	.section .data,"aw"
Ddata.data: / Offset 0



	.section .bss,"aw"
Bbss.bss:


	.section .bssf,"aw"


	.section .rodata,"a"
	.align 8
.L97: / Offset 0
	.type .L97, @object
	.size .L97, 200000

	.zero 200000
Drodata.rodata: / Offset 200000



	.section .rodata1,"a"
	.align 4
.L102: / Offset 0
	.type .L102, @object
	.size .L102, 3

	.2byte 0x6425
	.zero 1

/  Begin sdCreateSection : .debug_info
/  Section Info: link_name/strtab=, entsize=0x1, adralign=0x1, flags=0x0
/  Section Data Blocks:
/   reloc[0]: knd=2, off=6, siz=4, lab1=.debug_abbrev, lab2=, loff=0
/   reloc[1]: knd=2, off=160, siz=4, lab1=.debug_line, lab2=, loff=0
	.section .debug_info
	.byte 0xa4,0x00,0x00,0x00,0x02,0x00
	.4byte .debug_abbrev
	.byte 0x04,0x01,0x00,0x00,0x00,0x00,0x04,0x00
	.byte 0x00,0x00,0x33,0x2e,0x63,0x00,0x0c,0x2f
	.byte 0x68,0x6f,0x6d,0x65,0x2f,0x73,0x74,0x75
	.byte 0x64,0x65,0x6e,0x74,0x73,0x2f,0x31,0x32
	.byte 0x30,0x78,0x2f,0x64,0x79,0x61,0x63,0x68
	.byte 0x65,0x6e,0x6b,0x6f,0x2f,0x65,0x76,0x6d
	.byte 0x2f,0x6c,0x61,0x62,0x33,0x00,0x20,0x2f
	.byte 0x6f,0x70,0x74,0x2f,0x53,0x55,0x4e,0x57
	.byte 0x73,0x70,0x72,0x6f,0x2f,0x70,0x72,0x6f
	.byte 0x64,0x2f,0x62,0x69,0x6e,0x2f,0x63,0x63
	.byte 0x20,0x2d,0x78,0x4f,0x30,0x20,0x2d,0x53
	.byte 0x20,0x20,0x33,0x2e,0x63,0x00,0x58,0x61
	.byte 0x3b,0x52,0x3d,0x53,0x75,0x6e,0x20,0x43
	.byte 0x20,0x35,0x2e,0x38,0x20,0x32,0x30,0x30
	.byte 0x35,0x2f,0x31,0x30,0x2f,0x31,0x33,0x3b
	.byte 0x62,0x61,0x63,0x6b,0x65,0x6e,0x64,0x3b
	.byte 0x72,0x61,0x77,0x3b,0x63,0x64,0x3b,0x00
	.byte 0x44,0x42,0x47,0x5f,0x47,0x45,0x4e,0x20
	.byte 0x35,0x2e,0x30,0x2e,0x38,0x00
	.4byte .debug_line
	.byte 0x00,0x00,0x00,0x00
/  End sdCreateSection
/  Begin sdCreateSection : .debug_line
/  Section Info: link_name/strtab=, entsize=0x1, adralign=0x1, flags=0x0
/  Section Data Blocks:
	.section .debug_line
	.byte 0x44,0x00,0x00,0x00,0x02,0x00,0x3e,0x00
	.byte 0x00,0x00,0x01,0x00,0xff,0x04,0x0a,0x00
	.byte 0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x01
	.byte 0x2f,0x68,0x6f,0x6d,0x65,0x2f,0x73,0x74
	.byte 0x75,0x64,0x65,0x6e,0x74,0x73,0x2f,0x31
	.byte 0x32,0x30,0x78,0x2f,0x64,0x79,0x61,0x63
	.byte 0x68,0x65,0x6e,0x6b,0x6f,0x2f,0x65,0x76
	.byte 0x6d,0x2f,0x6c,0x61,0x62,0x33,0x00,0x00
	.byte 0x33,0x2e,0x63,0x00,0x01,0x00,0x00,0x00
/  End sdCreateSection
/  Begin sdCreateSection : .debug_abbrev
/  Section Info: link_name/strtab=, entsize=0x1, adralign=0x1, flags=0x0
/  Section Data Blocks:
	.section .debug_abbrev
	.byte 0x01,0x11,0x00,0x11,0x01,0x12,0x01,0x03
	.byte 0x08,0x13,0x0b,0x1b,0x08,0x85,0x44,0x08
	.byte 0x87,0x44,0x08,0x25,0x08,0x10,0x06,0x00
	.byte 0x00,0x00
/  End sdCreateSection
