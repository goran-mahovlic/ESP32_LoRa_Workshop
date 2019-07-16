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

void checkAcceptor(void){
  if (digitalRead(coinAcceptor) == LOW){
    if(!readingAcceptor){
      readingAcceptor = true;
      AcceptorFirstPulseTime = os_getTime();
    }
    cointAcceptorInterruptCounter++;
  }  
}

void checkMoney(void){
  
  if(readingAcceptor && (os_getTime() - AcceptorFirstPulseTime) > maxAcceptorWaitTime){
      readingAcceptor = false;
      refreshScreen = true;
      switch (cointAcceptorInterruptCounter) {
        case 6:
          projectMoney++;
          cointAcceptorInterruptCounter = 0;
          break;
        case 7:
          projectMoney+=2;
          cointAcceptorInterruptCounter = 0;
          break;
        case 8:
          projectMoney+=5;
          cointAcceptorInterruptCounter = 0;
          break;
        default:
          // statements
          break;
      }
    }
  }
