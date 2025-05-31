#include "headers/UartHandler.h"
#include "headers/UDPHandler.h"
#include "headers/WebConfig.h"
#include "src/BottangoCore.h"
#include "config/config.h" 

String serialBuffer = "";      // Buffer voor inkomende seriële data
int currentMode = MODE_NORMAL; // Start in normale modus

// External animation control variables from BottangoArduinoCallbacks.cpp
extern volatile int requestedAnimationIndex;
extern volatile bool requestedAnimationLoop;
extern volatile bool stopAnimationRequested;

void setupUart() {
    Serial2.begin(115200, SERIAL_8N1, 33, 32); // RX, TX
    Serial2.onReceive(serialEvent2);
}

// UART interrupt handler
void serialEvent2() {
    while (Serial2.available()) {
        char inChar = (char)Serial2.read();
        
        if (inChar == '\n') {
            processCommand(serialBuffer);
            serialBuffer = ""; // Clear the buffer
        }
        else {
            serialBuffer += inChar; // Add to buffer
        }
    }
}

void processCommand(String command) {
    command.trim(); 
    
    if(HELE_VELE_OUTPUT){
        Serial.print("Received command: ");
        Serial.println(command);
    }
    
    if (command == "UDP_MODE") {
        if (getModus() != MODE_NORMAL) {
            Serial.println("Switching to UDP mode");
            
            // Stop Bottango if it's running
            if (getModus() == MODE_BOTTANGO || getModus() == MODE_ANIMATION) {
                BottangoCore::stop();
            }
            
            // Start UDP
            setupUDP();
            stelModusIn(MODE_NORMAL);
            
            // Confirmation response
            Serial2.println("MODE_SWITCHED:UDP");
        }
    } 
    else if (command == "BOTTANGO_MODE") {
        if (getModus() != MODE_BOTTANGO) {
            Serial.println("Switching to Bottango mode");
            
            // Stop UDP if it's running
            if (getModus() == MODE_NORMAL) {
                stopUDP();
            }
            
            // Initialize Bottango directly (uncomment the setup call in main.cpp)
            stelModusIn(MODE_BOTTANGO);
            
            // Confirmation response
            Serial2.println("MODE_SWITCHED:BOTTANGO");
        }
    }
   else if (command == "ANIMATIES_MODE") {
    Serial.println("Switching to Animation mode");
    
    // Stop UDP if it's running
    if (getModus() == MODE_NORMAL) {
        stopUDP();
    }
    
    // Switch to animation mode
    stelModusIn(MODE_ANIMATION);
    
    // Confirmation response
    Serial2.println("MODE_SWITCHED:ANIMATIES");
}
     else if (command.startsWith("PLAY_ANIMATION:") || command.startsWith("LOOP_ANIMATION:")) {
    bool shouldLoop = command.startsWith("LOOP_ANIMATION:");
    
    // Extract animation index from command
    int separatorPos = command.indexOf(':');
    if (separatorPos != -1) {
        String indexStr = command.substring(separatorPos + 1);
        byte animIndex = indexStr.toInt();
        
        // Switch to animation mode if needed
        if (getModus() != MODE_ANIMATION) {
            if (getModus() == MODE_NORMAL) {
                stopUDP();
            }
            stelModusIn(MODE_ANIMATION);
        }
        
        // Set the request variables instead of calling startCommandStream directly
        requestedAnimationIndex = animIndex;
        requestedAnimationLoop = shouldLoop;
        
        Serial.print("Animation requested: ");
        Serial.print(animIndex);
        Serial.print(" with loop: ");
        Serial.println(shouldLoop);
        
        Serial2.println("ANIMATION_REQUESTED");
    }
}

else if (command == "STOP_ANIMATION") {
    stopAnimationRequested = true;
    Serial2.println("ANIMATION_STOP_REQUESTED");
}
}

void stelModusIn(int mode) {
    currentMode = mode;
}

int getModus() {
    return currentMode;
}