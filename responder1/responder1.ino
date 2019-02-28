#include "common.h" 
#include "config.h"
#include "myfi.h"
#include "MqttLite.h"
#include "otaHelper.h"
#include <Timer.h>   // https://github.com/JChristensen/Timer
int led = 2;
Timer T;
Config C;
MqttLite M;
//OtaHelper O;

void setup() {
    init_serial();
    init_hardware();
    C.init();
    C.dump();   
    M.init (&C);
    //O.init (&C, &M);
    M.publish("The MQTT responder is listening...");
}

void loop() {
    T.update(); 
    M.update();    
}

void init_hardware() {
    pinMode(led, OUTPUT);  
    blinker();
}

void init_serial () {
    #ifdef ENABLE_DEBUG
        Serial.begin(BAUD_RATE); 
        #ifdef VERBOSE_MODE
          Serial.setDebugOutput(true);
        #endif
        Serial.setTimeout(250);
    #endif    
    SERIAL_PRINTLN("\n*******  MQTT Responder starting... ********\n"); 
}

void blinker() {
    for (int i=0; i<6; i++) {
        digitalWrite(led, LOW);
        delay(100);
        digitalWrite(led, HIGH);
        delay(100);        
    }
}

/*
void check_for_updates() {
    SERIAL_PRINTLN ("\n<<<<<<---------  checking for FW updates... ----------->>>>>>\n");
    int result = O.check_and_update();  // if there was an update, this will restart 8266
    SERIAL_PRINT ("OtaHelper: response code: ");   // if the update failed
    SERIAL_PRINTLN (result);
    T.oscillate(led, 500, HIGH, 2);  // ready to read the command button
}
*/

//-----------------------------------------------------------------------------------

void  app_callback(const char* command_string) {
    SERIAL_PRINTLN ("app_callback: MQTT message received :");
    SERIAL_PRINTLN (command_string);
    if (command_string[0]=='O' && command_string[1]=='N') {
        SERIAL_PRINTLN ("Remote command: ON");
        T.oscillate(led,50,HIGH,8);
        M.publish("The relay is ON");
    }
    else
    if (command_string[0]=='O' && command_string[1]=='F' && 
        command_string[2]=='F') {
        SERIAL_PRINTLN ("Remote command: OFF");
        T.oscillate(led,200,HIGH,4);
        M.publish("The relay is switched OFF");
    }    
    /***
    else
    if (command_string[0]=='E' && command_string[1]=='X' && 
        command_string[2]=='I' && command_string[3]=='T') {
        SERIAL_PRINTLN ("Remote cam app has terminated !");
        if (C.sleep_deep) {
            M.publish("RemCam Button goes to sleep..");
            digitalWrite (led, LOW);
            delay(2000);
            digitalWrite (led, HIGH);
            ESP.deepSleep(0);
        }
        else
            T.pulse(led,2000,HIGH);
    }   
    ***/  
}
