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

#define TFT_DC 23
#define TFT_CS  22

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RESET);

boolean readingAcceptor = false;
boolean gotMoney = false;
boolean refreshScreen = true;

unsigned long lastSerialDebugTime = 0;
unsigned long serialSerialDebugTime = 100000;
boolean serialDebugAvailable = true;

unsigned long lastLikeTime = 0;
unsigned long likeWaitTime = 1000000;
boolean likeAvailable = true;

unsigned long AcceptorFirstPulseTime = 0;
unsigned long maxAcceptorWaitTime = 100000;

volatile int cointAcceptorInterruptCounter = 0;

typedef struct 
{
  uint8_t ID1;
  int projectMoney1;
  int projectLikes1;
  String projectName1;
  
} projet;

long currentProject = 0;
uint16_t projectMoney = 0;
uint16_t projectLikes = 0;
