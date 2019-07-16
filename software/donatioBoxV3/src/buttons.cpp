/*
  _____                    _   _             ____          __      ______
 |  __ \                  | | (_)           |  _ \         \ \    / /___ \
 | |  | | ___  _ __   __ _| |_ _  ___  _ __ | |_) | _____  _\ \  / /  __) |
 | |  | |/ _ \| '_ \ / _` | __| |/ _ \| '_ \|  _ < / _ \ \/ /\ \/ /  |__ <
 | |__| | (_) | | | | (_| | |_| | (_) | | | | |_) | (_) >  <  \  /   ___) |
 |_____/ \___/|_| |_|\__,_|\__|_|\___/|_| |_|____/ \___/_/\_\  \/   |____/

 Description: 
 License: FreeBSD
 Maintainer: Goran Mahovlić
 by: Radiona.org

*/

#include "../inc/includes.h"

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR handleInterrupt() {
  portENTER_CRITICAL_ISR(&mux);
  checkAcceptor();
  portEXIT_CRITICAL_ISR(&mux);
}

void checkButtons(void){
      if(!digitalRead(leftButton)){
        currentProject = random(NO_PROJECTS);
        refreshScreen = true;
        }
      if(!digitalRead(rightButton) && likeAvailable){
          projectLikes++;
          lastLikeTime = os_getTime();
          likeAvailable = false;
        }
}

void setupAllPins(void){

      pinMode(leftButton, INPUT_PULLUP);
      pinMode(rightButton, INPUT_PULLUP);
      pinMode(coinAcceptor, INPUT_PULLUP);
      attachInterrupt(digitalPinToInterrupt(coinAcceptor), handleInterrupt, FALLING);
}