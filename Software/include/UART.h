#ifndef UART_H
#define UART_H

#include <avr/io.h>

class UART {
public:
    UART(unsigned int baudRate);
    void transmit(unsigned char data);
    void print(const char* str);

private:
    void init(unsigned int ubrr);
};

#endif // UART_H