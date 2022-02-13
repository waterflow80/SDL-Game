#include "game.h"
#include "utils.h"
#include "mainMenu.h"

/*Colors*/
SDL_Color white1 = {240,240,240};

/*Game main screen*/
void gameMainScreen(){

  /*Game Home Screen*/
  if (fullScreenCheck){
    gameHomeScreen = SDL_SetVideoMode(WIDTH,HEIGHT,BPP,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
  }else {
    gameHomeScreen = SDL_SetVideoMode(WIDTH,HEIGHT,BPP,SDL_HWSURFACE | SDL_DOUBLEBUF);
  }
  if(checkScreen(gameHomeScreen) == 1){
    printf("Game Home screen has not been loaded !");
    return; // checking if the screen has been loaded successfully
  }

  /*Events*/
  SDL_Event event;

  /*Background Image*/
  frameObject backgroundImage;
  backgroundImage.placeHolder = IMG_Load("../images/game-images/game-home-screen-image.jpg");
  backgroundImage.position.x = 0;
  backgroundImage.position.y = 0;


  /*Welcome Text*/
  textObject welcomeText;
  welcomeText.font = TTF_OpenFont("../fonts/collegiate/CollegiateInsideFLF.ttf", 65); // Be careful with the path !!
  if (welcomeText.font == NULL){
    printf("Cannot set text ttf 1 %s\n", TTF_GetError());
    return;
  }
  welcomeText.color = white1;
  welcomeText.placeHolder = TTF_RenderText_Blended(welcomeText.font, WELCOMETEXT, welcomeText.color);
  if (welcomeText.placeHolder == NULL){
    printf("Cannot set text ttf %s\n", TTF_GetError());
    return;
  }
  welcomeText.position.x = (WIDTH / 2) - (welcomeText.placeHolder->w / 2); // this will center the title in the middle of the screen
  welcomeText.position.y = TITLE_ORD;

  /*New-Game Button*/
  frameObject newGameButton;
  newGameButton.placeHolder = IMG_Load("../images/game-images/new-game-button-260-220.png");
  newGameButton.position.x = (WIDTH / 2 ) - (newGameButton.placeHolder->w / 2 ); // this will center the button horizontally
  newGameButton.position.y = NEWGAMEBUTTON_ORD;

  /*Reutrn Arrow Icon (go back to main menu)*/
  frameObject returnArrow;
  returnArrow.placeHolder = IMG_Load("../images/options-menu/arrow-back-small.png");
  returnArrow.position.x = RETURNARROW_ABS;
  returnArrow.position.y = RETURNARROW_ORD;

  /*Arrow left (when hovering the return arrow)*/
  frameObject arrowLeft;
  arrowLeft.placeHolder = IMG_Load("../images/options-menu/arrow-left-small.png");
  arrowLeft.position.x = RETURNARROW_ABS;
  arrowLeft.position.y = RETURNARROW_ORD;

  /*Screen Loop*/
  int loop =1;
  int choice = -1;
  while (loop){
    /*Background Color*/
    SDL_FillRect(gameHomeScreen, NULL, SDL_MapRGB(gameHomeScreen->format, 255,255,255)); // White color for the background

    /*Display Background Image*/
    SDL_BlitSurface(backgroundImage.placeHolder, NULL, optionsMenuScreen, &backgroundImage.position);

    /*Display Welcome Text*/
    SDL_BlitSurface(welcomeText.placeHolder, NULL, optionsMenuScreen, &welcomeText.position);

    if (isButtonHovered(event, &returnArrow))
    {
      /*Display Left Arrow*/
      SDL_BlitSurface(arrowLeft.placeHolder, NULL, optionsMenuScreen, &arrowLeft.position);
    }else {
      /*Display Return Arrow*/
      SDL_BlitSurface(returnArrow.placeHolder, NULL, optionsMenuScreen, &returnArrow.position);
    }

    /*Display New-Game Button*/
    SDL_BlitSurface(newGameButton.placeHolder, NULL, optionsMenuScreen, &newGameButton.position);

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
          buttonHoverEventHandler2Buttons(event, &newGameButton,&arrowLeft, NEWGAMEBUTTON_ORD, RETURNARROW_ORD);
          break;
        }
        case SDL_MOUSEBUTTONDOWN: // Mouse clicked
        {
            if (!buttonHoverEventHandler2Buttons(event, &newGameButton,&arrowLeft, NEWGAMEBUTTON_ORD, RETURNARROW_ORD)); // at least one button is hovered
          {
            choice = clickEventHandler2Buttons(event, &newGameButton, &arrowLeft);
            switch (choice){
              case 1: // Start New Game
              //printf("increasing the sound !");
              break;
              case 2: //return to main menu
              loop = 0;
              break;
            }
            }
          break;
        }
      }
    }

    /*Updating Screen*/
    SDL_Flip(optionsMenuScreen);
  }

  switch (choice){
    case 2: // Go back to main menu
    mainMenu();
    break;
  }

}