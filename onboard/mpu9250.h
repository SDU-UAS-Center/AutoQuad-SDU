/*
    This file is part of AutoQuad.

    AutoQuad is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AutoQuad is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with AutoQuad.  If not, see <http://www.gnu.org/licenses/>.

    Copyright © 2011-2014  Bill Nesbitt
*/

#ifndef _mpu9250_h
#define _mpu9250_h

#include "calib.h"
#include "spi.h"
#include "util.h"

#define MPU9250_SPI_REG_BAUD	    SPI_BaudRatePrescaler_64	// initial setup only
#define MPU9250_SPI_RUN_BAUD	    SPI_BaudRatePrescaler_4	// 10.5 MHz

#define MPU9250_READ_BIT	    0x80
#define MPU9250_WRITE_BIT	    0x00
#define MPU9250_DEVICE_ID           0x71  // WHO_AM_I response code

#ifndef MPU9250_USE_AK8963  // should be defined in board file
    #define MPU9250_USE_AK8963      0
#endif

#if MPU9250_USE_AK8963
    #define MPU9250_BYTES           1 + 14 + 6 + 1  // 6x acc/2x temp/6x gyo + 6x mag + 1x magstatus
#else
    #define MPU9250_BYTES           1 + 14  // 6x acc/2x temp/6x gyo
#endif

#define MPU9250_SLOT_SIZE	    ((MPU9250_BYTES+sizeof(int)-1) / sizeof(int) * sizeof(int))

#ifndef MPU9250_SLOTS
    #define MPU9250_SLOTS	    80	// 100Hz GYO/50Hz ACC bandwidth (8KHz/4KHz sensor output rate)
#endif

#define MPU9250_DRATE_SLOTS_QUATOS	(MPU9250_SLOTS * 100.0f * DIMU_INNER_DT * 2.0f) // variable GYO (8KHz sensor output rate)
#define MPU9250_DRATE_SLOTS_PID		40  // 200Hz GYO (8KHz sensor output rate)

#ifndef MPU9250_DRATE_SLOTS
    #ifdef HAS_QUATOS
	#define MPU9250_DRATE_SLOTS	((int)p[QUATOS_ENABLE] ? MPU9250_DRATE_SLOTS_QUATOS : MPU9250_DRATE_SLOTS_PID)
    #else
	#define MPU9250_DRATE_SLOTS	MPU9250_DRATE_SLOTS_PID
    #endif
#endif

// mpu9250 registers
#define MPU9250_REG_SELF_TEST_X_G       0x00
#define MPU9250_REG_SELF_TEST_Y_G       0x01
#define MPU9250_REG_SELF_TEST_Z_G       0x02
//#define MPU9250_REG_X_FINE_GAIN         0x03
//#define MPU9250_REG_Y_FINE_GAIN         0x04
//#define MPU9250_REG_Z_FINE_GAIN         0x05
//#define MPU9250_REG_XA_OFFS_H           0x06
//#define MPU9250_REG_XA_OFFS_L           0x07
//#define MPU9250_REG_YA_OFFS_H           0x08
//#define MPU9250_REG_YA_OFFS_L           0x09
//#define MPU9250_REG_ZA_OFFS_H           0x0A
//#define MPU9250_REG_ZA_OFFS_L           0x0B
//#define MPU9250_REG_PRODUCT_ID          0x0C
#define MPU9250_REG_SELF_TEST_X_A       0x0D
#define MPU9250_REG_SELF_TEST_Y_A       0x0E
#define MPU9250_REG_SELF_TEST_Z_A       0x0F
#define MPU9250_REG_XG_OFFS_H           0x13
#define MPU9250_REG_XG_OFFS_L           0x14
#define MPU9250_REG_YG_OFFS_H           0x15
#define MPU9250_REG_YG_OFFS_L           0x16
#define MPU9250_REG_ZG_OFFS_H           0x17
#define MPU9250_REG_ZG_OFFS_L           0x18
#define MPU9250_REG_SMPLRT_DIV          0x19
#define MPU9250_REG_CONFIG              0x1A
#define MPU9250_REG_GYRO_CONFIG         0x1B
#define MPU9250_REG_ACCEL_CONFIG        0x1C
#define MPU9250_REG_ACCEL_CONFIG_2      0x1D
#define MPU9250_REG_LP_ACCEL_ODR        0x1E
#define MPU9250_REG_MOT_THR             0x1F
#define MPU9250_REG_FIFO_EN             0x23
#define MPU9250_REG_I2C_MST_CTRL        0x24
#define MPU9250_REG_I2C_SLV0_ADDR       0x25
#define MPU9250_REG_I2C_SLV0_REG        0x26
#define MPU9250_REG_I2C_SLV0_CTRL       0x27
#define MPU9250_REG_I2C_SLV1_ADDR       0x28
#define MPU9250_REG_I2C_SLV1_REG        0x29
#define MPU9250_REG_I2C_SLV1_CTRL       0x2A
#define MPU9250_REG_I2C_SLV2_ADDR       0x2B
#define MPU9250_REG_I2C_SLV2_REG        0x2C
#define MPU9250_REG_I2C_SLV2_CTRL       0x2D
#define MPU9250_REG_I2C_SLV3_ADDR       0x2E
#define MPU9250_REG_I2C_SLV3_REG        0x2F
#define MPU9250_REG_I2C_SLV3_CTRL       0x30
#define MPU9250_REG_I2C_SLV4_ADDR       0x31
#define MPU9250_REG_I2C_SLV4_REG        0x32
#define MPU9250_REG_I2C_SLV4_DO         0x33
#define MPU9250_REG_I2C_SLV4_CTRL       0x34
#define MPU9250_REG_I2C_SLV4_DI         0x35
#define MPU9250_REG_I2C_MST_STATUS      0x36
#define MPU9250_REG_INT_PIN_CFG         0x37
#define MPU9250_REG_INT_ENABLE          0x38
#define MPU9250_REG_ACCEL_XOUT_H        0x3B
#define MPU9250_REG_ACCEL_XOUT_L        0x3C
#define MPU9250_REG_ACCEL_YOUT_H        0x3D
#define MPU9250_REG_ACCEL_YOUT_L        0x3E
#define MPU9250_REG_ACCEL_ZOUT_H        0x3F
#define MPU9250_REG_ACCEL_ZOUT_L        0x40
#define MPU9250_REG_TEMP_OUT_H          0x41
#define MPU9250_REG_TEMP_OUT_L          0x42
#define MPU9250_REG_GYRO_XOUT_H         0x43
#define MPU9250_REG_GYRO_XOUT_L         0x44
#define MPU9250_REG_GYRO_YOUT_H         0x45
#define MPU9250_REG_GYRO_YOUT_L         0x46
#define MPU9250_REG_GYRO_ZOUT_H         0x47
#define MPU9250_REG_GYRO_ZOUT_L         0x48
#define MPU9250_REG_EXT_SENS_DATA_00    0x49
#define MPU9250_REG_EXT_SENS_DATA_01    0x4A
#define MPU9250_REG_EXT_SENS_DATA_02    0x4B
#define MPU9250_REG_EXT_SENS_DATA_03    0x4C
#define MPU9250_REG_EXT_SENS_DATA_04    0x4D
#define MPU9250_REG_EXT_SENS_DATA_05    0x4E
#define MPU9250_REG_EXT_SENS_DATA_06    0x4F
#define MPU9250_REG_EXT_SENS_DATA_07    0x50
#define MPU9250_REG_EXT_SENS_DATA_08    0x51
#define MPU9250_REG_EXT_SENS_DATA_09    0x52
#define MPU9250_REG_EXT_SENS_DATA_10    0x53
#define MPU9250_REG_EXT_SENS_DATA_11    0x54
#define MPU9250_REG_EXT_SENS_DATA_12    0x55
#define MPU9250_REG_EXT_SENS_DATA_13    0x56
#define MPU9250_REG_EXT_SENS_DATA_14    0x57
#define MPU9250_REG_EXT_SENS_DATA_15    0x58
#define MPU9250_REG_EXT_SENS_DATA_16    0x59
#define MPU9250_REG_EXT_SENS_DATA_17    0x5A
#define MPU9250_REG_EXT_SENS_DATA_18    0x5B
#define MPU9250_REG_EXT_SENS_DATA_19    0x5C
#define MPU9250_REG_EXT_SENS_DATA_20    0x5D
#define MPU9250_REG_EXT_SENS_DATA_21    0x5E
#define MPU9250_REG_EXT_SENS_DATA_22    0x5F
#define MPU9250_REG_EXT_SENS_DATA_23    0x60
#define MPU9250_REG_I2C_SLV0_DO         0x63
#define MPU9250_REG_I2C_SLV1_DO         0x64
#define MPU9250_REG_I2C_SLV2_DO         0x65
#define MPU9250_REG_I2C_SLV3_DO         0x66
#define MPU9250_REG_I2C_MST_DELAY_CTRL  0x67
#define MPU9250_REG_SIGNAL_PATH_RESET   0x68
#define MPU9250_REG_MOT_DETECT_CTRL     0x69
#define MPU9250_REG_USER_CTRL           0x6A
#define MPU9250_REG_PWR_MGMT_1          0x6B
#define MPU9250_REG_PWR_MGMT_2          0x6C
#define MPU9250_REG_BANK_SEL            0x6D
#define MPU9250_REG_MEM_START_ADDR      0x6E
#define MPU9250_REG_MEM_R_W             0x6F
#define MPU9250_REG_DMP_CFG_1           0x70
#define MPU9250_REG_DMP_CFG_2           0x71
#define MPU9250_REG_FIFO_COUNTH         0x72
#define MPU9250_REG_FIFO_COUNTL         0x73
#define MPU9250_REG_FIFO_R_W            0x74
#define MPU9250_REG_WHOAMI              0x75
#define MPU9250_REG_XA_OFFSET_H         0x77
#define MPU9250_REG_XA_OFFSET_L         0x78
#define MPU9250_REG_YA_OFFSET_H         0x7A
#define MPU9250_REG_YA_OFFSET_L         0x7B
#define MPU9250_REG_ZA_OFFSET_H         0x7D
#define MPU9250_REG_ZA_OFFSET_L         0x7E

// Configuration bits mpu9250
// SIGNAL_PATH_RESET register
#define MPU9250_CFG_PATH_RST_ALL	   0x07
// PWR_MGMT_1 register
#define MPU9250_CFG_SLEEP                  0x40
#define MPU9250_CFG_H_RESET                0x80
#define MPU9250_CFG_CLKSEL_PLL		   0x03
// INT_PIN_CFG register
#define MPU9250_CFG_INT_ANYRD_2CLEAR       0x10
// INT_ENABLE register
#define MPU9250_CFG_RAW_RDY_EN             0x01
// CONFIG register
#define MPU9250_CFG_DLPF_CFG_250HZ_NOLPF   0x00  // LPF off, 8KHz updt rate, 250Hz bw, 0.97ms delay. (FCHOICE_B should be 0x00)
#define MPU9250_CFG_DLPF_CFG_3600HZ_NOLPF  0x07  // LPF off, 8KHz updt rate, 3600Hz bw, 0.17ms delay.
// GYRO_CONFIG register
#define MPU9250_CFG_GYO_FCHOICE_B_DIS      0x00  // enable LPF (unless DLPF_CFG_250HZ_NOLPF or DLPF_CFG_3600HZ_NOLPF are set)
#define MPU9250_CFG_GYO_FCHOICE_B_8800HZ   0x01  // LPF off, 32KHz updt rate, 8800Hz bw, 0.064ms delay
#define MPU9250_CFG_GYO_FCHOICE_B_3600HZ   0x02  // LPF off, 32KHz updt rate, 3600Hz bw, 0.11ms delay
#define MPU9250_CFG_FS_250DPS              0x00
#define MPU9250_CFG_FS_500DPS              0x08
#define MPU9250_CFG_FS_1000DPS             0x10
#define MPU9250_CFG_FS_2000DPS             0x18
// ACCEL_CONFIG register
#define MPU9250_CFG_FS_2G                  0x00
#define MPU9250_CFG_FS_4G                  0x08
#define MPU9250_CFG_FS_8G                  0x10
#define MPU9250_CFG_FS_16G                 0x18
// ACCEL_CONFIG_2 register
#define MPU9250_CFG_ACCEL_FCHOICE_B_DIS    0x00  // enable LPF
#define MPU9250_CFG_ACCEL_FCHOICE_B_EN     0x08  // LPF off, 4KHz updt rate, 1046Hz bw, 0.5ms delay
#define MPU9250_CFG_A_DLPF_CFG_420HZ_NOLPF 0x07  // LPF off, 1KHz updt rate, 420Hz bw, 1.38ms delay
// USER_CTRL register
#define MPU9250_CFG_SIG_COND_RST           0x01
#define MPU9250_CFG_I2C_MSTR_RST           0x02
#define MPU9250_CFG_I2C_IF_DIS             0x10
#define MPU9250_CFG_I2C_MSTR_EN            0x20
// I2C_MST_CTRL register
#define MPU9250_CFG_I2C_MST_CLK_400        0x0D
// I2C_SLV0_CTRL register
#define MPU9250_CFG_I2C_SLV0_EN            0x80
#define MPU9250_CFG_I2C_SLV0_BYTE_SWP      0x40


// AK8963 MAG

#define AK8963_DEVICE_ID            0x48
#define AK8963_I2C_ADDR             0x0c
#define AK8963_SCALE_GA		    (4912.0f / 32760.0f / 100.0f * CALIB_SCALE)  // scale to Gauss and AQ scale

// Read-only Reg
#define AK8963_WIA                  0x00
#define AK8963_INFO                 0x01
#define AK8963_ST1                  0x02
#define AK8963_HXL                  0x03
#define AK8963_HXH                  0x04
#define AK8963_HYL                  0x05
#define AK8963_HYH                  0x06
#define AK8963_HZL                  0x07
#define AK8963_HZH                  0x08
#define AK8963_ST2                  0x09
// Write/Read Reg
#define AK8963_CNTL1                0x0A
#define AK8963_CNTL2                0x0B
#define AK8963_ASTC                 0x0C
#define AK8963_TS1                  0x0D
#define AK8963_TS2                  0x0E
#define AK8963_I2CDIS               0x0F
// Read-only Reg ( ROM )
#define AK8963_ASAX                 0x10
#define AK8963_ASAY                 0x11
#define AK8963_ASAZ                 0x12

// AK8962 config bits
// CNTL1 register
#define AK8963_CFG_MODE_PWR_DOWN    0x00
#define AK8963_CFG_MODE_CONT_8HZ    0x02  // continuous sampling mode @ 8Hz
#define AK8963_CFG_MODE_CONT_100HZ  0x06  // continuous sampling mode @ 100Hz
#define AK8963_CFG_MODE_FUSE_ACC    0x0F
#define AK8963_CFG_BITCOUNT_8       0x00
#define AK8963_CFG_BITCOUNT_16      0x10
// CNTL2 register
#define AK8963_CFG_SRST             0x01

typedef struct {
    utilFilter_t tempFilter;
    spiClient_t *spi;
    volatile uint32_t spiFlag;
    volatile uint8_t rxBuf[MPU9250_SLOT_SIZE*MPU9250_SLOTS];
    volatile uint8_t slot;
    float rawTemp;
    float rawAcc[3];
    float rawGyo[3];
    float dRateRawGyo[3];
    float gyoOffset[3];
    volatile float acc[3];
    volatile float temp;
    volatile float gyo[3];
    volatile float dRateGyo[3];
    volatile uint32_t lastUpdate;
    float accSign[3];
    float gyoSign[3];
#if MPU9250_USE_AK8963
    float rawMag[3];
    float mag[3];
    float magSign[3];
    float magScale[3];
    uint8_t magInit;
    uint8_t magEnabled;
#endif
    uint8_t readReg;
    uint8_t initialized;
    uint8_t enabled;
} mpu9250Struct_t;

extern mpu9250Struct_t mpu9250Data;

extern void mpu9250PreInit(void);
extern uint8_t mpu9250Init(void);
extern void mpu9250InitialBias(void);
extern void mpu9250Decode(void);
extern void mpu9250DrateDecode(void);
extern void mpu9250Enable(void);
extern void mpu9250Disable(void);

#endif
