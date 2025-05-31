/*
 * pca9685.c
 *
 *  Created on: Feb 19, 2025
 *      Author: tiebe
 */

#include "pca9685.h"
#include "display.h"  // For display_message function
#include <stdio.h>

/*
// External I2C handle declaration
extern I2C_HandleTypeDef hi2c2;

void PCA9685_Init(void)
{
		// Software reset
	    uint8_t reset_data = 0x06;
	    HAL_I2C_Master_Transmit(&hi2c2, 0x00, &reset_data, 1, 100);
	    HAL_Delay(10);

	    // Set PWM frequency to ~50Hz
	    uint8_t prescale = 0x7A;  // 122 decimal
	    HAL_I2C_Mem_Write(&hi2c2, PCA9685_ADDRESS, PCA9685_PRE_SCALE, 1, &prescale, 1, 100);

	    // Enable auto-increment and normal mode
	    uint8_t mode1_settings = 0x20;
	    HAL_I2C_Mem_Write(&hi2c2, PCA9685_ADDRESS, PCA9685_MODE1, 1, &mode1_settings, 1, 100);
}
*/
void PCA9685_SetSinglePwm(uint8_t index, uint16_t pwm)
{
    uint8_t i2cData[3];

    // Limit to 16 outputs
    index &= 0x0F;

    // Limit to 12-bit value
    pwm &= 0x0FFF;

    // Find correct register
    i2cData[0] = PCA9685_LED0_OFF_L + index * 4;

    // Split PWM value into two 8-bit values
    i2cData[1] = (uint8_t)(pwm & 0x00FF);
    i2cData[2] = (uint8_t)((pwm >> 8) & 0x000F);

    // Send data
    //HAL_I2C_Mem_Write(&hi2c2, PCA9685_ADDRESS, i2cData[0], 1, &i2cData[1], 2, 100);
}

void PCA9685_SetAllPwm(uint16_t* pwm_values)
{
    uint8_t i2cData[32];  // 16 channels × 2 bytes per channel
    uint8_t dataIndex = 0;

    for(uint8_t channel = 0; channel < 16; channel++)
    {
        uint16_t pwm = pwm_values[channel] & 0x0FFF;  // Limit to 12-bit
        i2cData[dataIndex++] = (uint8_t)(pwm & 0x00FF);
        i2cData[dataIndex++] = (uint8_t)((pwm >> 8) & 0x000F);
    }

    // Write all values at once starting from LED0_OFF_L
    //HAL_I2C_Mem_Write(&hi2c2, PCA9685_ADDRESS, PCA9685_LED0_OFF_L, 1, i2cData, 32, 100);
}

uint16_t AngleToPWM(float angle)
{
    // Convert angle (0-180) to PWM value (102-512 approximately)
    angle = (angle < 0) ? 0 : (angle > 180) ? 180 : angle;  // Constrain angle
    return (uint16_t)((angle * (511.9 - 102.4) / 180.0) + 102.4);
}
