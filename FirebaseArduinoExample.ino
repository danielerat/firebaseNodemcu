
 
#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "********* Your Wifi name ***********"
#define WIFI_PASSWORD "********* Your Wifi Password***********"

// Insert Firebase project API Key
#define API_KEY "********* Your Firebase Api Key ***********"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "********* Your Database URL ***********"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

// --------------
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
// Sensor Location
String BridgeId="1";

double Latitude=-1.184088;
double Longitude=27.047712;
// Database Path
String mainPath;
//Led Value
int red=14;
int green=13;
int blue=12;
int sensor=15;
// --------------
void setup(){
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Trying to connect you on a wifi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    //Blink Red Led As long as Wifi Is Not Connected
    digitalWrite(red,HIGH);
    delay(150);
    digitalWrite(red,LOW);
    delay(150);
  }
  Serial.println();
  Serial.print("Yo yo, I made it. Your Ip Is: ");
   digitalWrite(green,HIGH);
   digitalWrite(red,LOW);
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  timeClient.begin();
}

// -------------------------
// Function to get the epochTime
unsigned long getTime() {
  timeClient.update();
  unsigned long now = timeClient.getEpochTime();
  return now;
}
//Function to generate some radom nonsense values
 double sensorValue(double minf, double maxf)
{
  return minf + random(1UL << 31) * (maxf - minf) / (1UL << 31);  // use 1ULL<<63 for max double values)
}



void saveWeight() {
  //Create new json instance
  FirebaseJson json;

  
  // Sensor Data
  json.set("BridgeId",BridgeId);
  json.set("VehicleWeight",sensorValue(300,350));
  json.set("Humidity", sensorValue(30,50));
  json.set("Latitude",Latitude);
  json.set("Longitude",Longitude);
  json.set("Time", getTime());
  
  if(Firebase.ready() && signupOK ){
  mainPath = "Bridges/"+String(getTime());
    if (Firebase.RTDB.set(&fbdo, mainPath,&json)){
      Serial.println("Vehicle weight saved successfully");
      Serial.println("PATH: " + fbdo.dataPath() + " Type " + fbdo.dataType());
       digitalWrite(blue,HIGH);
       delay(500);
       digitalWrite(blue,LOW);
        delay(500);
        digitalWrite(blue,HIGH);
       delay(500);
       digitalWrite(blue,LOW);
        delay(500);
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
  
}

// Function to save to the database when electicity goes on or off 
void TrackPowerForActions(){
   int currentStatus = digitalRead(sensor);
   if (currentStatus==1) {
     //Saving to the database
        saveWeight();
        delay(5000);
        
      
   }

}



void loop(){
  TrackPowerForActions();
  delay(1000);
}
