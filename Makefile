CC=gcc
CFLAGS=-ansi -pedantic -Wall `pkg-config --cflags gtk+-2.0`
LDLIBS=`pkg-config --libs gtk+-2.0`
OBJ=ucpcal.o date.o

all: ucpcal docs

ucpcal: $(OBJ)
	$(CC) -o ucpcal $(OBJ) $(LDLIBS)

ucpcal.o: ucpcal.c ucpcal.h gui.h date.h event.h list.h
	$(CC) $(CFLAGS) -c -o ucpcal.o ucpcal.c

date.o: date.c date.h
	$(CC) $(CFLAGS) -c -o date.o date.c

gui.o: gui.c gui.h
	$(CC) $(CFLAGS) -c -o gui.o gui.c

docs:
	doxygen Doxyfile

clean:
	rm -rfv $(OBJ) ucpcal docs
