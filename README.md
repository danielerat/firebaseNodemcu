# Introduction

A simple Program to connect the Node MCU Module with Firebase DB for real time data monitoring.

## Use Cases

In most cases if not all the time you may need to save your sensor Data somewhere, This makes use of the 
Arduino Firebase Library to save your data to a RealtimeDB

## Setup/installation

### Install the Aduino IDE 
> You can install the IDE from: [ARDUINO IDE](http://www.arduino.cc/en/main/software)


### Adding the ESP8266 Board Manager
> From Your Arduino IDE go to File > Preferences > Additional Boards Manager 
> Paste this link and click OK: http://arduino.esp8266.com/stable/package_esp8266com_index.json
> Go to Tools > Boards > Board Manager 
> Search for esp8266 By ESP8266 Community and install the package

### Install the FIREBASE LIBRARY
> Go to Sketch > Include Library > Manage Libraries 
> Search For Firebase Esp Client 
> Install the Firebase Arduino Client Library for ESP8266 and ESP32 by (Mobitz)

### Code Modification
``` c++
#define WIFI_SSID "REPLACE_WITH_YOUR_SSID"
#define WIFI_PASSWORD "REPLACE_WITH_YOUR_PASSWORD"
#define API_KEY "REPLACE_WITH_YOUR_FIREBASE_PROJECT_API_KEY"
#define DATABASE_URL "REPLACE_WITH_YOUR_FIREBASE_DATABASE_URL"
```
