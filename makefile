CC=gcc
CFLAGS = -Wall -pedantic -lcurl -lm
rank: rank.o
    $(CC) -o rank rank.c $(CFLAGS)