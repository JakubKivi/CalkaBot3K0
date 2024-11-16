#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <avr/io.h>

class InputManager {
public:
    InputManager(volatile uint8_t* portRegister, volatile uint8_t* ddr, volatile uint8_t* pinRegister, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);
    uint8_t readPin(uint8_t pin);
    uint8_t readDecimalValue();

private:
    uint8_t pins[4];
    volatile uint8_t* portRegister;
    volatile uint8_t* ddr;
    volatile uint8_t* pinRegister;
};

#endif // INPUT_MANAGER_H

