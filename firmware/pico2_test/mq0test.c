#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define ELRS_UART uart1
#define ELRS_TX_PIN 4
#define ELRS_RX_PIN 5
#define ELRS_BAUD 420000

int main() {
    stdio_init_all();

    uart_init(ELRS_UART, ELRS_BAUD);
    gpio_set_function(ELRS_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(ELRS_RX_PIN, GPIO_FUNC_UART);
    uart_set_format(ELRS_UART, 8, 1, UART_PARITY_NONE);

    uart_set_hw_flow(ELRS_UART, false, false);
    sleep_ms(2000);

    printf("ELRS raw receiver data\n");
    printf("UART1 | GP4 TX | GP5 RX | 420000 baud\n\n");

    while (true) {
        if (uart_is_readable(ELRS_UART)) {
            uint8_t data = uart_getc(ELRS_UART);
            printf("%02X \n", data);
        }
    }
}
