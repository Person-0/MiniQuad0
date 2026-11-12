#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "../libs/mp92plus/inc/mp92plus.h"
#include "imu.h"

mpu9250_t IMU;

void elog(const char* txt) {
    while(true) {printf(txt);}
}

/*
 @return 0 -> success,
         2 -> mpu9250_reset failed,
         3 -> mpu9250_setup failed.
*/
int setup_imu() {
    spi_pin_t spi_pindefs = {
        .miso = IMU_MISO,
        .mosi = IMU_MOSI,
        .sck = IMU_SCK,
        .cs = IMU_CS,
    };

    uint8_t activate = mpu9250_reset(&IMU, &spi_pindefs, IMU_SPI, 1000 * 1000);

    if (activate > 0) {
        elog("Failed to initialize IMU! (mpu9250_reset failed)\n");
        return 2;
    }

    mpu_settings_t set = {
        .accel_range = ACCEL_RANGE_16G,
        .gyro_range = GYRO_RANGE_2000DPS,
        .dlpf_filter = DLPF_41HZ,
        .sample_rate_divider = 249
    };

    int16_t correct_gyro[] = {0, 0, 0};
    uint8_t settings = mpu9250_setup(&IMU, &set, correct_gyro);

    if (settings) {
        elog("Failed to initialize IMU! (mpu9250_setup failed)\n");
        return 3;
    }

    return 0;
}

/*
 @param imu_data output array in which the float values are stored:
                 `{accel[0], accel[1], accel[2], gyro[0] gyro[1] gyro[2]}`
*/
void read_imu(float imu_data[6]) {
    float accel[3] = {0.0f, 0.0f, 0.0f};
    float gyro[3] = {0.0f, 0.0f, 0.0f};

    mpu9250_read_motion(&IMU, accel, gyro);

    imu_data[0] = accel[0];
    imu_data[1] = accel[1];
    imu_data[2] = accel[2];
    imu_data[3] = gyro[0];
    imu_data[4] = gyro[1];
    imu_data[5] = gyro[2];
}

float read_imu_temp() {
    float temp = 0.0f;
    mpu9250_read_temperature(&IMU, &temp);
    //elog("Temperature in C      %10.4f\n\n", temp);
    return temp;
}

void disable_imu() {
    elog("Disabling IMU_SPI\n");
    spi_deinit(IMU_SPI);
}