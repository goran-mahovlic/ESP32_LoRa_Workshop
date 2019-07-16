# Radiona DonationBoxV3

DonationBox shoud be something like phisical crowd founding.

Inside DonationBoxV3 we Heltec esp32 wifi-lora-32, coin acceptor, display (small or big) and two buttons.

On button press you will get random project on screen, if you press right button you will like that project if you insert money like will be for selected project.

You will need to add pictures, and sounds for this project.

Currently SD card is not working so all pictures are .c files in pic folder

SD card is working normaly with same pins on other ESP32 board, but cannot get it to work on Heltec

You will need to program your coin selector to accept your coins 

https://www.sparkfun.com/products/11719

You will need to change LoRa keys in lora.c

[x] Left button - get random project

[x] Right button - like project

[x] Coin acceptor

[x] Sends changes(in money and likes) to TTN network over LoRa

[ ] Money and likes to selected project

[ ] SD card support

[ ] sounds

[ ] game play if money is inserted...

