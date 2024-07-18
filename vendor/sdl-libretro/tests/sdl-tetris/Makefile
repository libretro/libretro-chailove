# Makefile
#PATH = /usr/include/SDL
TARGET = tetris 
OBJECTS = main.o game.o frame.o render.o font.o menu.o sfx.o

CFLAGS = -O3 -Wall -g -I/usr/include/SDL -L/usr/lib -s -DNDEBUG 
LIBS = -lSDL
CC = gcc

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) 


