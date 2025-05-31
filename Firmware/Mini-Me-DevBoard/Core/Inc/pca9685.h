/*
 * pca9685.h
 *
 *  Created on: Feb 19, 2025
 *      Author: tiebe
 */

#ifndef INC_PCA9685_H_
#define INC_PCA9685_H_

#include <stdint.h>

// Device address and register definitions
#define PCA9685_ADDRESS     (0x40 << 1)  // 8-bit address format
#define PCA9685_MODE1       0x00
#define PCA9685_MODE2       0x01
#define PCA9685_LED0_ON_L   0x06
#define PCA9685_LED0_OFF_L  0x08
#define PCA9685_PRE_SCALE   0xFE

// Function prototypes
void PCA9685_Init(void);
void PCA9685_SetSinglePwm(uint8_t index, uint16_t pwm);
void PCA9685_SetAllPwm(uint16_t* pwm_values);
uint16_t AngleToPWM(float angle);

#endif /* INC_PCA9685_H_ */
