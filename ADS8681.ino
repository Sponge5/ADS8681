#include <Arduino.h>
#include <stdint.h>
#include <SPI.h>
#include <Wire.h>
#include <ArduinoLog.h>
#include "ADS868X.h"

#define LOG_LEVEL   LOG_LEVEL_VERBOSE
//#define LOG_LEVEL   LOG_LEVEL_NOTICE

#define SPI_CS          2

uint8_t serialInput;
uint16_t ads8681_register;

void setup()
{
    Serial.begin(115200);         /* Initialize the serial port to the PC */

    pinMode(SPI_CS, OUTPUT);
    SPI.begin();

    Log.begin(LOG_LEVEL, &Serial);
    Log.notice(F("ADS8681-FW Start\r\n"));
}

uint32_t ads8681_writeRegister(uint8_t command, uint16_t regAddr, uint16_t data)
{
    uint32_t ret = 0;
    uint8_t bytes[4] = {0};
    bytes[0] = (command << 1) | ((regAddr >> 8) & 0x01);
    bytes[1] = (regAddr & 0xFF);
    bytes[2] = (data >> 8);
    bytes[3] = data;
    digitalWrite(SPI_CS, LOW);
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    SPI.transfer(bytes, 4);
    SPI.endTransaction();
    digitalWrite(SPI_CS, HIGH);
    ret = ((uint32_t)bytes[0]) << 24;
    ret |= ((uint32_t)bytes[1]) << 16;
    ret |= ((uint32_t)bytes[2]) << 8;
    ret |= ((uint32_t)bytes[3]);
    return ret;
}

uint16_t ads8681_readRegister(uint16_t address)
{
    return (uint16_t)(ads8681_writeRegister(ADS868X_READ, address, 0) >> 16);
}

uint16_t ads8681_readAdc()
{
    return (uint16_t)(ads8681_writeRegister(ADS868X_NOP, 0, 0) >> 16);
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
