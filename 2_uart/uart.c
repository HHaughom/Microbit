#include "uart.h"
#include "gpio.h"

void uart_init() {
    GPIO->PIN_CNF[24] = 1;
    GPIO->PIN_CNF[25] = 0;
    UART->PSELTXD = 1 << 24;
    UART->PSELRXD = 1 << 25;
    UART->BAUDRATE = 0x00275000;
    UART->PSELRTS = 0xFFFFFFFF;
    UART->PSELCTS = 0xFFFFFFFF;
    UART->ENABLE = 4;
    UART->STARTRX = 1;
}



void uart_send(char letter) {
    UART->STARTTX = 1;
    if(!UART->TXDRDY) {
        UART->TXD = letter;
    }
    UART->TXDRDY = 0;
}




char uart_read() {
    if(UART->RXDRDY) {
        UART->RXDRDY = 0;
        return UART->RXD;
    }
    else {
        return '\0';
    }
}