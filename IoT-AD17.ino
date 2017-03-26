#include <ESP8266WiFi.h>
#include <neotimer.h>

#define BUTTON D0
#define LED D1

Neotimer blinker = Neotimer(500);
Neotimer timeout = Neotimer(5000);
Neotimer debouncer = Neotimer(3000);

WiFiClient client;

const char* ssid     = "frulrom2319";
const char* password = "familiarullan2319";

// Carriots Integration
const char* host = "api.carriots.com";
const char* DEVICE   = "defaultDevice@jrullan.jrullan";
const char* APIKEY = "ff932a7071fac2aa3f0a4005945e1feba1a8cf6269cf014d47d09bc0a2563ed9";

#include "carriots.h"

void setup() {
  pinMode(LED,OUTPUT);
  pinMode(BUTTON,INPUT);
  
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
  /*
   * Allow ESP8266 to perform background tasks
   */
  yield();

  /*
   * Blink led at 1 Hz @ 50% duty cycle
   */
  if(blinker.repeat(500)){
    digitalWrite(LED,!digitalRead(LED));
  }

  /*
   * Checks if button is pressed and timer is not running
   */
  if(digitalRead(BUTTON)==HIGH && !debouncer.waiting()){
    debouncer.start();    
    sendStream("button",false);
    //sendStream("switch",2);
    //sendStream("name","Jose");
    //sendStream("level",50.5);
  }

  /*
   * Resets timer after it finishes
   */
  if(debouncer.done()){
    debouncer.stop();
    //Serial.println("debouncer timer reset");
  }

  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
}

/*
void sendStream(){
  Serial.print("connecting to ");
  Serial.println(host);

 
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  
  // While not available
  while (client.available() == 0) {
    timeout.start();
    if (timeout.done()) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  

  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  
}
*/
