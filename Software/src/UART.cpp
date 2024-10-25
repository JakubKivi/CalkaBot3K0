#include "../include/UART.h"

#define F_CPU 16000000UL
#define BAUD_PRESCALE(baudRate) ((F_CPU / (16UL * baudRate)) - 1)

UART::UART(unsigned int baudRate) {
    init(BAUD_PRESCALE(baudRate));
}

void UART::init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void UART::transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void UART::print(const char* str) {
    while (*str) {
        transmit(*str++);
    }
}
