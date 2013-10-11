CC=gcc
CFLAGS=-ansi -pedantic -Wall `pkg-config --cflags gtk+-2.0`
LDLIBS=`pkg-config --libs gtk+-2.0`
OBJ=ucpcal.o

ucpcal: $(OBJ)
	$(CC) -o ucpcal $(OBJ) $(LDLIBS)

ucpcal.o: ucpcal.c ucpcal.h gui.h
	$(CC) -c -o ucpcal.o ucpcal.c

clean:
	rm -fv $(OBJ) ucpcal
