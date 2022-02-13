#include "utils.h"



/*Handle hovered buttons by the mouse
1: button 1 hovered
2: button 2 hovered
3: button 3 hovered
0: no button is hovered
*/
int buttonHoverEventHandler3Buttons(SDL_Event event, frameObject* button1, frameObject* button2, frameObject* button3, int ord1, int ord2, int ord3){
  if (isButtonHovered(event, button1))
  {
    if (button1->position.y == ord1)
    {
      Mix_PlayChannel(-1, hoverSound, 0); //playing hover sound
      
      button1->position.y -= 5; // moving button up to indicate hovering
      }
      return 1; // play button hovered
  }else if (isButtonHovered(event, button2))
          {
            if (button2->position.y == ord2){
              Mix_PlayChannel(-1, hoverSound, 0);
              button2->position.y -= 5; // moving button up to indicate hovering
              }
              return 2; // options button hovered
          }
  else if (isButtonHovered(event, button3))
          {
             if (button3->position.y == ord3){
              Mix_PlayChannel(-1, hoverSound, 0);
              button3->position.y -= 5; // moving button up to indicate hovering
             }
             return 3; // quit button hovered
          } 
  else{
    /*Return to the initial position*/
    button1->position.y = ord1;
    button2->position.y = ord2;
    button3->position.y = ord3;
    return 0;
  }
  
}


/*Handle the hovering of the buttons passed in parameters
ord: the position in the y axis of the button
*/
int buttonHoverEventHandler2Buttons(SDL_Event event, frameObject* button1, frameObject* button2, int ord1, int ord2){
   if (isButtonHovered(event, button1))
  {
    if (button1->position.y == ord1) // VOLUMEICON_ORD should be passed in parameters for more abstraction
    {
      Mix_PlayChannel(-1, hoverSound, 0); //playing hover sound
      
      button1->position.y -= 2; // moving button up to indicate hovering
      }
      return 1; // play button hovered
  }else if (isButtonHovered(event, button2))
          {
            if (button2->position.y == ord2){
              Mix_PlayChannel(-1, hoverSound, 0);
              button2->position.y -= 2; // moving button up to indicate hovering
              }
              return 2; // options button hovered
          }
          else {
    /*Return to the initial position*/
    button1->position.y = ord1;
    button2->position.y = ord2;
    return 0;
          }
}

/*Handle the hovering of the button passed in parameters
ord1: the position in the y axis of button1
ord2: the position in the y axis of button2
*/
int buttonHoverEventHandler1Button(SDL_Event event, frameObject* button, int ord){
   if (isButtonHovered(event, button))
  {
    if (button->position.y == ord) // VOLUMEICON_ORD should be passed in parameters for more abstraction
    {
      Mix_PlayChannel(-1, hoverSound, 0); //playing hover sound
      
      button->position.y -= 2; // moving button up to indicate hovering
      }
      return 1; // play button hovered
  }
          else {
    /*Return to the initial position*/
    button->position.y = ord;
    return 0;
          }
}

/*Handle hovered buttons by the mouse
1: button 1 hovered
2: button 2 hovered
3: button 3 hovered
4: button 4 hovered
0: no button is hovered
*/
int buttonHoverEventHandler4Buttons(SDL_Event event, frameObject* button1, frameObject* button2, frameObject* button3,frameObject* button4, int ord1, int ord2, int ord3, int ord4){
  if (isButtonHovered(event, button1))
  {
    if (button1->position.y == ord1)
    {
      Mix_PlayChannel(-1, hoverSound, 0); //playing hover sound
      
      button1->position.y -= 5; // moving button up to indicate hovering
      }
      return 1; // play button hovered
  }else if (isButtonHovered(event, button2))
          {
            if (button2->position.y == ord2){
              Mix_PlayChannel(-1, hoverSound, 0);
              button2->position.y -= 5; // moving button up to indicate hovering
              }
              return 2; // options button hovered
          }
  else if (isButtonHovered(event, button3))
          {
             if (button3->position.y == ord3){
              Mix_PlayChannel(-1, hoverSound, 0);
              button3->position.y -= 5; // moving button up to indicate hovering
             }
             return 3; // quit button hovered
          }
  else if (isButtonHovered(event, button4))
          {
             if (button4->position.y == ord4){
              Mix_PlayChannel(-1, hoverSound, 0);
              button4->position.y -= 5; // moving button up to indicate hovering
             }
             return 4; // quit button hovered
          }
  else{
    /*Return to the initial position*/
    button1->position.y = ord1;
    button2->position.y = ord2;
    button3->position.y = ord3;
    button4->position.y = ord4;
    return 0;
  }
  
}

/*Handle clicked buttons by the mouse
1: Button 1 clicked
2: Button 2 clicked
3: Button 3 clicked
*/
int clickEventHandler3Buttons(SDL_Event event, frameObject* button1, frameObject* button2, frameObject* button3){
  if (isButtonHovered(event, button1)){
    // Play button clicked
     Mix_PlayChannel(-1, clickSound, 0);
     return 1;
  }
  else if (isButtonHovered(event, button2)){
    // Options button clicked
    Mix_PlayChannel(-1, clickSound, 0);
    return 2;
  }
  else if (isButtonHovered(event, button3)){
    // Quit button clicked
    Mix_PlayChannel(-1, clickSound, 0);
    return 3;
  }
  
}

/*Handle clicked button by the mouse
1: button is clicked
*/
int clickEventHandler1Button(SDL_Event event, frameObject* button){
  if (isButtonHovered(event, button)){
    // Play button clicked
     Mix_PlayChannel(-1, clickSound, 0);
     return 1;
  }
  
}

/*Handle clicked buttons by the mouse
1: Button 1 clicked
2: Button 2 clicked
3: Button 3 clicked
4: Button 4 clicked
*/
int clickEventHandler4Buttons(SDL_Event event, frameObject* button1, frameObject* button2, frameObject* button3, frameObject* button4){
  if (isButtonHovered(event, button1)){
    // Button 1 clicked
     Mix_PlayChannel(-1, clickSound, 0);
     return 1;
  }
  else if (isButtonHovered(event, button2)){
    // Button 2 clicked
    Mix_PlayChannel(-1, clickSound, 0);
    return 2;
  }
  else if (isButtonHovered(event, button3)){
    // Button 3 clicked
    Mix_PlayChannel(-1, clickSound, 0);
    return 3;
  }
  else if (isButtonHovered(event, button4)){
    // Button 1 clicked
    Mix_PlayChannel(-1, clickSound, 0);
    return 4;
  }
  
}


/*Handle clicks on the buttons passed in parameters
1: button 1 clicked
2: button 2 clicked*/
int clickEventHandler2Buttons(SDL_Event event, frameObject* button1, frameObject* button2){
  if (isButtonHovered(event, button1)){
    // Play button clicked
     Mix_PlayChannel(-1, clickSound, 0);
     return 1;
  }
  else if (isButtonHovered(event, button2)){
    // Options button clicked
    Mix_PlayChannel(-1, clickSound, 0);
    return 2;
  }
}


/*Check if the button is hovered*/
bool isButtonHovered(SDL_Event event, frameObject* button){
  return event.motion.x >= button->position.x && event.motion.x <= button->position.x + button->placeHolder->w
          && event.motion.y >= button->position.y && event.motion.y <= button->position.y + button->placeHolder->h;
}

/*Set the title of the app (Game)*/
void setTitle(char* title){
  SDL_WM_SetCaption(title, "images/icon.png"); 
}


/*Check if the screen has been set correctly
return 1 otherwise*/
int checkScreen(SDL_Surface* screen){
  if (screen == NULL){
    printf("Unable to set video mode: %s\n", SDL_GetError());
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

int init_SDL(){
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    printf("test 11\n");
    printf("Unable to initialize SDL: %s\n", SDL_GetError());
    return 1;
  }
}
