#ifndef SENSOR_H
#define SENSOR_H

#include <avr/io.h>

class Sensor {
private:
    uint8_t pin;                // Numer pinu (A0, A1, ...)
    
public:
    // Konstruktor
    Sensor(uint8_t pin);

    // Metoda do odczytu wartości analogowej
    uint16_t read();
};

#endif