NAME = grid

all: 1 2 3

1: $(NAME)1.out

2: $(NAME)2.out

3: $(NAME)3.out

$(NAME)1.out: $(NAME)1.cpp
	mpicxx -o $(NAME)1.out $(NAME)1.cpp

$(NAME)2.out: $(NAME)2.cpp
	mpicxx -o $(NAME)2.out $(NAME)2.cpp

$(NAME)3.out: $(NAME)3.cpp
	mpicxx -o $(NAME)3.out $(NAME)3.cpp

clean:
	rm *.out *.bin
