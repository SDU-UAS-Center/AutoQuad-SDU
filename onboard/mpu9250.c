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

#include "config.h"

#if defined(HAS_DIGITAL_IMU) && defined(DIMU_HAVE_MPU9250)

#include "mpu9250.h"

#include "aq_timer.h"
#include "config.h"
//#include "comm.h"
#include "ext_irq.h"
#include "imu.h"

#include <string.h>
#ifndef __CC_ARM
#include <intrinsics.h>
#endif

mpu9250Struct_t mpu9250Data;

static void mpu9250TransferComplete(int unused) {
    mpu9250Data.slot = (mpu9250Data.slot + 1) % MPU9250_SLOTS;
}

void mpu9250InitialBias(void) {
    uint32_t lastUpdate = mpu9250Data.lastUpdate;
    float tempSum;
    int i;

    tempSum = 0.0f;

    for (i = 0; i < 50; i++) {
	while (lastUpdate == mpu9250Data.lastUpdate)
	    delay(1);
	lastUpdate = mpu9250Data.lastUpdate;

	tempSum += mpu9250Data.rawTemp;
    }

    mpu9250Data.temp = tempSum / 50.0f;
    utilFilterReset(&mpu9250Data.tempFilter, mpu9250Data.temp);
}


static void mpu9250ScaleAcc(int32_t *in, float *out, float divisor) {
    float scale;

    scale = 1.0f / ((1<<16) / (MPU9250_ACC_SCALE * 2.0f)) * GRAVITY * divisor;

    out[0] = mpu9250Data.accSign[0] * DIMU_ORIENT_ACC_X * scale;
    out[1] = mpu9250Data.accSign[1] * DIMU_ORIENT_ACC_Y * scale;
    out[2] = mpu9250Data.accSign[2] * DIMU_ORIENT_ACC_Z * scale;
}

static void mpu9250CalibAcc(float *in, volatile float *out) {
    float a, b, c;
    float x, y, z;

    // bias
    a = -(in[0] + p[IMU_ACC_BIAS_X] + p[IMU_ACC_BIAS1_X]*dImuData.dTemp + p[IMU_ACC_BIAS2_X]*dImuData.dTemp2 + p[IMU_ACC_BIAS3_X]*dImuData.dTemp3);
    b = +(in[1] + p[IMU_ACC_BIAS_Y] + p[IMU_ACC_BIAS1_Y]*dImuData.dTemp + p[IMU_ACC_BIAS2_Y]*dImuData.dTemp2 + p[IMU_ACC_BIAS3_X]*dImuData.dTemp3);
    c = -(in[2] + p[IMU_ACC_BIAS_Z] + p[IMU_ACC_BIAS1_Z]*dImuData.dTemp + p[IMU_ACC_BIAS2_Z]*dImuData.dTemp2 + p[IMU_ACC_BIAS3_X]*dImuData.dTemp3);

    // misalignment
    x = a + b*p[IMU_ACC_ALGN_XY] + c*p[IMU_ACC_ALGN_XZ];
    y = a*p[IMU_ACC_ALGN_YX] + b + c*p[IMU_ACC_ALGN_YZ];
    z = a*p[IMU_ACC_ALGN_ZX] + b*p[IMU_ACC_ALGN_ZY] + c;

    // scale
    x /= (p[IMU_ACC_SCAL_X] + p[IMU_ACC_SCAL1_X]*dImuData.dTemp + p[IMU_ACC_SCAL2_X]*dImuData.dTemp2 + p[IMU_ACC_SCAL3_X]*dImuData.dTemp3);
    y /= (p[IMU_ACC_SCAL_Y] + p[IMU_ACC_SCAL1_Y]*dImuData.dTemp + p[IMU_ACC_SCAL2_Y]*dImuData.dTemp2 + p[IMU_ACC_SCAL3_Y]*dImuData.dTemp3);
    z /= (p[IMU_ACC_SCAL_Z] + p[IMU_ACC_SCAL1_Z]*dImuData.dTemp + p[IMU_ACC_SCAL2_Z]*dImuData.dTemp2 + p[IMU_ACC_SCAL3_Z]*dImuData.dTemp3);

    // IMU rotation
    out[0] = x * imuData.cosRot - y * imuData.sinRot;
    out[1] = y * imuData.cosRot + x * imuData.sinRot;
    out[2] = z;
}

static void mpu9250ScaleGyo(int32_t *in, float *out, float divisor) {
    float scale;

    scale = 1.0f / ((1<<16) / (MPU9250_GYO_SCALE * 2.0f)) * DEG_TO_RAD * divisor;

    out[0] = mpu9250Data.gyoSign[0] * DIMU_ORIENT_GYO_X * scale;
    out[1] = mpu9250Data.gyoSign[1] * DIMU_ORIENT_GYO_Y * scale;
    out[2] = mpu9250Data.gyoSign[2] * DIMU_ORIENT_GYO_Z * scale;
}

static void mpu9250CalibGyo(float *in, volatile float *out) {
    float a, b, c;
    float x, y, z;

    // bias
    a = +(in[0] + mpu9250Data.gyoOffset[0] + p[IMU_GYO_BIAS_X] + p[IMU_GYO_BIAS1_X]*dImuData.dTemp + p[IMU_GYO_BIAS2_X]*dImuData.dTemp2 + p[IMU_GYO_BIAS3_X]*dImuData.dTemp3);
    b = -(in[1] + mpu9250Data.gyoOffset[1] + p[IMU_GYO_BIAS_Y] + p[IMU_GYO_BIAS1_Y]*dImuData.dTemp + p[IMU_GYO_BIAS2_Y]*dImuData.dTemp2 + p[IMU_GYO_BIAS3_Y]*dImuData.dTemp3);
    c = -(in[2] + mpu9250Data.gyoOffset[2] + p[IMU_GYO_BIAS_Z] + p[IMU_GYO_BIAS1_Z]*dImuData.dTemp + p[IMU_GYO_BIAS2_Z]*dImuData.dTemp2 + p[IMU_GYO_BIAS3_Z]*dImuData.dTemp3);

    // misalignment
    x = a + b*p[IMU_GYO_ALGN_XY] + c*p[IMU_GYO_ALGN_XZ];
    y = a*p[IMU_GYO_ALGN_YX] + b + c*p[IMU_GYO_ALGN_YZ];
    z = a*p[IMU_GYO_ALGN_ZX] + b*p[IMU_GYO_ALGN_ZY] + c;

    // scale
    x /= p[IMU_GYO_SCAL_X];
    y /= p[IMU_GYO_SCAL_Y];
    z /= p[IMU_GYO_SCAL_Z];

    // IMU rotation
    out[0] = x * imuData.cosRot - y * imuData.sinRot;
    out[1] = y * imuData.cosRot + x * imuData.sinRot;
    out[2] = z;
}

#if MPU9250_USE_AK8963
static void mpu9250ScaleMag(int32_t *in, float *out, float divisor) {
    //float scale;
    //scale = divisor * (1.0f / 187.88f);

    out[0] = mpu9250Data.magSign[0] * DIMU_ORIENT_MAG_X * mpu9250Data.magScale[0] * divisor;
    out[1] = mpu9250Data.magSign[1] * DIMU_ORIENT_MAG_Y * mpu9250Data.magScale[1] * divisor;
    out[2] = mpu9250Data.magSign[2] * DIMU_ORIENT_MAG_Z * mpu9250Data.magScale[2] * divisor;
}

static void mpu9250CalibMag(float *in, volatile float *out) {
    float a, b, c;
    float x, y, z;

    // bias
    a = +(in[0] + p[IMU_MAG_BIAS_X] + p[IMU_MAG_BIAS1_X]*dImuData.dTemp + p[IMU_MAG_BIAS2_X]*dImuData.dTemp2 + p[IMU_MAG_BIAS3_X]*dImuData.dTemp3);
    b = +(in[1] + p[IMU_MAG_BIAS_Y] + p[IMU_MAG_BIAS1_Y]*dImuData.dTemp + p[IMU_MAG_BIAS2_Y]*dImuData.dTemp2 + p[IMU_MAG_BIAS3_Y]*dImuData.dTemp3);
    c = -(in[2] + p[IMU_MAG_BIAS_Z] + p[IMU_MAG_BIAS1_Z]*dImuData.dTemp + p[IMU_MAG_BIAS2_Z]*dImuData.dTemp2 + p[IMU_MAG_BIAS3_Z]*dImuData.dTemp3);

    // misalignment
    x = a + b*p[IMU_MAG_ALGN_XY] + c*p[IMU_MAG_ALGN_XZ];
    y = a*p[IMU_MAG_ALGN_YX] + b + c*p[IMU_MAG_ALGN_YZ];
    z = a*p[IMU_MAG_ALGN_ZX] + b*p[IMU_MAG_ALGN_ZY] + c;

    // scale
    x /= (p[IMU_MAG_SCAL_X] + p[IMU_MAG_SCAL1_X]*dImuData.dTemp + p[IMU_MAG_SCAL2_X]*dImuData.dTemp2 + p[IMU_MAG_SCAL3_X]*dImuData.dTemp3);
    y /= (p[IMU_MAG_SCAL_Y] + p[IMU_MAG_SCAL1_Y]*dImuData.dTemp + p[IMU_MAG_SCAL2_Y]*dImuData.dTemp2 + p[IMU_MAG_SCAL3_Y]*dImuData.dTemp3);
    z /= (p[IMU_MAG_SCAL_Z] + p[IMU_MAG_SCAL1_Z]*dImuData.dTemp + p[IMU_MAG_SCAL2_Z]*dImuData.dTemp2 + p[IMU_MAG_SCAL3_Z]*dImuData.dTemp3);

    out[0] = x * imuData.cosRot - y * imuData.sinRot;
    out[1] = y * imuData.cosRot + x * imuData.sinRot;
    out[2] = z;
}
#endif  // MPU9250_USE_AK8963

void mpu9250DrateDecode(void) {
    volatile uint8_t *d = mpu9250Data.rxBuf;
    int32_t gyo[3];
    float divisor;
    int s, i;

    if (mpu9250Data.enabled) {
        for (i = 0; i < 3; i++)
            gyo[i] = 0;

        divisor = (float)MPU9250_DRATE_SLOTS;
        s = mpu9250Data.slot - 1;
        if (s < 0)
            s = MPU9250_SLOTS - 1;

        for (i = 0; i < MPU9250_DRATE_SLOTS; i++) {
            int j = s*MPU9250_SLOT_SIZE;

            // check if we are in the middle of a transaction for this slot
            if (s == mpu9250Data.slot && mpu9250Data.spiFlag == 0)	{
                divisor -= 1.0f;
            }
            else {
                gyo[0] += (int16_t)__rev16(*(uint16_t *)&d[j+9]);
                gyo[1] += (int16_t)__rev16(*(uint16_t *)&d[j+11]);
                gyo[2] += (int16_t)__rev16(*(uint16_t *)&d[j+13]);
            }

            if (--s < 0)
                s = MPU9250_SLOTS - 1;
        }

        divisor = 1.0f / divisor;

        mpu9250ScaleGyo(gyo, mpu9250Data.dRateRawGyo, divisor);
        mpu9250CalibGyo(mpu9250Data.dRateRawGyo, mpu9250Data.dRateGyo);
    }
}

void mpu9250Decode(void) {
    if (!mpu9250Data.enabled)
	return;

    volatile uint8_t *d = mpu9250Data.rxBuf;
    int32_t acc[3] = {0, 0, 0};
    int32_t gyo[3] = {0, 0, 0};
    int32_t temp = 0;
    float divisor, magDivsr;
    int i;
#if MPU9250_USE_AK8963
    int32_t mag[3] = {0, 0, 0};
    uint8_t magStat;
#endif

    divisor = magDivsr = (float)MPU9250_SLOTS;
    for (i = 0; i < MPU9250_SLOTS; i++) {
	int j = i * MPU9250_SLOT_SIZE;

	// check if we are in the middle of a transaction for this slot
	if (i == mpu9250Data.slot && mpu9250Data.spiFlag == 0)	{
	    divisor -= 1.0f;
	    magDivsr -= 1.0f;
	}
	else {
	    acc[0] += (int16_t)__rev16(*(uint16_t *)&d[j+1]);
	    acc[1] += (int16_t)__rev16(*(uint16_t *)&d[j+3]);
	    acc[2] += (int16_t)__rev16(*(uint16_t *)&d[j+5]);

	    temp += (int16_t)__rev16(*(uint16_t *)&d[j+7]);

	    gyo[0] += (int16_t)__rev16(*(uint16_t *)&d[j+9]);
	    gyo[1] += (int16_t)__rev16(*(uint16_t *)&d[j+11]);
	    gyo[2] += (int16_t)__rev16(*(uint16_t *)&d[j+13]);

#if MPU9250_USE_AK8963
	    if (mpu9250Data.magEnabled) {
		magStat = d[j+21];
		// check overflow bit
		if (!(magStat & 0x08)) {
		    // swap x & y axes
		    mag[1] += *(int16_t *)&d[j+15];
		    mag[0] += *(int16_t *)&d[j+17];
		    mag[2] += *(int16_t *)&d[j+19];
		} else
		    magDivsr -= 1.0f;
	    }
#endif
	}
    }

    divisor = 1.0f / divisor;

    mpu9250Data.rawTemp = temp * divisor * (1.0f / 333.87f) + 21.0f;
    mpu9250Data.temp = utilFilter(&mpu9250Data.tempFilter, mpu9250Data.rawTemp);

    mpu9250ScaleAcc(acc, mpu9250Data.rawAcc, divisor);
    mpu9250CalibAcc(mpu9250Data.rawAcc, mpu9250Data.acc);

    mpu9250ScaleGyo(gyo, mpu9250Data.rawGyo, divisor);
    mpu9250CalibGyo(mpu9250Data.rawGyo, mpu9250Data.gyo);

#if MPU9250_USE_AK8963
    if (mpu9250Data.magEnabled) {
	magDivsr = 1.0f / magDivsr;
	mpu9250ScaleMag(mag, mpu9250Data.rawMag, magDivsr);
	mpu9250CalibMag(mpu9250Data.rawMag, mpu9250Data.mag);
    }
#endif

    mpu9250Data.lastUpdate = timerMicros();
}

static uint32_t mpu9250RxBuf;
static uint32_t mpu9250TxBuf;

static uint8_t mpu9250GetReg(uint8_t reg) {
    ((uint8_t *)&mpu9250TxBuf)[0] = MPU9250_READ_BIT | reg;

    mpu9250Data.spiFlag = 0;
    spiTransaction(mpu9250Data.spi, &mpu9250RxBuf, &mpu9250TxBuf, 2);

    while (!mpu9250Data.spiFlag)
        ;

    return ((uint8_t *)&mpu9250RxBuf)[1];
}

static void mpu9250SetReg(uint8_t reg, uint8_t val) {
    ((uint8_t *)&mpu9250TxBuf)[0] = MPU9250_WRITE_BIT | reg;
    ((uint8_t *)&mpu9250TxBuf)[1] = val;

    mpu9250Data.spiFlag = 0;
    spiTransaction(mpu9250Data.spi, &mpu9250RxBuf, &mpu9250TxBuf, 2);

    while (!mpu9250Data.spiFlag)
        ;
}

static void mpu9250ReliablySetReg(uint8_t reg, uint8_t val) {
    do {
        delay(10);
        mpu9250SetReg(reg, val);
        delay(10);
    } while (mpu9250GetReg(reg) != val);
}

#if MPU9250_USE_AK8963
static void mpu9250SetMagReg(uint8_t reg, uint8_t val) {
    // I2C address of MAG slave sensor
    mpu9250ReliablySetReg(MPU9250_REG_I2C_SLV0_ADDR, AK8963_I2C_ADDR);
    // register to set
    mpu9250ReliablySetReg(MPU9250_REG_I2C_SLV0_REG, reg);
    // value of register
    mpu9250ReliablySetReg(MPU9250_REG_I2C_SLV0_DO, val);
    // I2C enable slave 0 and set one byte
    mpu9250ReliablySetReg(MPU9250_REG_I2C_SLV0_CTRL, MPU9250_CFG_I2C_SLV0_EN | 0x01);
}

static uint8_t mpu9250GetMagReg(uint8_t reg) {
    // I2C address of MAG slave sensor
    mpu9250ReliablySetReg(MPU9250_REG_I2C_SLV0_ADDR, AK8963_I2C_ADDR | MPU9250_READ_BIT);
    // register to read
    mpu9250ReliablySetReg(MPU9250_REG_I2C_SLV0_REG, reg);
    // I2C enable slave 0 and set one byte
    mpu9250ReliablySetReg(MPU9250_REG_I2C_SLV0_CTRL, MPU9250_CFG_I2C_SLV0_EN | 0x01);

    delayMicros(100);
    return mpu9250GetReg(MPU9250_REG_EXT_SENS_DATA_00);
}
#endif  // MPU9250_USE_AK8963

static void mpu9250IntHandler(void) {
    if (mpu9250Data.enabled)
	spiTransaction(mpu9250Data.spi, &mpu9250Data.rxBuf[mpu9250Data.slot*MPU9250_SLOT_SIZE], &mpu9250Data.readReg, MPU9250_BYTES);
}

inline void mpu9250Enable(void) {
    if (mpu9250Data.initialized) {
	mpu9250Data.enabled = 1;
#if MPU9250_USE_AK8963
	if (mpu9250Data.magInit)
	    mpu9250Data.magEnabled = 1;
#endif
    }
}

inline void mpu9250Disable(void) {
    mpu9250Data.enabled = 0;
#if MPU9250_USE_AK8963
    mpu9250Data.magEnabled = 0;
#endif
}

void mpu9250PreInit(void) {
    memset((void *)&mpu9250Data, 0, sizeof(mpu9250Data));
    mpu9250Data.spi = spiClientInit(DIMU_MPU9250_SPI, MPU9250_SPI_REG_BAUD, 0, DIMU_MPU9250_CS_PORT, DIMU_MPU9250_CS_PIN, &mpu9250Data.spiFlag, 0);
}

uint8_t mpu9250Init(void) {
    uint8_t retry;

    switch ((int)p[IMU_FLIP]) {
        case 1:
            mpu9250Data.accSign[0] =  1.0f;
            mpu9250Data.accSign[1] = -1.0f;
            mpu9250Data.accSign[2] = -1.0f;
            mpu9250Data.gyoSign[0] =  1.0f;
            mpu9250Data.gyoSign[1] = -1.0f;
            mpu9250Data.gyoSign[2] = -1.0f;
#if MPU9250_USE_AK8963
            mpu9250Data.magSign[0] =  1.0f;
            mpu9250Data.magSign[1] = -1.0f;
            mpu9250Data.magSign[2] = -1.0f;
#endif
            break;

        case 2:
            mpu9250Data.accSign[0] = -1.0f;
            mpu9250Data.accSign[1] =  1.0f;
            mpu9250Data.accSign[2] = -1.0f;
            mpu9250Data.gyoSign[0] = -1.0f;
            mpu9250Data.gyoSign[1] =  1.0f;
            mpu9250Data.gyoSign[2] = -1.0f;
#if MPU9250_USE_AK8963
            mpu9250Data.magSign[0] = -1.0f;
            mpu9250Data.magSign[1] =  1.0f;
            mpu9250Data.magSign[2] = -1.0f;
#endif
            break;

        case 0:
        default:
            mpu9250Data.accSign[0] = 1.0f;
            mpu9250Data.accSign[1] = 1.0f;
            mpu9250Data.accSign[2] = 1.0f;
            mpu9250Data.gyoSign[0] = 1.0f;
            mpu9250Data.gyoSign[1] = 1.0f;
            mpu9250Data.gyoSign[2] = 1.0f;
#if MPU9250_USE_AK8963
            mpu9250Data.magSign[0] = 1.0f;
            mpu9250Data.magSign[1] = 1.0f;
            mpu9250Data.magSign[2] = 1.0f;
#endif
            break;
    }

    utilFilterInit(&mpu9250Data.tempFilter, DIMU_OUTER_DT, DIMU_TEMP_TAU, IMU_ROOM_TEMP);

#if MPU9250_USE_AK8963
    // in case of a soft reset, this prevents occasional hangup of MAG init
    if (mpu9250GetReg(MPU9250_REG_USER_CTRL) & MPU9250_CFG_I2C_MSTR_EN) {
	// Power down MAG & wait
	mpu9250SetMagReg(AK8963_CNTL1, AK8963_CFG_MODE_PWR_DOWN);
	delay(100);
    }
#endif

    // reset MPU
    mpu9250SetReg(MPU9250_REG_PWR_MGMT_1, MPU9250_CFG_H_RESET);
    delay(50);

    // reset sensor signal paths
    mpu9250SetReg(MPU9250_REG_SIGNAL_PATH_RESET, MPU9250_CFG_PATH_RST_ALL);
    delay(1);

    // wake up w/PLL clock
    mpu9250ReliablySetReg(MPU9250_REG_PWR_MGMT_1, MPU9250_CFG_CLKSEL_PLL);

    // wait for a valid response
    retry = 200;  // ~2s
    while (--retry && mpu9250GetReg(MPU9250_REG_WHOAMI) != MPU9250_DEVICE_ID)
	delay(10);

    if (!retry)
	return 0;

    // GYO scale
#if MPU9250_GYO_SCALE == 250
    mpu9250ReliablySetReg(MPU9250_REG_GYRO_CONFIG, MPU9250_CFG_FS_250DPS);
#endif
#if MPU9250_GYO_SCALE == 500
    mpu9250ReliablySetReg(MPU9250_REG_GYRO_CONFIG, MPU9250_CFG_FS_500DPS);
#endif
#if MPU9250_GYO_SCALE == 1000
    mpu9250ReliablySetReg(MPU9250_REG_GYRO_CONFIG, MPU9250_CFG_FS_1000DPS);
#endif
#if MPU9250_GYO_SCALE == 2000
    mpu9250ReliablySetReg(MPU9250_REG_GYRO_CONFIG, MPU9250_CFG_FS_2000DPS);
#endif

    // ACC scale
#if MPU9250_ACC_SCALE == 2
    mpu9250ReliablySetReg(MPU9250_REG_ACCEL_CONFIG, MPU9250_CFG_FS_2G);
#endif
#if MPU9250_ACC_SCALE == 4
    mpu9250ReliablySetReg(MPU9250_REG_ACCEL_CONFIG, MPU9250_CFG_FS_4G);
#endif
#if MPU9250_ACC_SCALE == 8
    mpu9250ReliablySetReg(MPU9250_REG_ACCEL_CONFIG, MPU9250_CFG_FS_8G);
#endif
#if MPU9250_ACC_SCALE == 16
    mpu9250ReliablySetReg(MPU9250_REG_ACCEL_CONFIG, MPU9250_CFG_FS_16G);
#endif

    // Sample rate divider (full rate)
    mpu9250ReliablySetReg(MPU9250_REG_SMPLRT_DIV, 0x00);

    // GYO LPF off, 8KHz output rate, 250Hz bw
    mpu9250ReliablySetReg(MPU9250_REG_CONFIG, MPU9250_CFG_DLPF_CFG_250HZ_NOLPF);

    // ACC LPF off, 4KHz output rate, 1046Hz bw
    mpu9250ReliablySetReg(MPU9250_REG_ACCEL_CONFIG_2, MPU9250_CFG_ACCEL_FCHOICE_B_EN);

#if MPU9250_USE_AK8963

    // internal I2C Master mode, disable external I2C interface
    mpu9250ReliablySetReg(MPU9250_REG_USER_CTRL, MPU9250_CFG_I2C_IF_DIS | MPU9250_CFG_I2C_MSTR_EN);
    // I2C master configuration, 400Hz clock rate
    mpu9250ReliablySetReg(MPU9250_REG_I2C_MST_CTRL, MPU9250_CFG_I2C_MST_CLK_400);

    // reset MAG
    mpu9250SetMagReg(AK8963_CNTL2, AK8963_CFG_SRST);
    delay(50);

    // wait for a valid response
    retry = 100;  // ~1s
    while (--retry && mpu9250GetMagReg(AK8963_WIA) != AK8963_DEVICE_ID)
	delay(10);

    if (retry) {

	// fuse read mode
	mpu9250SetMagReg(AK8963_CNTL1, AK8963_CFG_MODE_FUSE_ACC);
	delay(1);
	// extract the factory calibration for each axis and set scaling factor
	mpu9250Data.magScale[0] = ((float)(mpu9250GetMagReg(AK8963_ASAX) - 128) / 256.0f + 1.0f) * AK8963_SCALE_GA;
	mpu9250Data.magScale[1] = ((float)(mpu9250GetMagReg(AK8963_ASAY) - 128) / 256.0f + 1.0f) * AK8963_SCALE_GA;
	mpu9250Data.magScale[2] = ((float)(mpu9250GetMagReg(AK8963_ASAZ) - 128) / 256.0f + 1.0f) * AK8963_SCALE_GA;
	//AQ_PRINTF("MAG: %f; %f; %f", mpu9250Data.magScale[0], mpu9250Data.magScale[1], mpu9250Data.magScale[2])

	// Power down & wait (as per datasheet recommendation)
	mpu9250SetMagReg(AK8963_CNTL1, AK8963_CFG_MODE_PWR_DOWN);
	delay(10);

	// config MAG CNTL1 register for sampling rate and resolution
	mpu9250SetMagReg(AK8963_CNTL1, AK8963_CFG_MODE_CONT_100HZ | AK8963_CFG_BITCOUNT_16);  // 100Hz @ 16bits

	// start reading MAG value bytes and status register into MPU storage
	mpu9250ReliablySetReg(MPU9250_REG_I2C_SLV0_ADDR, AK8963_I2C_ADDR | MPU9250_READ_BIT);
	mpu9250ReliablySetReg(MPU9250_REG_I2C_SLV0_REG, AK8963_HXL);
	mpu9250ReliablySetReg(MPU9250_REG_I2C_SLV0_CTRL, MPU9250_CFG_I2C_SLV0_EN | 0x07);

	mpu9250Data.magInit = 1;
    }

#else  // do not use on-board AK8963 mag

    // disable I2C interface
    mpu9250ReliablySetReg(MPU9250_REG_USER_CTRL, MPU9250_CFG_I2C_IF_DIS);

#endif  // MPU9250_USE_AK8963

    // Interrupt setup
    mpu9250ReliablySetReg(MPU9250_REG_INT_PIN_CFG, MPU9250_CFG_INT_ANYRD_2CLEAR);
    mpu9250ReliablySetReg(MPU9250_REG_INT_ENABLE, MPU9250_CFG_RAW_RDY_EN);

    // increase SPI clock rate
    spiChangeBaud(mpu9250Data.spi, MPU9250_SPI_RUN_BAUD);

    mpu9250Data.readReg = MPU9250_READ_BIT | MPU9250_REG_ACCEL_XOUT_H;	// start of sensor registers

    spiChangeCallback(mpu9250Data.spi, mpu9250TransferComplete);

    // External Interrupt line for data ready
    extRegisterCallback(DIMU_MPU9250_INT_PORT, DIMU_MPU9250_INT_PIN, EXTI_Trigger_Rising, 1, GPIO_PuPd_NOPULL, mpu9250IntHandler);

    mpu9250Data.initialized = 1;

    return mpu9250Data.initialized;
}

#endif  // defined(HAS_DIGITAL_IMU) && defined(DIMU_HAVE_MPU9250)
