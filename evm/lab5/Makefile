all: lab5_F lab5_SSE lab5_Blas lab5_C


lab5_F: FMatrix.o lab5_F.o
	g++ -O0 -o lab5_F FMatrix.o lab5_F.o

lab5_F.o: lab5_F.cpp FMatrix.o size.h
	g++ -O0 -c lab5_F.cpp

FMatrix.o: FMatrix.cpp FMatrix.h
	g++ -O0 -c FMatrix.cpp


lab5_SSE: SSEMatrix.o lab5_SSE.o
	g++ -O3 -o lab5_SSE SSEMatrix.o lab5_SSE.o

lab5_SSE.o: lab5_SSE.cpp SSEMatrix.o size.h
	g++ -O3 -c lab5_SSE.cpp

SSEMatrix.o: SSEMatrix.cpp SSEMatrix.h
	g++ -O3 -c SSEMatrix.cpp


lab5_Blas: BlasMatrix.o lab5_Blas.o
	g++ -O3 -o lab5_Blas lab5_Blas.o BlasMatrix.o -lblas -latlas

lab5_Blas.o: lab5_Blas.cpp BlasMatrix.o size.h
	g++ -O3 -c lab5_Blas.cpp

BlasMatrix.o: BlasMatrix.cpp BlasMatrix.h
	g++ -O3 -c BlasMatrix.cpp -lblas -latlas


lab5_C: CMatrix.o lab5_C.o
	g++ -O3 -o lab5_C CMatrix.o lab5_C.o -ftree-vectorize -msse2

lab5_C.o: lab5_F.cpp CMatrix.o size.h
	g++ -O3 -c lab5_F.cpp -o lab5_C.o -ftree-vectorize -msse2

CMatrix.o: FMatrix.cpp FMatrix.h
	g++ -O3 -c FMatrix.cpp -o CMatrix.o -ftree-vectorize -msse2


clean:
	rm *.o lab5_F lab5_SSE lab5_Blas lab5_C
