//config.cpp
#include "config.h"

extern void safe_strncpy (char *dest, char *src, int length = MAX_STRING_LENGTH);

Config::Config(){
}

void Config::init() {
    safe_strncpy (firmware_server_url,  FW_SERVER_URL);
    safe_strncpy (version_check_url,    FW_VERSION_URL);
}

void Config::dump() {
    SERIAL_PRINTLN("\n-----------------------------------------");
    SERIAL_PRINTLN("               configuration             ");
    SERIAL_PRINTLN("-----------------------------------------");    
    SERIAL_PRINT ("Firmware version: 1.0.");
    SERIAL_PRINTLN (FIRMWARE_VERSION);
    long freeheap = ESP.getFreeHeap();
    SERIAL_PRINT ("Free heap: ");
    SERIAL_PRINTLN (freeheap);   
    SERIAL_PRINT ("Firmware server URL: ");
    SERIAL_PRINTLN (firmware_server_url);    
    SERIAL_PRINT("Firmware version URL: ");
    SERIAL_PRINTLN(version_check_url);      

    SERIAL_PRINT("MQTT server, port: ");
    SERIAL_PRINT(mqtt_server); 
    SERIAL_PRINT(", ");
    SERIAL_PRINTLN(mqtt_port); 
    SERIAL_PRINT ("Publish topic: ");
    SERIAL_PRINTLN (mqtt_pub_topic); 
    SERIAL_PRINT ("Subscribe topic: ");
    SERIAL_PRINTLN (mqtt_sub_topic); 
    SERIAL_PRINTLN("-----------------------------------------\n");                     
}
 

 
