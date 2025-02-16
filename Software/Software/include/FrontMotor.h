#ifndef FRONT_MOTOR_H
#define FRONT_MOTOR_H

#include <avr/io.h>

class FrontMotor {
private:
    volatile uint8_t* port; // Wskaźnik do rejestru PORT
    volatile uint8_t* ddr;  // Wskaźnik do rejestru i/o
    uint8_t pin;            // Numer pinu (0-7)

public:
    // Konstruktor klasy
    FrontMotor(volatile uint8_t* port, volatile uint8_t* ddr, uint8_t pin);

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