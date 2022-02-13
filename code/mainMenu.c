#include"mainMenu.h"
#include"optionsMenu.h"
#include "utils.h"
#include "game.h"

/*Colors*/
SDL_Color blue = {92,141,219};

/*Main Menu Screen Handler*/
void mainMenu(void){
  /*Initializing components*/
  if(init_SDL() == 1)
    return;
  if(TTF_Init() == -1)
    return;
  
  /*Events*/
  SDL_Event event;

  /*Main Window*/
  if (fullScreenCheck){
    mainWindow = SDL_SetVideoMode(WIDTH,HEIGHT,BPP,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
  }else {
    mainWindow = SDL_SetVideoMode(WIDTH,HEIGHT,BPP,SDL_HWSURFACE | SDL_DOUBLEBUF);
  }
  
  if(checkScreen(mainWindow) == 1)
    return; // checking if the screen has been loaded successfully
  

  /*Background Image*/
  frameObject backgroundImage;
  backgroundImage.placeHolder = IMG_Load("../images/menu-background-black.jpg");
  backgroundImage.position.x = 0;
  backgroundImage.position.y = 0;
  

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
  

  /*Brief Sounds*/
  // Button Hovered
  hoverSound = Mix_LoadWAV("../brief-sounds/button-hover.wav");
  if(!hoverSound) {
    printf("Mix_LoadWAV: %s\n", Mix_GetError());
    // handle error
}
  // Button Clicked
  clickSound = Mix_LoadWAV("../brief-sounds/water-sci-fi-bleep.wav");
  


  /*Window Main loop*/
  int loop = 1; 
  int choice = -1; // The choice of the user (1: play, 2:options,3:quit)
  while(loop){

    /*Background Color*/
    SDL_FillRect(mainWindow, NULL, SDL_MapRGB(mainWindow->format, 255,255,255)); // White color for the background

    /*Display Background Image*/
    SDL_BlitSurface(backgroundImage.placeHolder, NULL, mainWindow, &backgroundImage.position);

    /*Display Title*/
    SDL_BlitSurface(title.placeHolder, NULL, mainWindow, &title.position);

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
          break;
        }
        case SDL_MOUSEMOTION: // Mouse moving
        {
          buttonHoverEventHandler3Buttons(event, &playButton, &optionsButton, &quitButton, PLAYBUTTON_ORD, OPTIONSBUTTON_ORD, QUITBUTTON_ORD);
          break;
        }
        case SDL_MOUSEBUTTONDOWN: // Mouse clicked
        {
          if (isButtonHovered(event, &playButton) || isButtonHovered(event, &optionsButton) || isButtonHovered(event, &quitButton)) // at least one button is hovered
          {
            choice = clickEventHandler3Buttons(event, &playButton, &optionsButton, &quitButton); // storing the next menu number
            loop = 0; // leaving the main menu
          }
          break;
        }
      }
    }
    /*Updating Screen*/
    SDL_Flip(mainWindow);
  }

  /*Open the user's target*/
  switch (choice){
    case 1: // play screen
    gameMainScreen();
    break; // to be continued
    case 2: // options menu
    optionsMenu();
    break;
    case 3: // Quit
    return;
  }

  printf("test 10\n");

  /*Cleaning Memory*/
  TTF_CloseFont(title.font);
  TTF_Quit();
  Mix_FreeMusic(backgroundMusic);
  SDL_FreeSurface(title.placeHolder);
  Mix_FreeChunk(hoverSound);
  SDL_Quit();

}


















