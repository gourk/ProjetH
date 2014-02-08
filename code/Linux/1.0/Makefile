#g++ Enemy/Enemy.cpp Hero/Hero.cpp Motor/Motor.cpp Object/Object.cpp SDLfont/SDLfont.cpp Main/main.cpp -o test `sdl-config --cflags --libs` -lSDL_ttf

CC=g++
CFLAGS=-Wall
LDFLAGS=`sdl-config --cflags --libs`
EXEC=H

all: main

main: Object.o Character.o Motor.o SDLfont.o Main.o
	$(CC) $(LDFLAGS) _Sortie/Object.o _Sortie/Character.o _Sortie/Motor.o _Sortie/SDLfont.o _Sortie/Main.o -o _Sortie/$(EXEC) -lSDL_ttf

Object.o: Object/Object.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c Object/Object.cpp -o _Sortie/Object.o 

Character.o: Character/Character.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c Character/Character.cpp -o _Sortie/Character.o 

Motor.o: Motor/Motor.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c Motor/Motor.cpp -o _Sortie/Motor.o 

SDLfont.o: SDLfont/SDLfont.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c SDLfont/SDLfont.cpp -o _Sortie/SDLfont.o -lSDL_ttf

Main.o: Main/main.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c Main/main.cpp -o _Sortie/Main.o 

clean:
	rm -rf _Sortie/*.o

mrproper: clean
	rm -rf _Sortie/$(EXEC)

