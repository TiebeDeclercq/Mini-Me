#include <WebServer.h>
#include <EEPROM.h>
#include "config/credentials.h"

extern WebServer server;

void setupWiFi();
void handleWebClient();
bool isInConfigMode();
void saveWiFiCredentials(const char* ssid, const char* password);