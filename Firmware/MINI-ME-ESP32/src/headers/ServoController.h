#include <Adafruit_PWMServoDriver.h>
#include "config/config.h"

extern Adafruit_PWMServoDriver mainBoard;
extern Adafruit_PWMServoDriver secondBoard;

void setupServos();
void setServoAngle(uint8_t servo, uint8_t angle);
uint16_t angleToPulse(uint8_t angle);