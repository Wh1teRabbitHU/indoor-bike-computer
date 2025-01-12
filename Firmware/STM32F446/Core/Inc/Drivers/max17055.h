#ifndef __MAX17055_H
#define __MAX17055_H

#include "bike.h"
#include "macros.h"
#include "main.h"

// More info can be found here: https://www.analog.com/media/en/technical-documentation/user-guides/max17055-software-implementation-guide.pdf

#define MAX17055_I2C_ADDR            0x36 << 1

#define MAX17055_CHARGE_VOLTAGE      4.2

#define MAX17055_STATUS_REG          0x00
#define MAX17055_VA_LRT_TH_REG       0x01
#define MAX17055_TA_LRT_TH_REG       0x02
#define MAX17055_SA_LRT_TH_REG       0x03
#define MAX17055_AT_RATE_REG         0x04
#define MAX17055_REP_CAP_REG         0x05
#define MAX17055_REP_SOC_REG         0x06
#define MAX17055_AGE_REG             0x07
#define MAX17055_TEMP_REG            0x08
#define MAX17055_VCELL_REG           0x09
#define MAX17055_CURRENT_REG         0x0A
#define MAX17055_AVG_CURRENT_REG     0x0B
#define MAX17055_Q_RESIDUAL_REG      0x0C
#define MAX17055_MIX_SOC_REG         0x0D
#define MAX17055_AV_SOC_REG          0x0E
#define MAX17055_MIX_CAP_REG         0x0F

#define MAX17055_FullCapRep_REG      0x10
#define MAX17055_TTE_REG             0x11
#define MAX17055_QRTable00_REG       0x12
#define MAX17055_FullSocThr_REG      0x13
#define MAX17055_RCell_REG           0x14
#define MAX17055_Reserved01_REG      0x15
#define MAX17055_AvgTA_REG           0x16
#define MAX17055_Cycles_REG          0x17
#define MAX17055_DesignCap_REG       0x18
#define MAX17055_AvgVCell_REG        0x19
#define MAX17055_MaxMinTemp_REG      0x1A
#define MAX17055_MaxMinVolt_REG      0x1B
#define MAX17055_MaxMinCurr_REG      0x1C
#define MAX17055_Config_REG          0x1D
#define MAX17055_IChgTerm_REG        0x1E
#define MAX17055_AvCap_REG           0x1F

#define MAX17055_TTF_REG             0x20
#define MAX17055_DevName_REG         0x21
#define MAX17055_QRTable10_REG       0x22
#define MAX17055_FullCapNom_REG      0x23
#define MAX17055_Reserved02_REG      0x24
#define MAX17055_Reserved03_REG      0x25
#define MAX17055_Reserved04_REG      0x26
#define MAX17055_AIN_REG             0x27
#define MAX17055_LearnCfg_REG        0x28
#define MAX17055_FilterCfg_REG       0x29
#define MAX17055_RelaxCfg_REG        0x2A
#define MAX17055_MiscCfg_REG         0x2B
#define MAX17055_TGain_REG           0x2C
#define MAX17055_TOff_REG            0x2D
#define MAX17055_CGain_REG           0x2E
#define MAX17055_COff_REG            0x2F

#define MAX17055_Reserved05_REG      0x30
#define MAX17055_Reserved06_REG      0x31
#define MAX17055_QRTable20_REG       0x32
#define MAX17055_Reserved07_REG      0x33
#define MAX17055_DieTemp_REG         0x34
#define MAX17055_FullCap_REG         0x35
#define MAX17055_Reserved08_REG      0x36
#define MAX17055_Reserved09_REG      0x37
#define MAX17055_RComp0_REG          0x38
#define MAX17055_TempCo_REG          0x39
#define MAX17055_VEmpty_REG          0x3A
#define MAX17055_Reserved10_REG      0x3B
#define MAX17055_Reserved11_REG      0x3C
#define MAX17055_FStat_REG           0x3D
#define MAX17055_Timer_REG           0x3E
#define MAX17055_ShdnTimer_REG       0x3F

#define MAX17055_UserMem1_REG        0x40
#define MAX17055_Reserved12_REG      0x41
#define MAX17055_QRTable30_REG       0x42
#define MAX17055_RGain_REG           0x43
#define MAX17055_Reserved13_REG      0x44
#define MAX17055_dQAcc_REG           0x45
#define MAX17055_dPAcc_REG           0x46
#define MAX17055_Reserved14_REG      0x47
#define MAX17055_Reserved15_REG      0x48
#define MAX17055_ConvgCfg_REG        0x49
#define MAX17055_VFRemCap_REG        0x4A
#define MAX17055_Reserved16_REG      0x4B
#define MAX17055_Reserved17_REG      0x4C
#define MAX17055_QH_REG              0x4D
#define MAX17055_Reserved18_REG      0x4E
#define MAX17055_Reserved19_REG      0x4F

#define MAX17055_Status2_REG         0xB0
#define MAX17055_Power_REG           0xB1
#define MAX17055_ID_UserMem2_REG     0xB2
#define MAX17055_AvgPower_REG        0xB3
#define MAX17055_IAlrtTh_REG         0xB4
#define MAX17055_TTFCfg_REG          0xB5
#define MAX17055_CVMixCap_REG        0xB6
#define MAX17055_CVHalfTime_REG      0xB7
#define MAX17055_CGTempCo_REG        0xB8
#define MAX17055_Curve_REG           0xB9
#define MAX17055_HibCfg_REG          0xBA
#define MAX17055_Config2_REG         0xBB
#define MAX17055_VRipple_REG         0xBC
#define MAX17055_RippleCfg_REG       0xBD
#define MAX17055_TimerH_REG          0xBE
#define MAX17055_Reserved20_REG      0xBF

#define MAX17055_RSense_UserMem3_REG 0xD0
#define MAX17055_ScOcvLim_REG        0xD1
#define MAX17055_Reserved21_REG      0xD2
#define MAX17055_SOCHold_REG         0xD3
#define MAX17055_MaxPeakPower_REG    0xD4
#define MAX17055_SusPeakPower_REG    0xD5
#define MAX17055_PackResistance_REG  0xD6
#define MAX17055_SysResistance_REG   0xD7
#define MAX17055_MinSysVoltage_REG   0xD8
#define MAX17055_MPPCurrent_REG      0xD9
#define MAX17055_SPPCurrent_REG      0xDA
#define MAX17055_ModelCfg_REG        0xDB
#define MAX17055_AtQResidual_REG     0xDC
#define MAX17055_AtTTE_REG           0xDD
#define MAX17055_AtAvSOC_REG         0xDE
#define MAX17055_AtAvCap_REG         0xDF

#define MAX17055_SoftWakeup_REG      0x60

typedef struct MAX17055_measurements {
    uint16_t instantVoltage;
    uint16_t instantCurrent;
    uint16_t stateOfCharge;
    uint16_t instantCapacity;
    uint16_t timeToEmpty;
    uint16_t status;
    uint16_t temperature;
} MAX17055_measurements;

void MAX17055_init(I2C_HandleTypeDef * i2c);
void MAX17055_readMeasurements(MAX17055_measurements * measurements);

#endif