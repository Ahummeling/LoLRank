CC=gcc
CFLAGS = -Wall -pedantic -lcurl -lm

rank: rank.o json.o
	$(CC) -o rank rank.c json.c $(CFLAGS)
