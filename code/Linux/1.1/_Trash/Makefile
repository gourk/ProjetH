#g++ Enemy/Enemy.cpp Hero/Hero.cpp Motor/Motor.cpp Object/Object.cpp SDLfont/SDLfont.cpp Main/main.cpp -o test `sdl-config --cflags --libs` -lSDL_ttf

CC=g++
CFLAGS=-Wall
LDFLAGS=`sdl-config --cflags --libs`
EXEC=H

all: main

main: Object.o Enemy.o Hero.o Motor.o SDLfont.o Main.o
	$(CC) $(LDFLAGS) Sortie/Object.o Sortie/Enemy.o Sortie/Hero.o Sortie/Motor.o Sortie/SDLfont.o Sortie/Main.o -o Sortie/$(EXEC) -lSDL_ttf

Object.o: Object/Object.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c Object/Object.cpp -o Sortie/Object.o 

Enemy.o: Enemy/Enemy.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c Enemy/Enemy.cpp -o Sortie/Enemy.o 

Hero.o: Hero/Hero.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c Hero/Hero.cpp -o Sortie/Hero.o 

Motor.o: Motor/Motor.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c Motor/Motor.cpp -o Sortie/Motor.o 

SDLfont.o: SDLfont/SDLfont.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c SDLfont/SDLfont.cpp -o Sortie/SDLfont.o -lSDL_ttf

Main.o: Main/main.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c Main/main.cpp -o Sortie/Main.o 

clean:
	rm -rf Sortie/*.o

mrproper: clean
	rm -rf Sortie/$(EXEC)

