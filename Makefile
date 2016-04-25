CC=gcc
CFLAGS=-Wall
EXEC=render
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
DEPS = parser.h
INCLUDES =-I/usr/include/libxml2/ -I/usr/include/SDL
LIBS=-lxml2 -lSDL -lSDL_ttf

all: $(EXEC)

%.o: %.c
	 $(CC) $(CFLAGS) -c $(INCLUDES) $<

render: $(OBJ) 
	$(CC) $(INCLUDES) -o $@ $^ $(LIBS)

parser.o : parser.h
render_engine.o : render_engine.h
drawer.o : drawer.h
render.o : render.h

clean :
	rm -rf *.o
	rm -rf *~
	rm -rf \#*

mrproper: clean
	rm -rf $(EXEC)
