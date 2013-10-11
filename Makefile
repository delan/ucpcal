CC=gcc
CFLAGS=-ansi -pedantic -Wall -g `pkg-config --cflags gtk+-2.0`
LDLIBS=`pkg-config --libs gtk+-2.0`
OBJ=ucpcal.o gui.o date.o event.o list.o

ucpcal: $(OBJ)
	$(CC) -o ucpcal $(OBJ) $(LDLIBS)

ucpcal.o: ucpcal.c ucpcal.h gui.h date.h event.h list.h
	$(CC) $(CFLAGS) -c -o ucpcal.o ucpcal.c

gui.o: gui.c gui.h
	$(CC) $(CFLAGS) -c -o gui.o gui.c

date.o: date.c date.h
	$(CC) $(CFLAGS) -c -o date.o date.c

event.o: event.c event.h date.h
	$(CC) $(CFLAGS) -c -o event.o event.c

list.o: list.c list.h event.h date.h
	$(CC) $(CFLAGS) -c -o list.o list.c

docs:
	doxygen Doxyfile

clean:
	rm -rfv $(OBJ) ucpcal docs *.stackdump
