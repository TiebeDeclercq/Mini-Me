#include "src/BottangoCore.h"
#include "src/BasicCommands.h"
#include <Wire.h>
#include "headers/ServoController.h"
#include "headers/UDPHandler.h"
#include "headers/WebConfig.h"
#include "headers/UartHandler.h"

// Add the I2C scanning function
void scanI2CDevices() {
  byte error, address;
  int deviceCount = 0;
  
  Serial.println("Scanning I2C bus...");
  
  for(address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println();
      deviceCount++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  
  if (deviceCount == 0) {
    Serial.println("No I2C devices found");
  } else {
    Serial.print("Found ");
    Serial.print(deviceCount);
    Serial.println(" device(s)");
  }
}

void setup()
{
  
  Serial.begin(115200); 
  Serial.println("Mini-me gestart");
  
  // Activeer de interne pull-up weerstanden
  pinMode(21, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  
  // Initialize I2C with improved settings
  Wire.begin();
  Wire.setClock(400000); // Set I2C clock speed to 400kHz

  // Scan for connected I2C devices
  scanI2CDevices();
  
  // Add delay before accessing I2C devices
  delay(100);
  
  // Initialize servos
  setupServos();
  
  // Setup UART for mode switching
  setupUart();
  
  // Initialize WiFi
  setupWiFi();
  uint8_t mac[6];
  WiFi.macAddress(mac);
  
  char macStr[18] = {0};
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.print("Mac address: ");
  Serial.println(macStr);
  
  // Check if we're connected to a network
  if (!isInConfigMode()) {
      // If connected, start the UDP communication
      // Start in UDP mode by default
      setupUDP();
      stelModusIn(MODE_NORMAL);
  }
  
  // Initialize Bottango in the background so it's ready
  // but don't start it actively yet
  
  BottangoCore::bottangoSetup();
}

void loop()
{
  
  // Handle different modes with improved error handling
  if (isInConfigMode()) {
    // In config mode, handle the webserver for network connection
    handleWebClient();
  } 
  else {
    try {
      switch (getModus()) {
        case MODE_NORMAL:
          // Handle UDP packets in normal mode
          handleUDPPackets();
          break;
          
        case MODE_BOTTANGO:
        case MODE_ANIMATION:
          // Bottango or Animation mode
          BottangoCore::bottangoLoop();
          break;
      }
    } catch(...) {
      // Error recovery - if any mode crashes, fall back to UDP mode
      Serial.println("Error in loop() - switching to UDP mode");
      stelModusIn(MODE_NORMAL);
      if (BottangoCore::initialized) {
        BottangoCore::stop();
      }
      setupUDP();
      delay(100); // Give system time to stabilize
    }
  }
    
    
   //BottangoCore::bottangoLoop();
}