#pragma once

#define FC_TARGET_MCU     RP2350A
#define BOARD_NAME        mq0
#define MANUFACTURER_ID   p0

#define LED0_PIN          PA25

// Example GPIO pins for testing motor output
#define MOTOR1_PIN        PA10
#define MOTOR2_PIN        PA11
#define MOTOR3_PIN        PA12
#define MOTOR4_PIN        PA13

// receiver
#define UART1_TX_PIN      PA4
#define UART1_RX_PIN      PA5

// 26.6.2 wont compile without this :(
#define USE_SDCARD