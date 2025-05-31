#include "headers/ServoController.h"

Adafruit_PWMServoDriver mainBoard = Adafruit_PWMServoDriver(MAIN_BOARD_ADDR);
Adafruit_PWMServoDriver secondBoard = Adafruit_PWMServoDriver(SECOND_BOARD_ADDR);

// Initialiseer de servo's
void setupServos() {
    mainBoard.begin();
    mainBoard.setOscillatorFrequency(27000000); // Interne frequentie van de PCA9685
    mainBoard.setPWMFreq(SERVO_FREQ); // Frequentie van de PWM signalen voor de servo's
    
    secondBoard.begin();
    secondBoard.setOscillatorFrequency(27000000);
    secondBoard.setPWMFreq(SERVO_FREQ);
}

 // Zet de hoek van een servo in
void setServoAngle(uint8_t servo, uint8_t angle) {
    if(servo < NUM_SERVOS && angle <= 180) {
        // Bereken op welk board de servo zit en welk kanaal
        if (servo < MAIN_BOARD_CHANNELS) {
            // Servo zit op het hoofdboard
            mainBoard.setPWM(servo, 0, angleToPulse(angle));
            Serial.printf("Servo %d (hoofdboard) ingesteld op %d graden\n", servo, angle);
        } else {
            // Servo zit op het tweede board
            // Bereken de juiste kanaalindex voor het tweede board
            uint8_t secondBoardChannel = servo - MAIN_BOARD_CHANNELS;
            secondBoard.setPWM(secondBoardChannel, 0, angleToPulse(angle));
            Serial.printf("Servo %d (tweede board, kanaal %d) ingesteld op %d graden\n", 
                           servo, secondBoardChannel, angle);
        }
    }
}

// Zet een hoek om naar een puls lengte
uint16_t angleToPulse(uint8_t angle) {
    return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}