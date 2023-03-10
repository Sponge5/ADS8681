#include "ADS8681.h"

#define ADS8681_CS_PIN  2

ADS8681 adc(ADS8681_CS_PIN);

void setup()
{
    Serial.begin(115200);
    /* Set input range to 0-5.12V */
    uint32_t range_sel_reg = 0;
    range_sel_reg |= (uint32_t)
        ADS8681_RANGE_SEL_UP_1_25_VREF
        & ADS8681_RANGE_SEL_MASK
        << ADS8681_RANGE_SEL_SHIFT;
    adc.spiSend(
            ADS868X_SPI_COMMAND_WRITE_FULL,
            ADS868X_REGISTER_ADDRESS_RANGE_SEL,
            range_sel_reg);
}

void loop()
{
    Serial.println(adc.adcRead());
    delay(1000);
}

