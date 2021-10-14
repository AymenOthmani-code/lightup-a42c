CC=gcc
AR=ar
CFLAGS=-std=c99 -Wall -g
CPPFLAGS=-MD -MP
LDFLAGS= -L.
LDLIBS=-lgame

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
DEPENDENCIES = $(SOURCES:.c=.d)

all : game_text

libgame.a : game.o game_aux.o
	ar -r $@ $^

game_text : game_text.o libgame.a
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

-include $(DEPENDENCIES)

.PHONY : clean
clean :
	rm -f game_text libgame.a $(DEPENDENCIES) $(OBJECTS)
