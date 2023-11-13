DEBUG = -g
OPTS = $(DEBUG) -Wall -ansi -pedantic -std=c++20 

CC=g++ $(OPTS) -c
LN=g++

OBJS = AirportAnimator.o main.o

proj2: $(OBJS)
	$(LN) -o proj2 $(OBJS) -lncurses

main.o: main.cpp AirportAnimator.cpp AirportAnimator.hpp 
	$(CC) main.cpp

AirportAnimator.o: AirportAnimator.cpp AirportAnimator.hpp 
	$(CC) AirportAnimator.cpp

clean:
	/bin/rm -rf *~ $(OBJS) proj2
