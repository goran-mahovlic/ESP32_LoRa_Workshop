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

#ifndef INCLUDES_H_
#define INCLUDES_H_

#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include <Adafruit_ILI9341.h>
#include "buttons.h"
#include "coins.h"
#include "jobs.h"
#include "lcd.h"
#include "lora.h"
#include "timers.h"

#include "../pic/donation.c"
#include "../pic/laser.c"
#include "../pic/smartZg.c"
#include "../pic/ulx3s.c"
#include "../pic/synthomir.c"


#define TFT_RESET 2
extern Adafruit_ILI9341 tft;

const byte leftButton = 12;
const byte rightButton = 13;
const byte coinAcceptor = 21;
const byte RedLed = 16;
const byte GreenLed = 25;
//dio = {26, 33, 32},

static osjob_t sendjob;
static osjob_t checkjob;

extern boolean readingAcceptor;
extern boolean gotMoney;
extern boolean refreshScreen;

extern unsigned long lastSerialDebugTime;
extern unsigned long serialSerialDebugTime;
extern boolean serialDebugAvailable;

extern unsigned long lastLikeTime;
extern unsigned long likeWaitTime;
extern boolean likeAvailable;

extern unsigned long AcceptorFirstPulseTime;
extern unsigned long maxAcceptorWaitTime ;

extern volatile int cointAcceptorInterruptCounter;

extern long currentProject;
extern uint16_t projectMoney;
extern uint16_t projectLikes;

extern uint16_t project0Likes;
extern uint16_t project1Likes;
extern uint16_t project2Likes;
extern uint16_t project3Likes;
extern uint16_t project4Likes;

extern uint16_t project0Money;
extern uint16_t project1Money;
extern uint16_t project2Money;
extern uint16_t project3Money;
extern uint16_t project4Money;


#endif /* INCLUDES_H_ */
