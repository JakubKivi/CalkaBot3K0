#include "../include/Sensor.h"

// Konstruktor klasy Sensor
Sensor::Sensor(uint8_t pin) {
    this->pin = pin;
    
    ADMUX |= (1 << REFS0); // Ustawienie Vcc jako napięcia referencyjnego
    
    ADCSRA |= (1 << ADEN); // Włączenie ADC
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1); // Ustawienie preskalera ADC na 64
}

// Metoda odczytu analogowego
uint16_t Sensor::read() {
    // Rozpoczęcie konwersji ADC
    // Wybór kanału ADC (A0-A7)
    ADMUX = (ADMUX & 0xF0) | (pin & 0x0F);  // Maskowanie kanału w ADMUX

    // Rozpoczęcie konwersji ADC
    ADCSRA |= (1 << ADSC);

    // Czekamy, aż konwersja się zakończy
    while (ADCSRA & (1 << ADSC)) {
        // Czekaj, aż konwersja się zakończy
    }

    // Odczyt wyniku konwersji (ADC)
    return ADC;
}