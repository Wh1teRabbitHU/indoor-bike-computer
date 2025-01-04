#include "max17055.h"

static I2C_HandleTypeDef * i2c = NULL;

uint16_t MAX17055_readRegister(uint8_t reg) {
    uint16_t measurement = 0;
    uint8_t buffer[2]    = {0};

    HAL_StatusTypeDef result = HAL_I2C_Mem_Read(i2c, MAX17055_I2C_ADDR, reg, sizeof(uint16_t), buffer, sizeof(uint16_t), 1000);

    if (result != HAL_OK) {
        Bike_setError("Error: Couldn't read from the MAX17055 register");
    } else {
        measurement = measurement | buffer[0];
        measurement = measurement | buffer[1] << 8;
    }

    return measurement;
}

void MAX17055_writeRegister(uint8_t reg, uint16_t data) {
    uint8_t buffer[2];

    buffer[0] = data & 255;
    buffer[1] = data >> 8;

    HAL_StatusTypeDef result = HAL_I2C_Mem_Write(i2c, MAX17055_I2C_ADDR, reg, sizeof(uint16_t), buffer, sizeof(uint16_t), 1000);

    if (result != HAL_OK) {
        Bike_setError("Error: Couldn't write to the MAX17055 register");
    }
}

void MAX17055_init(I2C_HandleTypeDef * _i2c) {
    i2c = _i2c;

    volatile uint8_t status     = MAX17055_readRegister(MAX17055_STATUS_REG);
    volatile uint8_t status_POR = status & 0x0002;

    if (status_POR) {
        while (MAX17055_readRegister(MAX17055_FStat_REG) & 1) {
            HAL_Delay(10);                                     // do not continue until FSTAT.DNR == 0
        }

        uint16_t HibCFG = MAX17055_readRegister(0xBA);         // Store original HibCFG value

        MAX17055_writeRegister(MAX17055_SoftWakeup_REG, 0x90); // Exit Hibernate Mode step 1
        MAX17055_writeRegister(MAX17055_HibCfg_REG, 0x0);      // Exit Hibernate Mode step 2
        MAX17055_writeRegister(MAX17055_SoftWakeup_REG, 0x0);  // Exit Hibernate Mode step 3

        uint16_t DesignCap = 4000;
        uint16_t IchgTerm  = 0x0640;
        uint16_t VEmpty    = 0xA561;
        uint16_t dQAcc     = DesignCap / 32;

        // EZ Config

        MAX17055_writeRegister(MAX17055_DesignCap_REG, DesignCap);                 // Write DesignCap
        MAX17055_writeRegister(MAX17055_dQAcc_REG, DesignCap / 32);                // Write dQAcc
        MAX17055_writeRegister(MAX17055_IChgTerm_REG, IchgTerm);                   // Write IchgTerm
        MAX17055_writeRegister(MAX17055_VEmpty_REG, VEmpty);                       // Write VEmpty
                                                                                   // Only use integer portion of dQAcc=int(DesignCap/32) in the calculation of dPAcc to avoid quantization of FullCapNom
        if (MAX17055_CHARGE_VOLTAGE > 4.275) {
            MAX17055_writeRegister(MAX17055_dPAcc_REG, dQAcc * 51200 / DesignCap); // Write dPAcc
            MAX17055_writeRegister(MAX17055_ModelCfg_REG, 0x8400);                 // Write ModelCFG
        } else {
            MAX17055_writeRegister(MAX17055_dPAcc_REG, dQAcc * 44138 / DesignCap); // Write dPAcc
            MAX17055_writeRegister(MAX17055_ModelCfg_REG, 0x8000);                 // Write ModelCFG
        }

        // Poll ModelCFG.Refresh(highest bit), proceed to Step 4 when ModelCFG.Refresh = 0.
        while (MAX17055_readRegister(MAX17055_ModelCfg_REG) & 0x8000) {
            HAL_Delay(10);                                            // 10ms wait loop. Do not continue until ModelCFG.Refresh == 0.
        }

        MAX17055_writeRegister(MAX17055_HibCfg_REG, HibCFG);          // Restore Original HibCFG value

        status = MAX17055_readRegister(MAX17055_STATUS_REG);
        MAX17055_writeRegister(MAX17055_STATUS_REG, status & 0xFFFD); // Write and Verify Status with POR bit cleared
        status = MAX17055_readRegister(MAX17055_STATUS_REG);

        if (status & 0x0002) {
            Bike_setError("Error: Couldn't initialize the MAX17055 module");

            return;
        }
    }

    volatile uint16_t Saved_FullCapRep = MAX17055_readRegister(0x10); // Read FullCapRep
    volatile uint16_t Saved_FullCapNom = MAX17055_readRegister(0x23); // Read FullCapNom
    volatile uint16_t RepCap           = MAX17055_readRegister(0x05);
    volatile uint16_t RepSOC           = MAX17055_readRegister(0x06);
    volatile uint16_t TTE              = MAX17055_readRegister(0x11);

    HAL_Delay(350);

    volatile uint16_t FullCapNom = MAX17055_readRegister(0x23); // Read FullCapNom
    volatile uint16_t MixCap     = (MAX17055_readRegister(0x0D) * FullCapNom) / 25600;
    MAX17055_writeRegister(0x0F, MixCap);                       // WriteAndVerify MixCap
    MAX17055_writeRegister(0x10, Saved_FullCapRep);             // WriteAndVerify FullCapRep
    // Write dQacc to 200% of Capacity and dPacc to 200%
    volatile uint16_t dQacc = (Saved_FullCapNom / 16);
    MAX17055_writeRegister(0x46, 0x0C80); // Write and Verify dPacc
    MAX17055_writeRegister(0x45, dQacc);  // Write and Verify dQacc

    HAL_Delay(350);

    MAX17055_writeRegister(0x17, 0); // WriteAndVerify Cycles

    RepCap = MAX17055_readRegister(0x05);
    RepSOC = MAX17055_readRegister(0x06);
    TTE    = MAX17055_readRegister(0x11);

    status = MAX17055_readRegister(MAX17055_STATUS_REG);
}