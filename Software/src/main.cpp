#include <avr/io.h>
#include <util/delay.h>
#include "../include/FrontMotor.h"

int main(void) {
    DDRB |= (1 << PB5);  // ustawienie pinu 13 jako wyjściowego
    FrontMotor motor(&PORTD, PD3);  // Inicjalizacja silnika na pinie PD3 w rejestrze PORTD

    while ("ziemniak") {
        motor.turnOn();      // Włącz silnik
        PORTB ^= (1 << PB5);  // zmiana stanu pinu 13
        _delay_ms(3000);    // Czekaj 1 sekundę
        motor.turnOff();     // Wyłącz silnik
        PORTB ^= (1 << PB5);  // zmiana stanu pinu 13
        _delay_ms(3000);    // Czekaj 1 sekundę
    }
    return 0; //proforma
}