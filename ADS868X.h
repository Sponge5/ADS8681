/* ADS868X.h - Header for interfaceing with ADS868X ADC */

#ifndef __ADS868X_H__
#define __ADS868X_H__

/* Register Locations and Names */
#define ADS868X_DEVICE_ID_REG   0x00
#define ADS868X_RST_PWRCTL_REG  0x04
#define ADS868X_SDI_CTL_REG     0x08
#define ADS868X_SDO_CTL_REG     0x0C
#define ADS868X_DATAOUT_CTL_REG 0x10
#define ADS868X_RANGE_SEL_REG   0x14
#define ADS868X_ALARM_REG       0x20
#define ADS868X_ALARM_H_TH_REG  0x24
#define ADS868X_ALARM_L_TH_REG  0x28

#define ADS868X_RANGE_SEL_BITMASK     0x0F
#define ADS868X_RANGE_SEL_BITSHIFT    0x00
#define ADS868X_INTREF_DIS_BITMASK    0x40
#define ADS868X_INTREF_DIS_BITSHIFT   0x06

/* SPI commands */
#define ADS868X_NOP             0b0000000
#define ADS868X_CLEAR_HWORD     0b1100000
#define ADS868X_READ_HWORD      0b1100100
#define ADS868X_READ            0b0100100
#define ADS868X_WRITE_FULL      0b1101000
#define ADS868X_WRITE_MS        0b1101001
#define ADS868X_WRITE_LS        0b1101010
#define ADS868X_SET_HWORD       0b1101100

#endif /* __ADS868X_H__ */
