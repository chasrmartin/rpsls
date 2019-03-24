# Makefile for my version
PROGRAMS=play referee player
CC=gcc
CFLAGS=-Wno-unused-parameter -DDEBUG
INCLUDES=roshambo.h
roshambo: $(PROGRAMS)
	./play > log
getms.o: getms.c $(INCLUDES)
	$(CC) $(CFLAGS) -c getms.c
pick.o: pick.c $(INCLUDES)
	$(CC) $(CFLAGS) -c pick.c
score.o: score.c $(INCLUDES)
	$(CC) $(CFLAGS) -c score.c
play: play.c $(INCLUDES)
	$(CC) $(CFLAGS) -o play play.c
referee: referee.c score.o $(INCLUDES)
	$(CC) $(CFLAGS) -o referee referee.c score.o 
player: player.c pick.o getms.o $(INCLUDES)
	$(CC) $(CFLAGS) -o player player.c pick.o getms.o
picktest: pick.c getms.o $(INCLUDES)
	$(CC) $(CFLAGS) -DMAIN -o picktest pick.c getms.c && ./picktest 50
clean:
	rm -f log *.o $(PROGRAMS) picktest
