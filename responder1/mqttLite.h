//mqttLite.h
// HiveMQ: http://www.hivemq.com/demos/websocket-client/

#ifndef MQTTLITE_H
#define MQTTLITE_H

#include "config.h"
#include "common.h"
#include "myfi.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>   // https://github.com/knolleary/pubsubclient 

class MqttLite {
  public:
    MqttLite();
    void init(Config* config);
    void update ();
    bool reconnect ();
    void generateClientID ();
    bool subscribe ();
    bool publish (const char *msg);
    //static void callback(char* topic, byte* payload, unsigned int length);   
    int QOS=1; 
  private:
    Config *pC;  
    MyFi  W;
    char mqtt_client_id [MAX_STRING_LENGTH];   
};


#endif
