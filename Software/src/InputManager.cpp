#include "InputManager.h"

InputManager::InputManager(volatile uint8_t* port, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4) 
    : port(port) {
    // Tworzenie maski na podstawie podanych pinów
    pinMask = (1 << pin1) | (1 << pin2) | (1 << pin3) | (1 << pin4);
    initPins();
}

void InputManager::initPins() {
    // Ustawienie wybranych pinów jako wejścia z włączonym rezystorem pull-up
    *port &= ~pinMask;  // Ustawienie jako wejścia (0)
    *(port + 1) |= pinMask;  // Włączenie pull-up (w rejestrze PORTx)
}

uint8_t InputManager::read() {
    // Odczyt stanu przełączników
    return (~(*port) & pinMask) >> 4;
}


uint8_t InputManager::readPin(uint8_t switchNumber) {
    // Zwraca stan konkretnego pinu w zależności od switchNumber (1-4)
    uint8_t pinOffset = switchNumber + 3;  // Dla PD4 = 1, PD5 = 2, itd.
    return (~(*port) & (1 << pinOffset)) ? 1 : 0;
}
