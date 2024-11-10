#include "../include/FrontMotor.h"

// Konstruktor klasy
FrontMotor::FrontMotor(volatile uint8_t* port, uint8_t pin) : port(port), pin(pin) {
    setPinAsOutput(); // Ustawienie pinu jako wyjściowy
}

// Ustawienie pinu jako wyjściowy
void FrontMotor::setPinAsOutput() {
    *port |= (1 << pin); // Ustawienie pinu jako wyjściowy
}

// Włączenie silnika
void FrontMotor::on() {
    *port |= (1 << pin); // Ustawienie pinu na wysoki stan
}

// Wyłączenie silnika
void FrontMotor::off() {
    *port &= ~(1 << pin); // Ustawienie pinu na niski stan
}

// Przełączenie stanu silnika
void FrontMotor::toggle() {
    *port ^= (1 << pin); // Zmiana stanu pinu
}

// Odczyt stanu silnika
uint8_t FrontMotor::getState() const {
    return (*port & (1 << pin)) ? 1 : 0; // Zwraca 1 jeśli pin wysoki, 0 jeśli niski
}