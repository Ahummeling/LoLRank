CC=gcc
CFLAGS = -Wall -pedantic -lcurl -lm

rank: write.o rank.o
	$(CC) -o rank write.c rank.c  $(CFLAGS)
