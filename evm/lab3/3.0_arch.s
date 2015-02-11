	.file "3.c"
	.code64
	.globl main
	.type main, @function
	.local .L93
	.local .L98
	.globl scanf
	.type scanf, @function
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
	.align 16
main:
.CG0:

.CG1:	push       %rbp
.CG2:				;/ line : 6
	movq       %rsp,%rbp
.CG3:				;/ line : 6
	subq       $200016,%rsp				;/ line : 6
.CG1.31:
	leaq       (%rsp),%rdi				;/ line : 7
	leaq       .L93(%rip),%rsi				;/ line : 7
	movq       $200000,%rdx				;/ line : 7 инициализация
	call       memcpy				;/ line : 7
	xorl       %eax,%eax				;/ line : 12
	movl       %eax,-16(%rbp)				;/ line : 12
	leaq       -16(%rbp),%r8				;/ line : 12 r8=&i
	movl       (%r8),%eax				;/ line : 12 eax=i
	movl       $50000,%ecx				;/ line : 12
	cmpl       %ecx,%eax				;/ line : 12
	jge        .CG3.33				;/ line : 12 следующий цикл
.LP0.42:
.LB0.43:
.CG2.32:
	leaq       .L98(%rip),%rdi				;/ line : 14 
	leaq       -16(%rbp),%r8				;/ line : 14 r8=&i
	movl       (%r8),%eax				;/ line : 14 eax=i
	movslq     %eax,%r8				;/ line : 14 r8=i?
	shlq       $2,%r8				;/ line : 14 r8+=sizeof(int)
	xorq       %r9,%r9				;/ line : 14
	subq       %r9,%r8				;/ line : 14
	leaq       (%rsp,%r8),%rsi				;/ line : 14 загрузка куда a+j+1
	xorl       %eax,%eax				;/ line : 14 
	call       scanf				;/ line : 14
	leaq       -16(%rbp),%r8				;/ line : 12
	movl       (%r8),%eax				;/ line : 12
	incl       %eax				;/ line : 12 i++
	movl       %eax,-16(%rbp)				;/ line : 12
.LC0.44:
	leaq       -16(%rbp),%r8				;/ line : 12
	movl       (%r8),%eax				;/ line : 12 eax=i
	movl       $50000,%ecx				;/ line : 12 
	cmpl       %ecx,%eax				;/ line : 12
	jl         .LB0.43				;/ line : 12 repeat
.LX0.45:
.LE0.41:
.CG3.33:
	xorl       %eax,%eax				;/ line : 17 
	movl       %eax,-16(%rbp)				;/ line : 17 i в стеке 0
	leaq       -16(%rbp),%r8				;/ line : 17
	movl       (%r8),%eax				;/ line : 17 eax=0 wtf
	movl       $50000,%ecx				;/ line : 17
	cmpl       %ecx,%eax				;/ line : 17
	jge        .CG9.39				;/ line : 17 return 0
.LP2.52:
.LB2.53:
.CG4.34:
	movl       $1,%eax				;/ line : 19 инициализация цикла по j
	movl       %eax,-12(%rbp)				;/ line : 19
	leaq       -12(%rbp),%r8				;/ line : 19 тудой-сюдой
	movl       (%r8),%eax				;/ line : 19
	movl       $50000,%ecx				;/ line : 19
	cmpl       %ecx,%eax				;/ line : 19
	jge        .CG8.38				;/ line : 19 переход к следующей итерации цикла по i
.LP1.47:
.LB1.48:
.CG5.35:
	leaq       -12(%rbp),%r10				;/ line : 21
	movl       (%r10),%eax				;/ line : 21 eax=j
	movslq     %eax,%r8				;/ line : 21 r8=j
	shlq       $2,%r8				;/ line : 21 r8+=4?
	xorq       %r9,%r9				;/ line : 21 r9=0
	subq       %r9,%r8				;/ line : 21 
	movl       (%rsp,%r8),%ecx				;/ line : 21 ecx=a[j]
	movl       (%r10),%eax				;/ line : 21 eax=j. хоть и не менялось
	decl       %eax				;/ line : 21 eax=j-1
	movslq     %eax,%r8				;/ line : 21
	shlq       $2,%r8				;/ line : 21
	subq       %r9,%r8				;/ line : 21
	movl       (%rsp,%r8),%eax				;/ line : 21 eax=a[j-1]
	cmpl       %eax,%ecx				;/ line : 21 
	jge        .CG7.37				;/ line : 21 в конец
	movl       (%r10),%eax				;/ line : 23 eax=j
	movslq     %eax,%r8				;/ line : 23 r8=j
	shlq       $2,%r8				;/ line : 23
	subq       %r9,%r8				;/ line : 23 
	movl       (%rsp,%r8),%eax				;/ line : 23 eax=a[j]
	movl       %eax,-8(%rbp)				;/ line : 23 b=a[j]
	movl       (%r10),%eax				;/ line : 24 eax=j
	decl       %eax				;/ line : 24 eax=j-1
	movslq     %eax,%r8				;/ line : 24 r8=j-1
	shlq       $2,%r8				;/ line : 24 
	subq       %r9,%r8				;/ line : 24
	movl       (%rsp,%r8),%eax				;/ line : 24 eax=a[j-1]
	leaq       -12(%rbp),%r10				;/ line : 24 
	movl       (%r10),%ecx				;/ line : 24 ecx=j
	movslq     %ecx,%r8				;/ line : 24
	shlq       $2,%r8				;/ line : 24 r8=j
	subq       %r9,%r8				;/ line : 24
	movl       %eax,(%rsp,%r8)				;/ line : 24 a[j]=a[j-1]
	leaq       -8(%rbp),%r8				;/ line : 25
	movl       (%r8),%ecx				;/ line : 25 ecx=b;
	movl       (%r10),%eax				;/ line : 25 eax=j
	decl       %eax				;/ line : 25 eax=j-1
	movslq     %eax,%r8				;/ line : 25
	shlq       $2,%r8				;/ line : 25
	subq       %r9,%r8				;/ line : 25
	movl       %ecx,(%rsp,%r8)				;/ line : 25 a[j-1]=b
.CG7.37:
	leaq       -12(%rbp),%r8				;/ line : 19
	movl       (%r8),%eax				;/ line : 19
	incl       %eax				;/ line : 19 j++
	movl       %eax,-12(%rbp)				;/ line : 19
.LC1.49:
	leaq       -12(%rbp),%r8				;/ line : 19
	movl       (%r8),%eax				;/ line : 19
	movl       $50000,%ecx				;/ line : 19 
	cmpl       %ecx,%eax				;/ line : 19 j<N
	jl         .LB1.48				;/ line : 19 repeat
.LX1.50:
.LE1.46:
.CG8.38:
	leaq       -16(%rbp),%r8				;/ line : 17 
	movl       (%r8),%eax				;/ line : 17
	incl       %eax				;/ line : 17 i++
	movl       %eax,-16(%rbp)				;/ line : 17
.LC2.54:
	leaq       -16(%rbp),%r8				;/ line : 17
	movl       (%r8),%eax				;/ line : 17
	movl       $50000,%ecx				;/ line : 17
	cmpl       %ecx,%eax				;/ line : 17 i<N
	jl         .LB2.53				;/ line : 17 repeat
.LX2.55:
.LE2.51:
.CG9.39:
	xorl       %eax,%eax				;/ line : 30
	leave      				;/ line : 30
	ret        				;/ line : 30
.CG4:
	.size main, . - main


	.section .data,"aw"
Ddata.data: / Offset 0



	.section .bss,"aw"
Bbss.bss:


	.section .bssf,"aw"


	.section .rodata,"a"
	.align 8
.L93: / Offset 0
	.type .L93, @object
	.size .L93, 200000

	.zero 200000
Drodata.rodata: / Offset 200000



	.section .rodata1,"a"
	.align 8
.L98: / Offset 0
	.type .L98, @object
	.size .L98, 3

	.2byte 0x6425
	.zero 1


	.section .eh_frame,"aL",link=.text,@unwind
.Lframe1:
	.long	.LECIE1-.LBCIE1
.LBCIE1:
	.long	0x0
	.byte	0x1
	.string	""
	.uleb128	0x1
	.sleb128	-8
	.byte	0x10
	.byte	0xc
	.uleb128	0x7
	.uleb128	0x8
	.byte	0x90
	.uleb128	0x1
	.byte	0x8
	.byte	0x3
	.byte	0x8
	.byte	0x6
	.byte	0x8
	.byte	0xc
	.byte	0x8
	.byte	0xd
	.byte	0x8
	.byte	0xe
	.byte	0x8
	.byte	0xf
	.align 8
.LECIE1:
	.long	.LEFDE0-.LBFDE0
.LBFDE0:
	.long	.LBFDE0-.Lframe1
	.quad	.CG0
	.quad	.CG4-.CG0
	.cfa_advance_loc	.CG2-.CG1
	.byte	0xe
	.uleb128	0x10
	.byte	0x86
	.uleb128	0x2
	.cfa_advance_loc	.CG3-.CG2
	.byte	0xd
	.uleb128	0x6
	.align	8
.LEFDE0:

/  Begin sdCreateSection : .debug_info
/  Section Info: link_name/strtab=, entsize=0x1, adralign=0x1, flags=0x0
/  Section Data Blocks:
/   reloc[0]: knd=2, off=14, siz=8, lab1=.debug_abbrev, lab2=, loff=0
/   reloc[1]: knd=2, off=194, siz=8, lab1=.debug_line, lab2=, loff=0
	.section .debug_info
	.byte 0xff,0xff,0xff,0xff,0xc0,0x00,0x00,0x00
	.byte 0x00,0x00,0x00,0x00,0x02,0x00
	.8byte .debug_abbrev
	.byte 0x08,0x01,0x00,0x00,0x00,0x00,0x00,0x00
	.byte 0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00
	.byte 0x00,0x00,0x33,0x2e,0x63,0x00,0x0c,0x2f
	.byte 0x68,0x6f,0x6d,0x65,0x2f,0x73,0x74,0x75
	.byte 0x64,0x65,0x6e,0x74,0x73,0x2f,0x31,0x32
	.byte 0x30,0x78,0x2f,0x64,0x79,0x61,0x63,0x68
	.byte 0x65,0x6e,0x6b,0x6f,0x2f,0x65,0x76,0x6d
	.byte 0x2f,0x6c,0x61,0x62,0x33,0x00,0x20,0x2f
	.byte 0x6f,0x70,0x74,0x2f,0x53,0x55,0x4e,0x57
	.byte 0x73,0x70,0x72,0x6f,0x2f,0x70,0x72,0x6f
	.byte 0x64,0x2f,0x62,0x69,0x6e,0x2f,0x63,0x63
	.byte 0x20,0x2d,0x78,0x4f,0x30,0x20,0x2d,0x78
	.byte 0x61,0x72,0x63,0x68,0x3d,0x61,0x6d,0x64
	.byte 0x36,0x34,0x61,0x20,0x2d,0x53,0x20,0x20
	.byte 0x33,0x2e,0x63,0x00,0x58,0x61,0x3b,0x52
	.byte 0x3d,0x53,0x75,0x6e,0x20,0x43,0x20,0x35
	.byte 0x2e,0x38,0x20,0x32,0x30,0x30,0x35,0x2f
	.byte 0x31,0x30,0x2f,0x31,0x33,0x3b,0x62,0x61
	.byte 0x63,0x6b,0x65,0x6e,0x64,0x3b,0x72,0x61
	.byte 0x77,0x3b,0x63,0x64,0x3b,0x00,0x44,0x42
	.byte 0x47,0x5f,0x47,0x45,0x4e,0x20,0x35,0x2e
	.byte 0x30,0x2e,0x38,0x00
	.8byte .debug_line
	.byte 0x00,0x00
/  End sdCreateSection
/  Begin sdCreateSection : .debug_line
/  Section Info: link_name/strtab=, entsize=0x1, adralign=0x1, flags=0x0
/  Section Data Blocks:
	.section .debug_line
	.byte 0xff,0xff,0xff,0xff,0x48,0x00,0x00,0x00
	.byte 0x00,0x00,0x00,0x00,0x02,0x00,0x3e,0x00
	.byte 0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00
	.byte 0xff,0x04,0x0a,0x00,0x01,0x01,0x01,0x01
	.byte 0x00,0x00,0x00,0x01,0x2f,0x68,0x6f,0x6d
	.byte 0x65,0x2f,0x73,0x74,0x75,0x64,0x65,0x6e
	.byte 0x74,0x73,0x2f,0x31,0x32,0x30,0x78,0x2f
	.byte 0x64,0x79,0x61,0x63,0x68,0x65,0x6e,0x6b
	.byte 0x6f,0x2f,0x65,0x76,0x6d,0x2f,0x6c,0x61
	.byte 0x62,0x33,0x00,0x00,0x33,0x2e,0x63,0x00
	.byte 0x01,0x00,0x00,0x00
/  End sdCreateSection
/  Begin sdCreateSection : .debug_abbrev
/  Section Info: link_name/strtab=, entsize=0x1, adralign=0x1, flags=0x0
/  Section Data Blocks:
	.section .debug_abbrev
	.byte 0x01,0x11,0x00,0x11,0x01,0x12,0x01,0x03
	.byte 0x08,0x13,0x0b,0x1b,0x08,0x85,0x44,0x08
	.byte 0x87,0x44,0x08,0x25,0x08,0x10,0x07,0x00
	.byte 0x00,0x00
/  End sdCreateSection
