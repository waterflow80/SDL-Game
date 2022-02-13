main: main.o mainMenu.o optionsMenu.o utils.o game.o utils.h
	gcc -o main main.o mainMenu.o optionsMenu.o game.o utils.o -lSDL -lSDL_mixer -lSDL_image -lSDL_ttf 

main.o: main.c mainMenu.h
	gcc -c main.c
mainMenu.o: mainMenu.c optionsMenu.h utils.h
	gcc -c mainMenu.c 
optionsMenu.o: optionsMenu.c mainMenu.h utils.h
	gcc -c optionsMenu.c
game.o: game.c utils.h mainMenu.h
	gcc -c game.c
utils.o: utils.c
	gcc -c utils.c
clean: 
	rm -f main.o mainMenu.o optionsMenu.o utils.o 
	rm -f main
