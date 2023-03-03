#ifndef __ADS8681_H__
#define __ADS8681_H__

class ADS8681
{
public:
    ADS8681(int cs_pin);
    uint32_t writeRegister(uint8_t command, uint16_t regAddr, uint16_t data);
    uint16_t readRegister(uint16_t address);
    uint16_t readAdc();
private:
    uint16_t reg;
    int _cs_pin;
}

#endif /* __ADS8681_H__ */
