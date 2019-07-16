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

#ifndef LORA_H_
#define LORA_H_

void setupLoRa(void);
void do_send(osjob_t* j);
//#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
//#define TIME_TO_SLEEP  60        /* Time ESP32 will go to sleep (in seconds) */
// #define USE_JOINING

#endif /* LORA_H_ */