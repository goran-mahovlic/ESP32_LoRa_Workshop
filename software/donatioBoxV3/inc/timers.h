/*
  _____                    _   _             ____          __      ______
 |  __ \                  | | (_)           |  _ \         \ \    / /___ \
 | |  | | ___  _ __   __ _| |_ _  ___  _ __ | |_) | _____  _\ \  / /  __) |
 | |  | |/ _ \| '_ \ / _` | __| |/ _ \| '_ \|  _ < / _ \ \/ /\ \/ /  |__ <
 | |__| | (_) | | | | (_| | |_| | (_) | | | | |_) | (_) >  <  \  /   ___) |
 |_____/ \___/|_| |_|\__,_|\__|_|\___/|_| |_|____/ \___/_/\_\  \/   |____/

 Description: Generic lora driver

 License: FreeBSD

 Maintainer: Goran Mahovlić

 by: Radiona.org

*/

#ifndef TIMERS_H_
#define TIMERS_H_

void setupTimers(void);
void checkLikeTime(void);
void checkSerialDebug(void);
void IRAM_ATTR onTimer();

#endif /* TIMERS_H_ */
