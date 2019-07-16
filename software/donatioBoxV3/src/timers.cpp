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

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  checkButtons();
  checkMoney();
  checkSerialDebug();
  checkLikeTime();
  portEXIT_CRITICAL_ISR(&timerMux);
}

void setupTimers(void){
	timer = timerBegin(0, 80, true);
	timerAttachInterrupt(timer, &onTimer, true);
	timerAlarmWrite(timer, 100000, true);
	timerAlarmEnable(timer);
}

void checkLikeTime(void){
    if(!likeAvailable && (os_getTime() - lastLikeTime) > likeWaitTime){
      likeAvailable = true;
  }
}

void checkSerialDebug(void){
 if(!serialDebugAvailable && (os_getTime() - lastSerialDebugTime) > serialSerialDebugTime){
      serialDebugAvailable = true;
 }
}
