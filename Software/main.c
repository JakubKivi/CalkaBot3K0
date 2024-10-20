#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB |= (1 << PB5);  // ustawienie pinu 13 jako wyjściowego

    while (1) {
        PORTB ^= (1 << PB5);  // zmiana stanu pinu 13
        _delay_ms(100);      // czekaj 1 sekundę
    }
}