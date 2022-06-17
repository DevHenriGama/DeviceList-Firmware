#include<Arduino.h>
#include <ESP8266WiFi.h>
#include<ESP8266WiFiMulti.h>
#include<ESP8266HTTPClient.h>
#include<WiFiClient.h>
#include<ArduinoJson.h>

//Wifi 
const char* ssid = "Ze12";
const char* pass = "12345678";

// List | Lista 
String names[10];
String address[10];


void setup() {
Serial.begin(115200);
WiFi.begin(ssid,pass);

   while(!WifiStatus()){
    delay(1000);
    Serial.print(".");
   }

}

void loop() {
 //End-Point Settings  | Configuração do End-point
  if(WifiStatus){
   HTTPClient http;
   WiFiClient WClient;
    http.begin(WClient,"http://192.168.100.7:8082/data");//End-point url
    int httpCode = http.GET();

    if(httpCode > 0){
      String payload = http.getString();
      process_request(payload);
    }
    http.end();
  }
 delay(1000);
}

bool WifiStatus(){
  if(WiFi.status() != WL_CONNECTED){
    return false;
  }else{
    return true;
  }
}
void process_request(String package){
  //JSON 
 DynamicJsonDocument doc(1024);
 deserializeJson(doc,package);
   const int NumDev = doc["total"];

    //Create list of Devices with Address and names.
    //Cria a List de dispositivos com nome e endereço.
   for(int i = 0; i < NumDev; i++){
     String DEVName = doc["Device"+String(i)][0];
     String DEVAddr = doc["Device"+String(i)][1];
     names[i] = DEVName;
     address[i] = DEVAddr; 
  }
}
