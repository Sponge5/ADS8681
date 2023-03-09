#include <Arduino.h>

#include "ADS8681.h"

ADS8681::ADS8681(int cs_pin)
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
    digitalWrite(_cs_pin, LOW);
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
    SPI.transfer(bytes, 4);
    SPI.endTransaction();
    digitalWrite(_cs_pin, HIGH);
    ret = ((uint32_t)bytes[0]) << 24;
    ret |= ((uint32_t)bytes[1]) << 16;
    ret |= ((uint32_t)bytes[2]) << 8;
    ret |= ((uint32_t)bytes[3]);
    return ret;
}

//uint16_t ADS8681::readRegister(uint16_t address)
//{
//    return (uint16_t)(this->writeRegister(ADS868X_READ, address, 0) >> 16);
//}
uint32_t ADS8681::readRegister(uint16_t address)
{
    return this->writeRegister(ADS868X_READ, address, 0);
}

uint16_t ADS8681::readAdc()
{
    return (uint16_t)(this->writeRegister(ADS868X_NOP, 0, 0) >> 16);
}

