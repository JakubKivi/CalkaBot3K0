#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <avr/io.h>

class InputManager {
private:
    volatile uint8_t* port;  // Wskaźnik na port
    uint8_t pinMask;  // Maska dla wybranych pinów
    void initPins();  // Inicjalizacja pinów jako wejścia z pull-up

public:
    // Konstruktor przyjmuje numery pinów jako argumenty
    InputManager(volatile uint8_t* port, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);  
    uint8_t read();  // Odczyt stanu przełączników
    uint8_t readPin(uint8_t switchNumber);  // Odczyt stanu pinu 1-4 (PD4-PD7)
};

#endif
