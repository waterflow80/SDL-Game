#ifndef UTILS_H
#define UTILS_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<SDL/SDL.h>
#include<SDL/SDL_mixer.h>
#include<SDL/SDL_ttf.h>
#include<SDL/SDL_image.h>

/*Frame Object Type*/
typedef struct{
  SDL_Surface* placeHolder;
  SDL_Rect position;
}frameObject;

/*Text Object Type*/
typedef struct {
  SDL_Surface* placeHolder;
  TTF_Font* font;
  SDL_Color color; // RGB color
  SDL_Rect position;
}textObject;

/*Colors*/
//SDL_Color blue = {92,141,219};

int buttonHoverEventHandler1Button(SDL_Event event, frameObject* button, int ord);
int clickEventHandler1Button(SDL_Event event, frameObject* button);
int buttonHoverEventHandler3Buttons(SDL_Event event, frameObject* button1, frameObject* button2, frameObject* button3, int ord1, int ord2, int ord3);
int buttonHoverEventHandler2Buttons(SDL_Event event, frameObject* button1, frameObject* button2, int ord1, int ord2);
int buttonHoverEventHandler4Buttons(SDL_Event event, frameObject* button1, frameObject* button2, frameObject* button3,frameObject* button4, int ord1, int ord2, int ord3, int ord4);
int clickEventHandler3Buttons(SDL_Event event, frameObject* playButton, frameObject* optionsButton, frameObject* quitButton);
int clickEventHandler2Buttons(SDL_Event event, frameObject* button1, frameObject* button2);
int clickEventHandler4Buttons(SDL_Event event, frameObject* button1, frameObject* button2, frameObject* button3, frameObject* button4);
bool isButtonHovered(SDL_Event event, frameObject* button);
void setTitle(char* title);
int checkScreen(SDL_Surface* screen);
void initializeAudio();
int init_SDL();

/*Check if the screen is in full-screen mode*/
bool fullScreenCheck;

/*Constants*/
#define WIDTH 1000
#define HEIGHT 800
#define BPP 32
#define TITLE "My Game"

#define OPTIONSHEADER "Options"

#define WELCOMETEXT "Welcome to My Game"

#define TITLE_ABS 310 
#define TITLE_ORD 70

/*Buttons Specs*/
#define PLAYBUTTON_ABS 330 // the position of the button horizontally
#define PLAYBUTTON_ORD 250 // the position of the button vertically
#define OPTIONSBUTTON_ABS 330
#define OPTIONSBUTTON_ORD 380
#define QUITBUTTON_ORD 510
#define BUTTON_WIDTH 260
#define BUTTON_HEIGHT 250
#define VOLUMEICON_ORD 250
#define PLUSICON_ORD 320
#define MINUSICON_ORD 280

#define RETURNARROW_ORD 10
#define RETURNARROW_ABS 10
#define FULLSCREEN_ORD 550

#define NEWGAMEBUTTON_ORD 280


/*Brief Sounds*/
Mix_Chunk* hoverSound;
Mix_Chunk* clickSound;



/*Main window variables*/
SDL_Surface* mainWindow;

/*Options window variables*/
SDL_Surface* optionsMenuScreen;

/*Game variables*/
SDL_Surface* gameHomeScreen;

#endif