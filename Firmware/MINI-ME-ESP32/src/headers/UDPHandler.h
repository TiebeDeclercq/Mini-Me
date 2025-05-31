#include <WiFiUDP.h>
#include <ArduinoJson.h>
#include "ServoController.h"

extern WiFiUDP udp;
extern char incomingPacket[1024];
extern bool processingPacket;
extern unsigned long packetProcessingStartTime;
extern const unsigned long PACKET_PROCESSING_TIMEOUT;

void setupUDP();
void handleUDPPackets();
void stopUDP();