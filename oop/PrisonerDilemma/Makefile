PrisonerDilemma: PrisonerDilemma.o Judge.o Prisoner.o History.o Strategy.o AngryStrategy.o KindStrategy.o RandomStrategy.o
	g++ -o PrisonerDilemma PrisonerDilemma.o Judge.o Prisoner.o History.o Strategy.o AngryStrategy.o KindStrategy.o RandomStrategy.o

PrisonerDilemma.o: PrisonerDilemma.cpp Factory.h Prisoner.h KindStrategy.h AngryStrategy.h RandomStrategy.h
	g++ -c PrisonerDilemma.cpp

Judge.o: Judge.h Judge.cpp Prisoner.h
	g++ -c Judge.cpp

Prisoner.o: Prisoner.h Prisoner.cpp Strategy.h History.h Factory.h
	g++ -c Prisoner.cpp

History.o: History.h History.cpp
	g++ -c History.cpp

Strategy.o: Strategy.h Strategy.cpp History.h
	g++ -c Strategy.cpp

AngryStrategy.o: AngryStrategy.h AngryStrategy.cpp Strategy.h
	g++ -c AngryStrategy.cpp

KindStrategy.o: KindStrategy.h KindStrategy.cpp Strategy.h
	g++ -c KindStrategy.cpp

RandomStrategy.o: RandomStrategy.h RandomStrategy.cpp Strategy.h
	g++ -c RandomStrategy.cpp

clean:
	rm *.o PrisonerDilemma
