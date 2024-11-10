#ifndef FRONT_MOTOR_H
#define FRONT_MOTOR_H

#include <avr/io.h>

class FrontMotor {
private:
    volatile uint8_t* port; // Wskaźnik do rejestru PORT
    uint8_t pin;            // Numer pinu (0-7)

    // Zwraca stan rejestru DDR (ustawienie pinu jako wyjściowy)
    void setPinAsOutput();

public:
    // Konstruktor klasy
    FrontMotor(volatile uint8_t* port, uint8_t pin);

    // Włączenie silnika
    void on();

    // Wyłączenie silnika
    void off();

    // Przełączenie stanu silnika
    void toggle();

    // Odczyt stanu silnika
    uint8_t getState() const;
};

#endif // FRONT_MOTOR_H