#pragma once

#define FC_TARGET_MCU               RP2350A
#define BOARD_NAME                  MQ0
#define MANUFACTURER_ID             P0

// led
#define LED0_PIN                    PA25

// receiver
#define UART1_TX_PIN                PA4
#define UART1_RX_PIN                PA5

// mpu6500 imu
#define USE_ACC
#define USE_GYRO
#define USE_ACC_SPI_MPU6500
#define USE_GYRO_SPI_MPU6500
#define GYRO_1_SPI_INSTANCE         SPI0
#define GYRO_1_CS_PIN               PA1
#define SPI0_SCK_PIN                PA2
#define SPI0_SDI_PIN                PA0
#define SPI0_SDO_PIN                PA3
#define GYRO_1_ALIGN                CW0_DEG


// Example GPIO pins for testing motor output
#define MOTOR1_PIN                  PA10
#define MOTOR2_PIN                  PA11
#define MOTOR3_PIN                  PA12
#define MOTOR4_PIN                  PA13

// does not compile without this !?
#define USE_SDCARD