#include"menu.h"
#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_mixer.h>
#include<SDL/SDL_ttf.h>
#include<SDL/SDL_image.h>

/*Headers*/
int init_SDL();
void initializeAudio();
int checkScreen(SDL_Surface* screen);
void setTitle(char* title);


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


void buttonEventHandler(SDL_Event event, frameObject* playButton, frameObject* optionsButton, frameObject* quitButton); //this will contain all buttons

/*Colors*/
SDL_Color blue = {92,141,219};

/*Constants*/
#define WIDTH 1000
#define HEIGHT 800
#define BPP 32
#define TITLE "My Game"

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

/*Brief Sounds*/


int i =0;
/*Main Menu Screen Handler*/
void mainMenu(void){
  printf("test 1\n");
  /*Initializing components*/
  if(init_SDL() == 1)
    return;
  if(TTF_Init() == -1)
    return;
  printf("test 2\n");
  /*Events*/
  SDL_Event event;

  /*Main Window*/
  SDL_Surface* mainWindow;
  mainWindow = SDL_SetVideoMode(WIDTH,HEIGHT,BPP,SDL_HWSURFACE | SDL_DOUBLEBUF);
  if(checkScreen(mainWindow) == 1)
    return; // checking if the screen has been loaded successfully
  printf("test 3\n");

  /*Background Image*/
  frameObject backgroundImage;
  backgroundImage.placeHolder = IMG_Load("../images/menu-background-black.jpg");
  backgroundImage.position.x = 0;
  backgroundImage.position.y = 0;
  printf("test 4\n");

  /*Title Text*/
  textObject title;
  title.font = TTF_OpenFont("../fonts/collegiate/CollegiateInsideFLF.ttf", 65); // Be careful with the path !!
  if (title.font == NULL){
    printf("Cannot set text ttf 1 %s\n", TTF_GetError());
    return;
  }
  title.color = blue;
  title.placeHolder = TTF_RenderText_Blended(title.font, TITLE, title.color);
  if (title.placeHolder == NULL){
    printf("Cannot set text ttf %s\n", TTF_GetError());
    return;
    
  }
  title.position.x = (WIDTH / 2) - (title.placeHolder->w / 2); // this will center the title in the middle of the screen
  title.position.y = TITLE_ORD;
  printf("test 5\n");

  /*Play Button*/
  frameObject playButton;
  playButton.placeHolder = IMG_Load("../images/buttons/button-260-250.png");
  playButton.position.x = (WIDTH / 2 ) - (playButton.placeHolder->w / 2 ); // this will center the play button horizontally
  playButton.position.y = PLAYBUTTON_ORD;

  /*Options Button*/
  frameObject optionsButton;
  optionsButton.placeHolder = IMG_Load("../images/buttons/option-button-260220.png");
  optionsButton.position.x = (WIDTH / 2 ) - (optionsButton.placeHolder->w / 2 ); // this will center the options button horizontally
  optionsButton.position.y = OPTIONSBUTTON_ORD;

  /*Quit Button*/
  frameObject quitButton;
  quitButton.placeHolder = IMG_Load("../images/buttons/quit-button-260-220.png");
  quitButton.position.x = (WIDTH / 2 ) - (quitButton.placeHolder->w / 2);
  quitButton.position.y = QUITBUTTON_ORD;

  /*Background Music*/
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){
  //API Mixer initialization 
    printf("%s\n", Mix_GetError());
    return;
  }
  Mix_Music* backgroundMusic;
  backgroundMusic = Mix_LoadMUS("../music/background-music.mp3");
  if (backgroundMusic == NULL)
  {
    printf("Cannot load music ! %s", Mix_GetError());
    return;
  }
  //Mix_PlayMusic(backgroundMusic, -1); // looping the music
  printf("test 6\n");

  /*Brief Sounds*/
  Mix_Chunk* clickSound;
  clickSound = Mix_LoadWAV("../brief-sounds/gun-click.wav");


  /*Window Main loop*/
  int loop = 1; 
  while(loop){

    /*Background Color*/
    SDL_FillRect(mainWindow, NULL, SDL_MapRGB(mainWindow->format, 255,255,255)); // White color for the background
    //printf("test 7\n");

    /*Display Background Image*/
    SDL_BlitSurface(backgroundImage.placeHolder, NULL, mainWindow, &backgroundImage.position);
    //printf("test 8\n");

    /*Display Title*/
    SDL_BlitSurface(title.placeHolder, NULL, mainWindow, &title.position);
    //printf("test 9\n");

    /*Display Play button*/
    SDL_BlitSurface(playButton.placeHolder, NULL, mainWindow, &playButton.position);

    /*Display Otions button*/
    SDL_BlitSurface(optionsButton.placeHolder, NULL, mainWindow, &optionsButton.position);

    /*Display Quit Button*/
    SDL_BlitSurface(quitButton.placeHolder, NULL, mainWindow, &quitButton.position);

    /*Handling events*/
    while (SDL_PollEvent(&event))
    { //Check for messages
      switch(event.type)
      {
        // Exit if the window is closed
        case SDL_QUIT:
          loop = 0;
          break;
        // Check for keypresses
        case SDL_KEYDOWN:
        {
          //Exit if ESCAPE is pressed
          if (event.key.keysym.sym == SDLK_ESCAPE)
          loop = 0;
          /* if (event.key.keysym.sym == SDLK_RIGHT)
          positionElement.x += 10;
          if (event.key.keysym.sym == SDLK_LEFT)
          positionElement.x -= 10;
          if (event.key.keysym.sym == SDLK_DOWN)
          positionElement.y += 10;
          if (event.key.keysym.sym == SDLK_UP)
          positionElement.y -= 10; */
          break;
        }
        case SDL_MOUSEMOTION:
        {
          buttonEventHandler(event, &playButton, &optionsButton, &quitButton);
        }
      }
    }

    /*Updating Screen*/
    SDL_Flip(mainWindow);
  }

  printf("test 10\n");

  /*Cleaning Memory*/
  TTF_CloseFont(title.font);
  TTF_Quit();
  Mix_FreeMusic(backgroundMusic);
  SDL_FreeSurface(title.placeHolder);
  Mix_FreeChunk(clickSound);
  SDL_Quit();

}



int init_SDL(){
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    printf("test 11\n");
    printf("Unable to initialize SDL: %s\n", SDL_GetError());
    return 1;
  }
}

/* initializing audio requirements
 * print error if there's a problem*/
void initializeAudio(){
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){
  //API Mixer initialization 
    printf("%s\n", Mix_GetError());
  }
}

/*Check if the screen has been set correctly
return 1 otherwise*/
int checkScreen(SDL_Surface* screen){
  if (screen == NULL){
    printf("Unable to set video mode: %s\n", SDL_GetError());
    return 1;
  }
}

/*Set the title of the app (Game)*/
void setTitle(char* title){
  SDL_WM_SetCaption(title, "images/icon.png"); 
}


/*Handle Mouse events on buttons*/
void buttonEventHandler(SDL_Event event, frameObject* playButton, frameObject* optionsButton, frameObject* quitButton){
  if (event.motion.x >= playButton->position.x && event.motion.x <= playButton->position.x + playButton->placeHolder->w
          && event.motion.y >= playButton->position.y && event.motion.y <= playButton->position.y + playButton->placeHolder->h)
  {
    if (playButton->position.y == PLAYBUTTON_ORD)
    {
      playButton->position.y -= 5; // moving button up to indicate hovering
      }
  }else if (event.motion.x >= optionsButton->position.x && event.motion.x <= optionsButton->position.x + optionsButton->placeHolder->w
          && event.motion.y >= optionsButton->position.y && event.motion.y <= optionsButton->position.y + optionsButton->placeHolder->h)
          {
            if (optionsButton->position.y == OPTIONSBUTTON_ORD)
              optionsButton->position.y -= 5; // moving button up to indicate hovering
          }
  else if (event.motion.x >= quitButton->position.x && event.motion.x <= quitButton->position.x + quitButton->placeHolder->w
          && event.motion.y >= quitButton->position.y && event.motion.y <= quitButton->position.y + quitButton->placeHolder->h)
          {
             if (quitButton->position.y == QUITBUTTON_ORD)
              quitButton->position.y -= 5; // moving button up to indicate hovering
          } 
  else{
    /*Return to the initial position*/
    playButton->position.y = PLAYBUTTON_ORD;
    optionsButton->position.y = OPTIONSBUTTON_ORD;
    quitButton->position.y = QUITBUTTON_ORD;
  }
  
}