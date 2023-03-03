#include <Arduino.h>
#include <SPI.h>

#include "ADS868X.h"
#include "ADS8681.h"

SPISettings settings(1000000, MSBFIRST, SPI_MODE0);

AD7398::AD7398(int cs_pin)
{
	pinMode(cs_pin, OUTPUT);
	digitalWrite(cs_pin, LOW);
	_cs_pin = cs_pin;

    SPI.begin();
}

uint32_t ADS8681::writeRegister(uint8_t command, uint16_t regAddr, uint16_t data)
{
    uint32_t ret = 0;
    uint8_t bytes[4] = {0};
    bytes[0] = (command << 1) | ((regAddr >> 8) & 0x01);
    bytes[1] = (regAddr & 0xFF);
    bytes[2] = (data >> 8);
    bytes[3] = data;
    digitalWrite(SPI_CS, LOW);
    SPI.beginTransaction(settings);
    SPI.transfer(bytes, 4);
    SPI.endTransaction();
    digitalWrite(SPI_CS, HIGH);
    ret = ((uint32_t)bytes[0]) << 24;
    ret |= ((uint32_t)bytes[1]) << 16;
    ret |= ((uint32_t)bytes[2]) << 8;
    ret |= ((uint32_t)bytes[3]);
    return ret;
}

uint16_t ADS8681::readRegister(uint16_t address)
{
    return (uint16_t)(ads8681_writeRegister(ADS868X_READ, address, 0) >> 16);
}

uint16_t ADS8681::readAdc()
{
    return (uint16_t)(ads8681_writeRegister(ADS868X_NOP, 0, 0) >> 16);
}

