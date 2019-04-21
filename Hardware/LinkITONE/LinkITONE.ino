 /**
 * Helloworld style, connect an ESP8266 to the IBM IoT Foundation
 * 
 * Author: Ant Elder
 * License: Apache License v2
 */

#include <PubSubClient.h> // https://github.com/knolleary/pubsubclient/releases/tag/v2.3
#include <LWiFi.h>
#include <LWiFiClient.h>
#include <LWiFiServer.h>
#include <LWiFiUdp.h>
//-------- Customise these values -----------
const char* ssid = "OnePlus2";
const char* password = "NULL";

#define ORG "wp5ocx"
#define DEVICE_TYPE "ParkCure_Hardware"
#define DEVICE_ID "2CF7F1014C3E"
#define TOKEN "parkcure"
//-------- Customise the above values --------

char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/evt/status/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

LWiFiClient wifiClient;
PubSubClient client(server, 1883, NULL, wifiClient);

void setup() {
 Serial.begin(115200);
 Serial.println();

 Serial.print("Connecting to "); Serial.print(ssid);
  LWiFi.begin();
  // Keep retrying until connected to AP
  Serial.println("Connecting to AP");
  while (0 == LWiFi.connect(ssid, LWiFiLoginInfo(LWIFI_OPEN, password)))
  {
    delay(1000);
  }
  Serial.println("Connected to AP");
}

int counter = 0;

void loop() {

 if (!client.connected()) {
 Serial.print("Reconnecting client to ");
 Serial.println(server);
 while (!!!client.connect(clientId, authMethod, token)) {
 Serial.print(".");
 delay(500);
 }
 Serial.println();
 }

 String payload = "{\"d\":{\"myName\":\"ESP8266.Test1\",\"counter\":";
 payload += counter;
 payload += "}}";
 
 Serial.print("Sending payload: ");
 Serial.println(payload);
 
 if (client.publish(topic, (char*) payload.c_str())) {
 Serial.println("Publish ok");
 } else {
 Serial.println("Publish failed");
 }

 ++counter;
 delay(10000);
}
