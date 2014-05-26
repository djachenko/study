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
.limit locals 6
ldc2_w 7.0
dstore 2
dload 2
invokestatic defaultclass.print(D)V
ldc2_w 5.0
dstore 2
dload 2
invokestatic defaultclass.print(D)V
return
.end method

.method public static main([Ljava/lang/String;)V
.limit stack 5
.limit locals 5
invokestatic defaultclass.main()V
return
.end method