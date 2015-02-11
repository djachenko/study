#!/usr/bin/perl

$count = 0;

system("echo \"\" > lab5_F.txt");
system("echo \"\" > lab5_Blas.txt");
system("echo \"\" > lab5_SSE.txt");
system("echo \"\" > lab5_C.txt");

while ($count < 10)
{
	system("./lab5_F >> lab5_F.txt");
	system("./lab5_Blas >> lab5_Blas.txt");
	system("./lab5_SSE >> lab5_SSE.txt");
	system("./lab5_C >> lab5_C.txt");

	$count ++;
}
