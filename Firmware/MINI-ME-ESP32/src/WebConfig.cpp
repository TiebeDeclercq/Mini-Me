#include "headers/WebConfig.h"
#include "webpages/connectToWifi.h"

WebServer server(80);

void setupWiFi() {
    EEPROM.begin(512);
    
    // Probeer eerst verbinding te maken met opgeslagen inloggegevens
    String stored_ssid = EEPROM.readString(0);
    String stored_password = EEPROM.readString(32);
    
    if (stored_ssid.length() > 0) {
        WiFi.begin(stored_ssid.c_str(), stored_password.c_str());
        
        int attempts = 0;
        // Wacht tot WiFi is verbonden of tot 5 pogingen zijn gedaan
        while (WiFi.status() != WL_CONNECTED && attempts < 20) {
            delay(500);
            Serial.print(".");
            attempts++;
        }
    }
    
    // Als WiFi niet is verbonden, start configuratieportaal
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("\nStart configuratieportaal");
        WiFi.mode(WIFI_AP);
        WiFi.softAP(AP_SSID);
        
        // Stel de root route in om de HTML-pagina te serveren
        server.on("/", HTTP_GET, []() {
            server.send(200, "text/html", html_page);
        });
        
        // Stel de save route in om de WiFi-inloggegevens op te slaan
        server.on("/save", HTTP_POST, []() {
            String new_ssid = server.arg("ssid");
            String new_password = server.arg("password");
            saveWiFiCredentials(new_ssid.c_str(), new_password.c_str());
            
            String response = "Verbinden met " + new_ssid + "...<br>Als succesvol, zal deze pagina niet langer beschikbaar zijn.<br>Verbind met uw WiFi-netwerk.";
            server.send(200, "text/html", response);
            delay(2000);
            ESP.restart();
        });
        
        server.begin();
        
        Serial.print("Configuratieportaal IP: ");
        Serial.println(WiFi.softAPIP());
    } else {
        Serial.println("\nWiFi verbonden");
        Serial.print("IP-adres: ");
        Serial.println(WiFi.localIP());
    }
}

// Verwerk webclientverzoeken
void handleWebClient() {
    server.handleClient();
}

// Controleer of het apparaat in configuratiemodus is
bool isInConfigMode() {
    return WiFi.getMode() == WIFI_AP;
}

// Sla WiFi-inloggegevens op in EEPROM
void saveWiFiCredentials(const char* ssid, const char* password) {
    EEPROM.writeString(0, ssid);
    EEPROM.writeString(32, password);
    EEPROM.commit();
}