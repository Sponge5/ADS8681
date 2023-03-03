#include <Arduino.h>
#include <stdint.h>
#include <SPI.h>
#include <Wire.h>
#include <ArduinoLog.h>
#include "ADS868X.h"

#define LOG_LEVEL   LOG_LEVEL_VERBOSE
//#define LOG_LEVEL   LOG_LEVEL_NOTICE

#define SPI_CS          2

ADS8681 adc(SPI_CS);

uint8_t serialInput;

void setup()
{
    Serial.begin(115200);         /* Initialize the serial port to the PC */

    Log.begin(LOG_LEVEL, &Serial);
    Log.notice(F("ADS8681-FW Start\r\n"));
}

void loop()
{
    if (Serial.available())               /* Check for user input */
    {
        serialInput = Serial.read();
        switch(serialInput)
        {
            case 'a':
                ads8681_register = ads8681_readRegister(ADS868X_DEVICE_ID_REG);
                break;
            case 'b':
                ads8681_register = ads8681_readRegister(ADS868X_DATAOUT_CTL_REG);
                break;
            case 'c':
                ads8681_register = ads8681_readRegister(ADS868X_RANGE_SEL_REG);
                Log.notice("RANGE_SEL: %X\r\n",
                        (ads8681_register & ADS868X_RANGE_SEL_BITMASK)
                        >> ADS868X_RANGE_SEL_BITSHIFT);
                Log.notice("INTREF_DIS: %X\r\n",
                        (ads8681_register & ADS868X_INTREF_DIS_BITMASK)
                        >> ADS868X_INTREF_DIS_BITSHIFT);
                break;
            case 'd':
                ads8681_register = ads8681_readRegister(ADS868X_RANGE_SEL_REG);
                ads8681_register |= (0x1 << ADS868X_INTREF_DIS_BITSHIFT);
                ads8681_register = ads8681_writeRegister(
                        ADS868X_WRITE_FULL, ADS868X_RANGE_SEL_REG, ads8681_register);
                break;
            case 'e':
                ads8681_register = ads8681_readRegister(ADS868X_RANGE_SEL_REG);
                ads8681_register &= ~ADS868X_INTREF_DIS_BITMASK;
                ads8681_register = ads8681_writeRegister(
                        ADS868X_WRITE_FULL, ADS868X_RANGE_SEL_REG, ads8681_register);
                break;
            default:
                ads8681_register = ads8681_readAdc();
                Log.notice("%X\r\n", ads8681_register);
                break;
        }
    }
    delay(1);
}
