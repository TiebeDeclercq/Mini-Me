// I2C Pinnen
#define I2C_SDA 21
#define I2C_SCL 22

// PWM Configuratie
#define SERVO_FREQ 50 // Frequentie van de PWM signalen voor de servo's
#define SERVOMIN 102 //Minimum puls lengte
#define SERVOMAX 460 //Maximum puls lengte
#define NUM_SERVOS 27 // Aantal servo's

// Servo board configuratie
#define MAIN_BOARD_ADDR 0x40    // Standaard adres voor eerste PCA9685
#define SECOND_BOARD_ADDR 0x41  // Tweede PCA9685 board adres
#define MAIN_BOARD_CHANNELS 16  // Aantal kanalen op het bord

// UDP Configuratie
#define UDP_PORT 5005 // UDP poortnummer

// Bottango Configuration
#define BOTTANGO_COMMUNICATION_MODE 0  // 0 = Serial, 1 = WebSocket
#define BOTTANGO_WEBSOCKET_PORT 59225  // Default Bottango WebSocket port
#define BOTTANGO_SERVER_IP "10.198.112.11"  // IP address for Bottango WebSocket

// Andere random dingen
#define HELE_VELE_OUTPUT true// Zet op true om veel seriële data te ontvangen over alles, false om minder data te ontvangen

//        (\ /)
//       ( . .) ♥ ~< Very cool very noice >
//       c(")(")