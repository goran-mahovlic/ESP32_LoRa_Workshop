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

const unsigned TX_INTERVAL = 60;
RTC_DATA_ATTR int bootCount = 0;
//every project needs 5 bytes
static uint8_t mydata[NO_PROJECTS*5] = { 0 };

// Pin mapping
const lmic_pinmap lmic_pins = {
  .nss = 18,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 14,
  .dio = {26, 33, 32},
};

#ifdef USE_JOINING
  // OTAA join keys
  // This EUI must be in little-endian format, so least-significant-byte
  // first. When copying an EUI from ttnctl output, this means to reverse
  // the bytes. For TTN issued EUIs the last bytes should be 0xD5, 0xB3,
  // 0x70.
  static const u1_t PROGMEM APPEUI[8] = { 0xXX, 0xXX, 0x00, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX };

  void os_getArtEui (u1_t* buf) {
    memcpy_P(buf, APPEUI, 8);
  }
 
  // This should also be in little endian format, see above.
  static const u1_t PROGMEM DEVEUI[8] = { 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX };
  void os_getDevEui (u1_t* buf) {
    memcpy_P(buf, DEVEUI, 8);
  }
 
  // This key should be in big endian format (or, since it is not really a
  // number but a block of memory, endianness does not really apply). In
  // practice, a key taken from ttnctl can be copied as-is.
  // The key shown here is the semtech default key.
  static const u1_t PROGMEM APPKEY[16] = { 0xXX, 0XX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX };
  void os_getDevKey (u1_t* buf) {
    memcpy_P(buf, APPKEY, 16);
  }
 
#else
  // ABP keys
 
  // LoRaWAN NwkSKey, network session key (msb)
  
  static const PROGMEM u1_t NWKSKEY[] = { 0x61, 0xA6, 0xCB, 0x2E, 0xF2, 0xA2, 0xF9, 0xBB, 0xEC, 0x1A, 0xC2, 0x3D, 0x22, 0xC0, 0x14, 0x94 };
  
  // LoRaWAN AppSKey, application session key (msb)
  static const u1_t PROGMEM APPSKEY[] = { 0x5B, 0x2B, 0xA4, 0x88, 0x93, 0x08, 0x7E, 0x1B, 0x77, 0xB0, 0xEA, 0x76, 0xB3, 0x2E, 0x7D, 0xF2 };
 
  // LoRaWAN end-device address (DevAddr)
  static const u4_t DEVADDR = 0x26011AAF; 
 
  void os_getArtEui (u1_t* buf) { }
  void os_getDevEui (u1_t* buf) { }
  void os_getDevKey (u1_t* buf) { }
 
#endif


     
    void onEvent (ev_t ev) {
      Serial.print(os_getTime());
      #ifdef OLED
       u8x8.setPowerSave(0);
      u8x8.begin();
      u8x8.setFont(u8x8_font_chroma48medium8_r);
      u8x8.drawString(0, 1, "radiona.org");
      u8x8.setCursor(0, 5);
      u8x8.printf("TIME %lu", os_getTime());
	#endif

   
      Serial.print(": ");
      switch (ev) {
        case EV_SCAN_TIMEOUT:
          Serial.println(F("EV_SCAN_TIMEOUT"));

	#ifdef OLED
           u8x8.drawString(0, 7, "EV_SCAN_TIMEOUT");
	#endif
          

          break;
        case EV_BEACON_FOUND:
          Serial.println(F("EV_BEACON_FOUND"));

         #ifdef OLED
 		u8x8.drawString(0, 7, "EV_BEACON_FOUND");
	 #endif
          
          break;
        case EV_BEACON_MISSED:
          Serial.println(F("EV_BEACON_MISSED"));
	#ifdef OLED
           u8x8.drawString(0, 7, "EV_BEACON_MISSED");
	#endif
          

          break;
        case EV_BEACON_TRACKED:
          Serial.println(F("EV_BEACON_TRACKED"));
	#ifdef OLED
           u8x8.drawString(0, 7, "EV_BEACON_TRACKED");
	#endif  

          break;
        case EV_JOINING:
          Serial.println(F("EV_JOINING"));
	#ifdef OLED
           u8x8.drawString(0, 7, "EV_JOINING");
	#endif
          

          break;
        case EV_JOINED:
          Serial.println(F("EV_JOINED"));

          #ifdef OLED
           u8x8.drawString(0, 7, "EV_JOINED ");
	#endif

          LMIC_setDrTxpow(DR_SF7, 14); //added fixed SF after join for longer range messages
//          Disable link check validation (automatically enabled
//          during join, but not supported by TTN at this time).
          LMIC_setLinkCheckMode(0);
          break;
        case EV_RFU1:
          Serial.println(F("EV_RFU1"));

          #ifdef OLED
           u8x8.drawString(0, 7, "EV_RFUI");
	  #endif

          break;
        case EV_JOIN_FAILED:
          Serial.println(F("EV_JOIN_FAILED"));
	  #ifdef OLED
           u8x8.drawString(0, 7, "EV_JOIN_FAILED");
	  #endif
          

          break;
        case EV_REJOIN_FAILED:
          Serial.println(F("EV_REJOIN_FAILED"));

          #ifdef OLED
           u8x8.drawString(0, 7, "EV_REJOIN_FAILED");
	  #endif

          break;
        case EV_TXCOMPLETE:
          Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
	  #ifdef OLED
           u8x8.drawString(0, 7, "EV_TXCOMPLETE");
	  #endif  

          digitalWrite(BUILTIN_LED, LOW);
          if (LMIC.txrxFlags & TXRX_ACK) {
            Serial.println(F("Received ack"));
            #ifdef OLED
             u8x8.drawString(0, 7, "Received ACK");
	    #endif

          }
          if (LMIC.dataLen) {
            Serial.println(F("Received "));
            #ifdef OLED
 		u8x8.drawString(0, 6, "RX ");
             	u8x8.setCursor(4, 6);
            	u8x8.printf("%i bytes", LMIC.dataLen);
                u8x8.setCursor(0, 7);
            	u8x8.printf("RSSI %d SNR %.1d", LMIC.rssi, LMIC.snr);
	    #endif
            
            Serial.println(LMIC.dataLen);

            Serial.println(F(" bytes of payload"));

          }

          // Schedule next transmission
          os_setTimedCallback(&sendjob, os_getTime() + sec2osticks(TX_INTERVAL), do_send);
          delay(1000);
          //Increment boot number and print it every reboot
          ++bootCount;
          Serial.println("Boot number: " + String(bootCount));
         // u8x8.setPowerSave(1);

          break;
        case EV_LOST_TSYNC:
          Serial.println(F("EV_LOST_TSYNC"));

          #ifdef OLED
           u8x8.drawString(0, 7, "EV_LOST_TSYNC");
#endif

          break;
        case EV_RESET:
          Serial.println(F("EV_RESET"));
	#ifdef OLED
		u8x8.drawString(0, 7, "EV_RESET");
	#endif
          
          break;
        case EV_RXCOMPLETE:
          //data received in ping slot
          Serial.println(F("EV_RXCOMPLETE"));
	 #ifdef OLED
	 	u8x8.drawString(0, 7, "EV_RXCOMPLETE");
	 #endif
          break;
        case EV_LINK_DEAD:
          Serial.println(F("EV_LINK_DEAD"));
          #ifdef OLED
           u8x8.drawString(0, 7, "EV_LINK_DEAD");
	  #endif

          break;
        case EV_LINK_ALIVE:
          Serial.println(F("EV_LINK_ALIVE"));
          #ifdef OLED
           u8x8.drawString(0, 7, "EV_LINK_ALIVE");
	  #endif

          break;
        default:
          Serial.println(F("Unknown event"));
       
	#ifdef OLED
          u8x8.setCursor(0, 7);
          u8x8.printf("UNKNOWN EVENT %d", ev);
	#endif

          break;
      }
    }
     
    void do_send(osjob_t* j) {
      // Check if there is not a current TX/RX job running
      if (LMIC.opmode & OP_TXRXPEND) {
        Serial.println(F("OP_TXRXPEND, not sending"));
        
	#ifdef OLED
	 u8x8.drawString(0, 7, "OP_TXRXPEND, not sent");
	#endif
        
      } 
	else {
        // Prepare upstream data transmission at the next possible time.
        mydata[0] = currentProject;
        mydata[1] = projectLikes << 8;
        mydata[2] = projectLikes;
        mydata[3] = projectMoney << 8;
        mydata[4] = projectMoney;
        //projectMoney
        //projectLikes
        LMIC_setTxData2(1, mydata, 5, 0);
        Serial.println(F("Packet queued"));
        #ifdef OLED
                u8x8.drawString(0, 7, "PACKET QUEUED");
        #endif
      }
      // Next TX is scheduled after TX_COMPLETE event.
    }

 
void setupLoRa(void){
     
	#ifdef OTA
	      StartOTACheck();
	#endif

      // LMIC init
      os_init();
      // Reset the MAC state. Session and pending data transfers will be discarded.
      LMIC_reset();
     
    #ifndef USE_JOINING
        #ifdef PROGMEM
          // On AVR, these values are stored in flash and only copied to RAM
          // once. Copy them to a temporary buffer here, LMIC_setSession will
          // copy them into a buffer of its own again.
          uint8_t appskey[sizeof(APPSKEY)];
          uint8_t nwkskey[sizeof(NWKSKEY)];
          memcpy_P(appskey, APPSKEY, sizeof(APPSKEY));
          memcpy_P(nwkskey, NWKSKEY, sizeof(NWKSKEY));
          LMIC_setSession (0x1, DEVADDR, nwkskey, appskey);
        #else
          // If not running an AVR with PROGMEM, just use the arrays directly
          LMIC_setSession (0x1, DEVADDR, NWKSKEY, APPSKEY);
        #endif
    #endif

      // Set up the channels used by the Things Network, which corresponds
      // to the defaults of most gateways. Without this, only three base
      // channels from the LoRaWAN specification are used, which certainly
      // works, so it is good for debugging, but can overload those
      // frequencies, so be sure to configure the full frequency range of
      // your network here (unless your network autoconfigures them).
      // Setting up channels should happen after LMIC_setSession, as that
      // configures the minimal channel set.
      // NA-US channels 0-71 are configured automatically
      LMIC_setupChannel(0, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
      LMIC_setupChannel(1, 868300000, DR_RANGE_MAP(DR_SF12, DR_SF7B), BAND_CENTI);      // g-band
      LMIC_setupChannel(2, 868500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
      LMIC_setupChannel(3, 867100000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
      LMIC_setupChannel(4, 867300000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
      LMIC_setupChannel(5, 867500000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
      LMIC_setupChannel(6, 867700000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
      LMIC_setupChannel(7, 867900000, DR_RANGE_MAP(DR_SF12, DR_SF7),  BAND_CENTI);      // g-band
      LMIC_setupChannel(8, 868800000, DR_RANGE_MAP(DR_FSK,  DR_FSK),  BAND_MILLI);      // g2-band
      // TTN defines an additional channel at 869.525Mhz using SF9 for class B
      // devices' ping slots. LMIC does not have an easy way to define set this
      // frequency and support for class B is spotty and untested, so this
      // frequency is not configured here.
     
      // Disable link check validation
      //LMIC_setLinkCheckMode(0);
     
      // TTN uses SF9 for its RX2 window.
      //LMIC.dn2Dr = DR_SF9;
     
     
      LMIC_setDrTxpow(DR_SF7, 14); //set join at SF12
}
