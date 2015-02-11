	.file "3.c"
	.code32
	.globl main
	.type main, @function
	.globl __filbuf
	.type __filbuf, @function
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
	push       %ebp				;/ line : 6 запоминание начала стека
	movl       %esp,%ebp				;/ line : 6 кладем в ebp указатель на начало стека (помечаем, где начинаются переменные)
	subl       $200032,%esp				;/ line : 6 сдвиг стека на переменные (20000 на массив и по 16? на i и j)
	andl       $-16,%esp				;/ line : 6 выравнивание?
	push       %ebx				;/ line : отправка в стек неведомо чего из ebx
.CG1.36:
	leal       4(%esp),%ecx				;/ line : 7 загружается первая переменная в регистр (а или i?)
	movl       $.L97,%eax				;/ line : 7 загружаем что-то из L97 в регистр промежуточных данных (адрес массива, не иначе)
	push       $200000				;/ line : 7 кладем в стек размер массива
	push       %eax				;/ line : 7 кладем л97 (адрес массива)
	push       %ecx				;/ line : 7 кладем а?
	call       memcpy				;/ line : 7  копировать кусок стека в объект?
	addl       $12,%esp				;/ line : 7 уменьшить стек? нафига? и зачем на 12?
	xorl       %eax,%eax				;/ line : 12 сносим еах 
	movl       %eax,-32(%ebp)				;/ line : 12 кладем лежащий теперь в еах 0 куда-то в 32 байта от начала стека
	leal       -32(%ebp),%eax				;/ line : 12 а теперь загрузить адрес того, куда положили, в еах?
	movl       (%eax),%eax				;/ line : 12 кладем то, что по адресу еах в еах (а указывает он на положенный в стек 0, взятый из еах.)
	movl       $50000,%ecx				;/ line : 12 загрузка эн в счетчик
	cmpl       %ecx,%eax				;/ line : 12 вычитаем есх из еах. что?
	jge        .CG6.41				;/ line : если не 0, то исполняем
.LP0.56:
.LB0.57:
.CG2.37:
	xorl       %ecx,%ecx				;/ line : 1 ксор сам с собой?4
	leal       __iob(%ecx),%edx				;/ line : 14 прогуглить этот йоб
	movl       (%edx),%eax				;/ line : 14 копируем! содержимое едх в еах
	decl       %eax				;/ line : 14 уменьшить еах. едх не меняется
	movl       %eax,-28(%ebp)				;/ line : 14 грузим еах куда-то в кадр
	leal       -28(%ebp),%eax				;/ line : 14 грузим адрем прогруженного в еах
	movl       (%eax),%eax				;/ line : 14 содержимое еах в еах?
	movl       %eax,(%edx)				;/ line : 14 еах в едх. адрес прогруженного кадра?
	cmpl       %ecx,%eax				;/ line : 14 сравниваем счетчик и адрес кадра, видимо
	jge        .CG4.39				;/ line : 14 такое чувство, что запуск куска
	push       %edx				;/ line : 14 кладем адрес в стек?
	call       __filbuf				;/ line : 14 опять что-то зовется
	addl       $4,%esp				;/ line : 14 сдвигаем стек на один инт
	movl       %eax,-24(%ebp)				;/ line : 14 
	jmp        .CG5.40				;/ line : 14
.CG4.39:
	xorl       %eax,%eax				;/ line : 14 зануление?
	addl       $__iob,%eax				;/ line : 14 загрузка потока ввода в еах?
	movl       $4,%ecx				;/ line : 14 отправка 4 в счетчик
	addl       %ecx,%eax				;/ line : 14 
	movl       (%eax),%ecx				;/ line : 14 загрузка из памяти
	movl       %ecx,-20(%ebp)				;/ line : 14
	incl       %ecx				;/ line : 14
	movl       %ecx,-16(%ebp)				;/ line : 14
	leal       -16(%ebp),%ecx				;/ line : 14
	movl       (%ecx),%ecx				;/ line : 14
	movl       %ecx,(%eax)				;/ line : 14
	leal       -20(%ebp),%eax				;/ line : 14
	movl       (%eax),%eax				;/ line : 14
	movzbl     (%eax),%eax				;/ line : 14
	movzbl     %al,%eax				;/ line : 14
	movl       %eax,-24(%ebp)				;/ line : 14
.CG5.40:
	leal       -24(%ebp),%eax				;/ line : 14
	movl       (%eax),%ecx				;/ line : 14
	leal       -32(%ebp),%eax				;/ line : 14
	movl       (%eax),%eax				;/ line : 14
	leal       (,%eax,4),%edx				;/ line : 14
	movl       %ecx,4(%esp,%edx)				;/ line : 14
	incl       %eax				;/ line : 12
	movl       %eax,-32(%ebp)				;/ line : 12
.LC0.58:
	leal       -32(%ebp),%eax				;/ line : 12
	movl       (%eax),%eax				;/ line : 12
	movl       $50000,%ecx				;/ line : 12
	cmpl       %ecx,%eax				;/ line : 12
	jl         .LB0.57				;/ line : 12
.LX0.59:
.LE0.55:
.CG6.41:
	xorl       %eax,%eax				;/ line : 17 зануление...
	movl       %eax,-32(%ebp)				;/ line : 17 да что там
	leal       -32(%ebp),%eax				;/ line : 17
	movl       (%eax),%eax				;/ line : 17
	movl       $50000,%ecx				;/ line : 17
	cmpl       %ecx,%eax				;/ line : 17
	jge        .CGC.47				;/ line : 17
.LP2.66:
.LB2.67:
.CG7.42:
	movl       $1,%eax				;/ line : 19
	movl       %eax,-12(%ebp)				;/ line : 19
	leal       -12(%ebp),%eax				;/ line : 19
	movl       (%eax),%eax				;/ line : 19
	movl       $50000,%ecx				;/ line : 19
	cmpl       %ecx,%eax				;/ line : 19
	jge        .CGB.46				;/ line : 19
.LP1.61:
.LB1.62:
.CG8.43:
	leal       -12(%ebp),%eax				;/ line : 21
	movl       (%eax),%eax				;/ line : 21
	leal       (,%eax,4),%ecx				;/ line : 21
	movl       4(%esp,%ecx),%edx				;/ line : 21
	decl       %eax				;/ line : 21
	shll       $2,%eax				;/ line : 21
	movl       4(%esp,%eax),%ebx				;/ line : 21
	cmpl       %ebx,%edx				;/ line : 21
	jge        .CGA.45				;/ line : 21
	movl       %edx,-8(%ebp)				;/ line : 23
	movl       %ebx,4(%esp,%ecx)				;/ line : 24
	leal       -8(%ebp),%ecx				;/ line : 25
	movl       (%ecx),%ecx				;/ line : 25
	movl       %ecx,4(%esp,%eax)				;/ line : 25
.CGA.45:
	leal       -12(%ebp),%eax				;/ line : 19
	movl       (%eax),%eax				;/ line : 19
	incl       %eax				;/ line : 19
	movl       %eax,-12(%ebp)				;/ line : 19
.LC1.63:
	leal       -12(%ebp),%eax				;/ line : 19
	movl       (%eax),%eax				;/ line : 19
	movl       $50000,%ecx				;/ line : 19
	cmpl       %ecx,%eax				;/ line : 19
	jl         .LB1.62				;/ line : 19
.LX1.64:
.LE1.60:
.CGB.46:
	leal       -32(%ebp),%eax				;/ line : 17
	movl       (%eax),%eax				;/ line : 17
	incl       %eax				;/ line : 17
	movl       %eax,-32(%ebp)				;/ line : 17
.LC2.68:
	leal       -32(%ebp),%eax				;/ line : 17
	movl       (%eax),%eax				;/ line : 17
	movl       $50000,%ecx				;/ line : 17
	cmpl       %ecx,%eax				;/ line : 17
	jl         .LB2.67				;/ line : 17
.LX2.69:
.LE2.65:
.CGC.47:
	xorl       %eax,%eax				;/ line : 30
	pop        %ebx				;/ line : 30
	leave      				;/ line : 30
	ret        				;/ line : 30
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
