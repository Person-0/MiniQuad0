#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#include "src/imu.h"

#define ELRS_UART uart1
#define ELRS_TX_PIN 4
#define ELRS_RX_PIN 5
#define ELRS_BAUD 420000

uint8_t dataarr[64];
uint8_t dataarrp = 0;
uint8_t dlen = 0;
bool receiving = false;
void elrsSetup() {
    uart_init(ELRS_UART, ELRS_BAUD);
    gpio_set_function(ELRS_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(ELRS_RX_PIN, GPIO_FUNC_UART);
    uart_set_format(ELRS_UART, 8, 1, UART_PARITY_NONE);
    uart_set_hw_flow(ELRS_UART, false, false);
    sleep_ms(2000);
    printf("elrs setup\n");
}
void elrsStuff() {
    if (uart_is_readable(ELRS_UART)) {
        uint8_t data = uart_getc(ELRS_UART);

        if (!receiving) {
            if (data == 0xC8) {
                receiving = true;
                dataarrp = 0;
            }
            return;
        }

        if (dataarrp == 0) {
            dlen = data;
            if (dlen < 2 || dlen > 62) {
                receiving = false;
                return;
            }
            dataarr[dataarrp++] = data;
            return;
        }

        dataarr[dataarrp++] = data;

        if (dataarrp >= dlen + 1) {
            receiving = false;
            if (dataarr[1] == 0x16) {
                printf("RC frame detected!\n");
                for (uint8_t i = 0; i < dataarrp; i++) {
                    printf("%02X ", dataarr[i]);
                }
                printf("\n");
            }
        }

    }
}

int main() {
    stdio_init_all();

    //elrsSetup();

    if(setup_imu() > 0) {
        printf("imu setup err!\n");
        return 0;
    }
    
    while (true) {
        //elrsStuff();
        float imu_data[6];
        read_imu(imu_data);
        printf("imu read: ");
        for(int i = 0 ; i < 6; i++) {
            printf("%.3f ", imu_data[i]);
        }
        printf("\n");
    }

    return 0;
}
