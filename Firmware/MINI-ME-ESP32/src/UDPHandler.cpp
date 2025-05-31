#include "headers/UDPHandler.h"
#include "config/config.h"
#include "headers/WebConfig.h"
WiFiUDP udp;
char incomingPacket[1024];
bool processingPacket = false; // Variabele om bij te houden of een pakket wordt verwerkt
unsigned long packetProcessingStartTime = 0; // Tijdstip waarop de verwerking van het pakket begon
const unsigned long PACKET_PROCESSING_TIMEOUT = 500; // Timeout van 500 milliseconden

// Initialiseer UDP
void setupUDP() {
    // Always attempt to stop UDP before starting
    udp.stop();
    delay(100);
    
    // Check WiFi connection
    if(WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi not connected, cannot start UDP");
        return;
    }
    
    // Start UDP
    udp.begin(UDP_PORT);
    Serial.printf("UDP listening on port %d with IP %s\n", UDP_PORT, WiFi.localIP().toString().c_str());
}

// Verwerk UDP pakketten
void handleUDPPackets() {
    // Check WiFi connection first
    if(WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi niet verbonden tijdens UDP verwerking!");
        return;
    }
    
    if (processingPacket) {
        // Controleer of de timeout is verstreken
        if (millis() - packetProcessingStartTime > PACKET_PROCESSING_TIMEOUT) {
            processingPacket = false; // Reset de verwerkingsstatus na timeout
            Serial.println("Packet processing timeout, resetting processingPacket flag.");
        } else {
            return; // Weiger inkomende UDP-pakketten als er al een pakket wordt verwerkt
        }
    }

    int packetSize = udp.parsePacket();
    if (packetSize) {
        if (HELE_VELE_OUTPUT){
            Serial.print("UDP pakket ontvangen: grootte=");
            Serial.print(packetSize);
            Serial.print(", van IP=");
            Serial.print(udp.remoteIP());
            Serial.print(", poort=");
            Serial.println(udp.remotePort());
        }
        processingPacket = true; // Begin met het verwerken van een pakket
        packetProcessingStartTime = millis(); // Sla het tijdstip op waarop de verwerking begon

        int len = udp.read(incomingPacket, sizeof(incomingPacket) - 1);
        if (len > 0) {
            incomingPacket[len] = 0;

            if (HELE_VELE_OUTPUT){
                Serial.printf("Ontvangen UDP pakket inhoud: %s\n", incomingPacket);
            }

            StaticJsonDocument<1024> doc;
            DeserializationError error = deserializeJson(doc, incomingPacket);

            if (!error) {
                if(HELE_VELE_OUTPUT){
                    Serial.println("JSON succesvol verwerkt");
                    serializeJson(doc, Serial);
                    Serial.println();
                }
                
                // Enkele servo aansturen
                if (doc.containsKey("servo") && doc.containsKey("angle")) {
                    uint8_t servo = doc["servo"];
                    uint8_t angle = doc["angle"];
                    setServoAngle(servo, angle);
                }
                // Meerdere servo's aansturen
                else if (doc.containsKey("servos")) { // Array van servo's
                    JsonArray servosArray = doc["servos"];
                    Serial.printf("Meerdere servo's opdracht: aantal=%d\n", servosArray.size());
                    
                    for (JsonObject servo : servosArray) { // Loop over de servo's
                        if (servo.containsKey("id") && servo.containsKey("angle")) { // Controleer of de servo een id en hoek heeft
                            uint8_t id = servo["id"];
                            uint8_t angle = servo["angle"];
                            setServoAngle(id, angle); // Stel de hoek van de servo in
                            delay(1); // Wacht 1ms om de servo's niet te snel aan te sturen
                        } else {
                            Serial.println("  Servo mist id of angle in array");
                        }
                    }
                } else {
                    Serial.println("Geen bekende commando's gevonden in JSON");
                }
            } else {
                Serial.printf("Error bij het verwerken van JSON: %s\n", error.c_str());
                Serial.printf("Problematische pakket: %s\n", incomingPacket);
            }
            memset(incomingPacket, 0, sizeof(incomingPacket)); // Clear the buffer
        } else {
            Serial.println("Lege of ongeldige pakket ontvangen");
        }

        processingPacket = false; // Verwerking van het pakket is voltooid
    }
}

// Stop UDP
void stopUDP() {
    udp.flush();
    udp.stop();
    delay(50);
    Serial.println("UDP gestopt");
}