#include"optionsMenu.h"
#include"mainMenu.h"
#include "utils.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<SDL/SDL.h>
#include<SDL/SDL_mixer.h>
#include<SDL/SDL_ttf.h>
#include<SDL/SDL_image.h>

/*Colors*/
SDL_Color blue2 = {92,141,219};


/*Options menu handler*/
void optionsMenu(){

  /*Options Menu Screen*/
  if (fullScreenCheck){
    optionsMenuScreen = SDL_SetVideoMode(WIDTH,HEIGHT,BPP,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
  }else {
    optionsMenuScreen = SDL_SetVideoMode(WIDTH,HEIGHT,BPP,SDL_HWSURFACE | SDL_DOUBLEBUF);
  }
  
  if(checkScreen(optionsMenuScreen) == 1){
    printf("Options Menu screen has not been loaded !");
    return; // checking if the screen has been loaded successfully
  }

  /*Events*/
  SDL_Event event;

  /*Background Image*/
  frameObject backgroundImage;
  backgroundImage.placeHolder = IMG_Load("../images/menu-background-black.jpg");
  backgroundImage.position.x = 0;
  backgroundImage.position.y = 0;

  /*Header Text*/
  textObject header;
  header.font = TTF_OpenFont("../fonts/collegiate/CollegiateInsideFLF.ttf", 65); // Be careful with the path !!
  if (header.font == NULL){
    printf("Cannot set text ttf 1 %s\n", TTF_GetError());
    return;
  }
  header.color = blue2;
  header.placeHolder = TTF_RenderText_Blended(header.font, OPTIONSHEADER, header.color);
  if (header.placeHolder == NULL){
    printf("Cannot set text ttf %s\n", TTF_GetError());
    return;
  }
  header.position.x = (WIDTH / 2) - (header.placeHolder->w / 2); // this will center the title in the middle of the screen
  header.position.y = TITLE_ORD;


  /*Volume Icon*/
  frameObject VolumeIcon;
  VolumeIcon.placeHolder = IMG_Load("../images/options-menu/volume-icon-small.png");
  VolumeIcon.position.x = (WIDTH / 3 ); // place the icon on the left
  VolumeIcon.position.y = VOLUMEICON_ORD;


  /*Increase Volume Icon (plus icon)*/
  frameObject plusIcon;
  plusIcon.placeHolder = IMG_Load("../images/options-menu/plus-icon-small.png");
  plusIcon.position.x = WIDTH - (WIDTH / 3); // place the icon on the right
  plusIcon.position.y = PLUSICON_ORD;  

  /*Decrease Volume Icon (plus icon)*/
  frameObject minusIcon;
  minusIcon.placeHolder = IMG_Load("../images/options-menu/minus-icon-small.png");
  minusIcon.position.x = WIDTH - (WIDTH / 3); // place the icon on the right, after the plus icon
  minusIcon.position.y = MINUSICON_ORD;  

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

  /*Full-screen icon*/
  frameObject fullScreen;
  fullScreen.placeHolder = IMG_Load("../images/options-menu/full-screen-small-2.png");
  fullScreen.position.x = (WIDTH / 3 ); // place the icon on the left
  fullScreen.position.y = FULLSCREEN_ORD;

  /*Exit Full-Screen*/
  frameObject fullScreenExit;
  fullScreenExit.placeHolder = IMG_Load("../images/options-menu/exit-full-screen-small-2.png");
  fullScreenExit.position.x = WIDTH - (WIDTH / 3); // place the icon on the right
  fullScreenExit.position.y = FULLSCREEN_ORD;

  /*Screen Loop*/
  int loop = 1;
  int choice = -1;
  //int hover = 0;
  while(loop){

    /*Background Color*/
    SDL_FillRect(optionsMenuScreen, NULL, SDL_MapRGB(optionsMenuScreen->format, 255,255,255)); // White color for the background

  /*Display Background Image*/
    SDL_BlitSurface(backgroundImage.placeHolder, NULL, optionsMenuScreen, &backgroundImage.position);

    /*Display Header*/
    SDL_BlitSurface(header.placeHolder, NULL, optionsMenuScreen, &header.position);

    /*Display Volume Icon*/
    SDL_BlitSurface(VolumeIcon.placeHolder, NULL, optionsMenuScreen, &VolumeIcon.position);

    /*Display Plus Icon*/
    SDL_BlitSurface(plusIcon.placeHolder, NULL, optionsMenuScreen, &plusIcon.position);

    /*Display Minus Icon*/
    SDL_BlitSurface(minusIcon.placeHolder, NULL, optionsMenuScreen, &minusIcon.position);

    if (isButtonHovered(event, &returnArrow))
    {
      /*Display Left Arrow*/
      SDL_BlitSurface(arrowLeft.placeHolder, NULL, optionsMenuScreen, &arrowLeft.position);
    }else {
      /*Display Return Arrow*/
      SDL_BlitSurface(returnArrow.placeHolder, NULL, optionsMenuScreen, &returnArrow.position);
    }

    if (fullScreenCheck){
      /*Display Exit Full-Screen mode icon*/
    SDL_BlitSurface(fullScreenExit.placeHolder, NULL, optionsMenuScreen, &fullScreenExit.position);
    }else {
      /*Display Full-Screen mode icon*/
    SDL_BlitSurface(fullScreen.placeHolder, NULL, optionsMenuScreen, &fullScreen.position);
    }
    

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
          if (!fullScreenCheck){
            buttonHoverEventHandler4Buttons(event, &plusIcon, &minusIcon,&arrowLeft,&fullScreen, PLUSICON_ORD, MINUSICON_ORD, RETURNARROW_ORD, FULLSCREEN_ORD);
            break;
          }else {
            buttonHoverEventHandler4Buttons(event, &plusIcon, &minusIcon,&arrowLeft,&fullScreenExit, PLUSICON_ORD, MINUSICON_ORD, RETURNARROW_ORD, FULLSCREEN_ORD);
            break;
          }
        }
        case SDL_MOUSEBUTTONDOWN: // Mouse clicked
        {
          if (!fullScreenCheck){
            if (!buttonHoverEventHandler4Buttons(event, &plusIcon, &minusIcon,&returnArrow,&fullScreen, PLUSICON_ORD, MINUSICON_ORD, RETURNARROW_ORD, FULLSCREEN_ORD)); // at least one button is hovered
          {
            choice = clickEventHandler4Buttons(event, &plusIcon, &minusIcon, &arrowLeft, &fullScreen);
            switch (choice){
              case 1: // increse the sound
              //printf("increasing the sound !");
              break;
              case 2: // Decreasing the sound
              //printf("Decreasing the sound !");
              break;
              case 3: // returning to the mainMenu screen
              loop = 0;
              break;
              case 4: // Go to Full Screen Mode
              {
              optionsMenuScreen = SDL_SetVideoMode(WIDTH,HEIGHT,BPP,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
              mainWindow = SDL_SetVideoMode(WIDTH,HEIGHT,BPP,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
              fullScreenCheck = true;
              choice = -1; // refresh the value
              break;
              }
            }
            }
          }else {
            if (!buttonHoverEventHandler4Buttons(event, &plusIcon, &minusIcon,&returnArrow,&fullScreenExit, PLUSICON_ORD, MINUSICON_ORD, RETURNARROW_ORD, FULLSCREEN_ORD)); // at least one button is hovered
          {
            choice = clickEventHandler4Buttons(event, &plusIcon, &minusIcon, &arrowLeft, &fullScreenExit);
            switch (choice){
              case 1: // increse the sound
              //printf("increasing the sound !");
              break;
              case 2: // Decreasing the sound
              //printf("Decreasing the sound !");
              break;
              case 3: // returning to the mainMenu screen
              loop = 0;
              break;
              case 4: // Leave Full Screen Mode
              {
              optionsMenuScreen = SDL_SetVideoMode(WIDTH,HEIGHT,BPP,SDL_HWSURFACE | SDL_DOUBLEBUF);
              mainWindow = SDL_SetVideoMode(WIDTH,HEIGHT,BPP,SDL_HWSURFACE | SDL_DOUBLEBUF);
              fullScreenCheck = false;
              choice = -1; // refresh the value
              break;
              }
            }
            }
          }
          
          break;
        }
      }
    }
    /*Updating Screen*/
    SDL_Flip(optionsMenuScreen);
}
  if (choice != -1)
    mainMenu(); // open the mainWindow
}