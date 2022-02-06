main: main.o menu.o
	gcc -o main main.o menu.o -lSDL -lSDL_mixer -lSDL_image -lSDL_ttf 

main.o: main.c menu.h
	gcc -c main.c
menu.o: menu.c
	gcc -c menu.c 

clean: 
	rm -f main.o menu.o
	rm -f main
