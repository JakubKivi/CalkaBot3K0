#include "../include/InputManager.h"

// Konstruktor klasy
InputManager::InputManager(volatile uint8_t* portRegister, volatile uint8_t* ddr, volatile uint8_t* pinRegister, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4)
    : portRegister(portRegister), pinRegister(pinRegister) {
    pins[0] = pin1;
    pins[1] = pin2;
    pins[2] = pin3;
    pins[3] = pin4;
    *ddr &= ~((1 << pin1) | (1 << pin2) | (1 << pin3) | (1 << pin4)); // Ustawienie jako wejścia (0)
    // Ustawienie pinów jako wejścia z pull-upem
    *portRegister |= (1 << pin1) | (1 << pin2) | (1 << pin3) | (1 << pin4);
}

// Metoda do odczytu stanu konkretnego pinu
uint8_t InputManager::readPin(uint8_t pin) {
    for (uint8_t i = 0; i < 4; ++i) {
        if (pins[i] == pin) {
            return !(*pinRegister & (1 << pin)); // Zwraca stan pinu (0 lub 1)
        }
    }
    return 255; // W przypadku nieznanego pinu
}

// Metoda do odczytu wartości dziesiętnej z pinów
uint8_t InputManager::readDecimalValue() {
    uint8_t value = 0;
    for (uint8_t i = 0; i < 4; ++i) {
        value |= (readPin(pins[3-i]) << i);
    }
    return value; // Zwraca wartość dziesiętną
}