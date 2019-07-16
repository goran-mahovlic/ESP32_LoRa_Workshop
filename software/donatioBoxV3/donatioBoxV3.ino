/*
  _____                    _   _             ____          __      ______
 |  __ \                  | | (_)           |  _ \         \ \    / /___ \
 | |  | | ___  _ __   __ _| |_ _  ___  _ __ | |_) | _____  _\ \  / /  __) |
 | |  | |/ _ \| '_ \ / _` | __| |/ _ \| '_ \|  _ < / _ \ \/ /\ \/ /  |__ <
 | |__| | (_) | | | | (_| | |_| | (_) | | | | |_) | (_) >  <  \  /   ___) |
 |_____/ \___/|_| |_|\__,_|\__|_|\___/|_| |_|____/ \___/_/\_\  \/   |____/

 Description: DonationBoxV3 box for presentation and exibitions - users can donate money or likes
 
 Based on Heltec esp32 wifi-lora-32 board
 Version: 1.03 
 License: FreeBSD
 Maintainer: Goran Mahovlić
 by: Radiona.org

*/

#include "inc/includes.h"

// Here you define how many project you have
#define NO_PROJECTS 5
     
void setup() {
  // Interrupt every 100ms to check for changes
  setupTimers();
  // Setup pins
  setupAllPins();
  // Start serial
  Serial.begin(115200);
  // Init LCD
  setupLCD();
  // LMIC init
//  os_init();
  // SetupLoRa
//  setupLoRa();
//  initSD();
  // Start check for project change - change picture - send serial 
  do_check(&checkjob);
  // Start LoRa send job (sending automatically starts OTAA too)
//  do_send(&sendjob);
}
 
void loop() {
  os_runloop_once();
}

