.class public defaultclass
.super java/lang/Object
.method public <init>()V
aload_0
invokespecial java/lang/Object/<init>()V
return
.end method

.method public static print(D)V
.limit locals 5
.limit stack 5
getstatic java/lang/System/out Ljava/io/PrintStream;
dload_0
invokevirtual java/io/PrintStream/println(D)V
return
.end method

.method public static add3(D)D
.limit stack 100
.limit locals 2
dload 0
ldc2_w 3.0
dadd
dreturn
return
.end method

.method public static main()V
.limit stack 100
.limit locals 4
ldc2_w 2.0
dstore 2
ldc2_w 3.0
dstore 0
dload 2
dload 0
dmul
dload 2
dload 0
dadd
dcmpg
iflt IfStart0
goto IfEnd0
IfStart0:
dload 2
dload 0
dadd
invokestatic defaultclass.print(D)V
goto ElseEnd0
IfEnd0:
dload 2
dload 0
dmul
invokestatic defaultclass.print(D)V
ElseEnd0:
return
.end method

.method public static main([Ljava/lang/String;)V
.limit stack 5
.limit locals 5
invokestatic defaultclass.main()V
return
.end method