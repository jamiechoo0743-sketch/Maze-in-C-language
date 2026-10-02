CC = gcc
CFLAGS = -Wall -ansi -pedantic
OBJ = main.o map.o game.o color.o terminal.o random.o newSleep.o

labyrinth: $(OBJ)
	$(CC) $(OBJ) -o labyrinth

main.o: main.c map.h game.h color.h terminal.h random.h newSleep.h
	$(CC) $(CFLAGS) -c main.c

map.o: map.c map.h
	$(CC) $(CFLAGS) -c map.c

game.o: game.c game.h color.h random.h
	$(CC) $(CFLAGS) -c game.c

color.o: color.c color.h
	$(CC) $(CFLAGS) -c color.c

terminal.o: terminal.c terminal.h
	$(CC) $(CFLAGS) -c terminal.c

random.o: random.c random.h
	$(CC) $(CFLAGS) -c random.c

newSleep.o: newSleep.c newSleep.h
	$(CC) $(CFLAGS) -c newSleep.c

clean:
	rm -f *.o labyrinth
