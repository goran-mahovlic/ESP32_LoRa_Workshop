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
#define TFT_RESET 2

const unsigned CHECK_INTERVAL = 1;

void do_check(osjob_t* j) {
  
  if (refreshScreen){
    tft.setRotation(3);

  switch (currentProject) {
    case 0:    // wellcome
      tft.drawRGBBitmap(0,0,(uint16_t *)donation.pixel_data,donation.width, donation.height);
      break;
    case 1:    // ulx3s
      tft.drawRGBBitmap(0,0,(uint16_t *)ulx3s.pixel_data,ulx3s.width, ulx3s.height);
      break;
    case 2:    // laser
      tft.drawRGBBitmap(0,0,(uint16_t *)laser.pixel_data,laser.width, laser.height);
      break;
    case 3:    // kikiriki
      tft.drawRGBBitmap(0,0,(uint16_t *)smartZg.pixel_data,smartZg.width, smartZg.height);
      break;
    case 4:    // kikiriki
      tft.drawRGBBitmap(0,0,(uint16_t *)synthomir.pixel_data,synthomir.width, synthomir.height);
    break;
    default:
          tft.drawRGBBitmap(0,0,(uint16_t *)donation.pixel_data,donation.width, donation.height);
    break;
  } 
    refreshScreen = false;
  }

  if (serialDebugAvailable){
    
    serialDebugAvailable = false;
    lastSerialDebugTime = os_getTime();
    
    Serial.println("");  
    Serial.println("");
    Serial.println("########################");
    Serial.println("#Donation Box V3 Debug#");
    Serial.println("########################");
    Serial.println("");  
    Serial.print("Selected project: ");
    Serial.println(currentProject);     
    Serial.print("Likes: ");
    Serial.println(projectLikes);         
    Serial.print("Money: ");
    Serial.println(projectMoney);

    Serial.print("Like timer : ");
    Serial.println(os_getTime() - lastLikeTime);
    Serial.print("Like available: ");
    Serial.println(likeAvailable);

    Serial.print("Acceptor time: ");
    Serial.println(os_getTime() - AcceptorFirstPulseTime);

    Serial.print("Acceptor pulse: ");
    Serial.println(cointAcceptorInterruptCounter);
    
    Serial.print("Acceptor status: ");
    Serial.println(readingAcceptor);
    Serial.println("########################"); 
    
  } 
  os_setTimedCallback(&checkjob, os_getTime() + sec2osticks(CHECK_INTERVAL), do_check);
}
