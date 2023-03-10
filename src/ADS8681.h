#ifndef __ADS8681_H__
#define __ADS8681_H__

#include "ADS868X.h"
#include <SPI.h>

/* DEVICE_ID_REG */
#define ADS8681_DEVICE_ADDR_SHIFT           16
#define ADS8681_DEVICE_ADDR_MASK            0xF

/* RST_PWRCTL_REG */
#define ADS8681_WKEY_SHIFT                  8
#define ADS8681_WKEY_MASK                   0xFF
#define ADS8681_VDD_AL_DIS_SHIFT            5
#define ADS8681_VDD_AL_DIS_MASK             0b1
#define ADS8681_IN_AL_DIS_SHIFT             4
#define ADS8681_IN_AL_DIS_MASK              0b1
#define ADS8681_RSTn_APP_SHIFT              2
#define ADS8681_RSTn_APP_MASK               0b1
#define ADS8681_NAP_EN_SHIFT                1
#define ADS8681_NAP_EN_MASK                 0b1
#define ADS8681_PWRDN_SHIFT                 0
#define ADS8681_PWRDN_MASK                  0b1

/* SDI_CTL_REG */
#define ADS8681_SDI_MODE_SHIFT              0
#define ADS8681_SDI_MODE_MASK               0b11

/* SDO_CTL_REG */
#define ADS8681_GPO_VAL_SHIFT               12
#define ADS8681_GPO_VAL_MASK                0b1
#define ADS8681_SDO1_CONFIG_SHIFT           8
#define ADS8681_SDO1_CONFIG_MASK            0b11
#define ADS8681_SSYNC_CLK_SHIFT             6
#define ADS8681_SSYNC_CLK_MASK              0b1
#define ADS8681_SDO_MODE_SHIFT              0
#define ADS8681_SDO_MODE_MASK               0b11

/* DATAOUT_CTL_REG */
#define ADS8681_DEVICE_ADDR_INCL_SHIFT      14
#define ADS8681_DEVICE_ADDR_INCL_MASK       0b1
#define ADS8681_VDD_ACTIVE_ALARM_INCL_SHIFT 12
#define ADS8681_VDD_ACTIVE_ALARM_INCL_MASK  0b11
#define ADS8681_IN_ACTIVE_ALARM_INCL_SHIFT  10
#define ADS8681_IN_ACTIVE_ALARM_INCL_MASK   0b11
#define ADS8681_RANGE_INCL_SHIFT            8
#define ADS8681_RANGE_INCL_MASK             0b1
#define ADS8681_PAR_EN_SHIFT                3
#define ADS8681_PAR_EN_MASK                 0b1
#define ADS8681_DATA_VAL_SHIFT              0
#define ADS8681_DATA_VAL_MASK               0b111

/* RANGE_SEL_REG */
#define ADS8681_INTREF_DIS_SHIFT            6
#define ADS8681_INTREF_DIS_MASK             0b1
#define ADS8681_RANGE_SEL_SHIFT             0
#define ADS8681_RANGE_SEL_MASK              0xF

#define ADS8681_RANGE_SEL_BP_3_VREF         0b0000  /* = ±3 × VREF */
#define ADS8681_RANGE_SEL_BP_2_5_VREF       0b0001  /* = ±2.5 × VREF */
#define ADS8681_RANGE_SEL_BP_1_5_VREF       0b0010  /* = ±1.5 × VREF */
#define ADS8681_RANGE_SEL_BP_1_25_VREF      0b0011  /* = ±1.25 × VREF */
#define ADS8681_RANGE_SEL_BP_0_625_VREF     0b0100  /* = ±0.625 × VREF */
#define ADS8681_RANGE_SEL_UP_3_VREF         0b1000  /* = 3 × VREF */
#define ADS8681_RANGE_SEL_UP_2_5_VREF       0b1001  /* = 2.5 × VREF */
#define ADS8681_RANGE_SEL_UP_1_5_VREF       0b1010  /* = 1.5 × VREF */
#define ADS8681_RANGE_SEL_UP_1_25_VREF      0b1011  /* = 1.25 × VREF */

/* ALARM_REG */
#define ADS8681_ACTIVE_VDD_L_FLAG_SHIFT     15
#define ADS8681_ACTIVE_VDD_L_FLAG_MASK      0b1
#define ADS8681_ACTIVE_VDD_H_FLAG_SHIFT     14
#define ADS8681_ACTIVE_VDD_H_FLAG_MASK      0b1
#define ADS8681_ACTIVE_IN_L_FLAG_SHIFT      11
#define ADS8681_ACTIVE_IN_L_FLAG_MASK       0b1
#define ADS8681_ACTIVE_IN_H_FLAG_SHIFT      10
#define ADS8681_ACTIVE_IN_H_FLAG_MASK       0b1
#define ADS8681_TRP_VDD_L_FLAG_SHIFT        7
#define ADS8681_TRP_VDD_L_FLAG_MASK         0b1
#define ADS8681_TRP_VDD_H_FLAG_SHIFT        6
#define ADS8681_TRP_VDD_H_FLAG_MASK         0b1
#define ADS8681_TRP_IN_L_FLAG_SHIFT         5
#define ADS8681_TRP_IN_L_FLAG_MASK          0b1
#define ADS8681_TRP_IN_H_FLAG_SHIFT         4
#define ADS8681_TRP_IN_H_FLAG_MASK          0b1
#define ADS8681_OVW_ALARM_SHIFT             0
#define ADS8681_OVW_ALARM_MASK              0b1

/* ALARM_H_TH_REG */
#define ADS8681_INP_ALRM_HYST_SHIFT         24
#define ADS8681_INP_ALRM_HYST_MASK          0xFF
#define ADS8681_INP_ALRM_HIGH_TH_SHIFT      0
#define ADS8681_INP_ALRM_HIGH_TH_MASK       0xFFFF

/* ALARM_L_TH_REG */
#define ADS8681_INP_ALRM_LOW_TH_SHIFT       0
#define ADS8681_INP_ALRM_LOW_TH_MASK        0xFFFF

class ADS8681
{
public:
    ADS8681(int cs_pin);
    uint32_t spiSend(
            enum ads868x_spi_command command,
            enum ads868x_register_address regAddr,
            uint16_t data);
    uint16_t adcRead();
private:
    int _cs_pin;
};

#endif /* __ADS8681_H__ */
