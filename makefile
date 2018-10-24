CC=gcc
CFLAGS = -Wall -pedantic -lcurl -lm

rank: rank.o cJSON.o
	$(CC) -o rank rank.c cJSON.c $(CFLAGS)
