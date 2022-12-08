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
uint8_t spiBytes[4];
uint32_t adcValue;

void setup()
{
    Serial.begin(115200);         /* Initialize the serial port to the PC */

    pinMode(SPI_CS, OUTPUT);
    SPI.begin();

    Log.begin(LOG_LEVEL, &Serial);
    Log.notice(F("ADS8681-FW Start\r\n"));
}

void readValue(uint8_t command, uint16_t address, uint16_t data)
{
    adcValue = 0;
    spiBytes[0] = (command << 1) | ((address >> 8) & 0x01);
    spiBytes[1] = (address & 0xFF);
    spiBytes[2] = ((data >> 8) & 0xFF);
    spiBytes[3] = (data & 0xFF);
    digitalWrite(SPI_CS, LOW);
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    SPI.transfer(spiBytes, 4);
    SPI.endTransaction();
    digitalWrite(SPI_CS, HIGH);
    for(uint8_t i = 0; i < 4; ++i)
    {
        adcValue = (adcValue << 8);
        adcValue |= spiBytes[i];
    }
    uint8_t b1 = adcValue >> 16;
    uint8_t b2 = adcValue >> 24;
    uint16_t value = (b2 << 8) | b1;
    //Log.notice("%X %X\r\n", adcValue, adcValue >> 16);
    //Log.notice("%X %X\r\n", (adcValue >> 24) & 0x0F, (adcValue >> 16) & 0x0F);
    Log.notice("%X\r\n", value);
}

void loop()
{
    if (Serial.available())               /* Check for user input */
    {
        serialInput = Serial.read();
        switch(serialInput)
        {
            case 'a':
                readValue(ADS868X_READ, ADS868X_DEVICE_ID_REG, 0x00);
                break;
            case 'b':
                readValue(ADS868X_READ, ADS868X_DATAOUT_CTL_REG, 0x00);
                break;
            default:
                readValue(ADS868X_NOP, 0x00, 0x00);
                break;
        }
    }
    delay(1);
}
