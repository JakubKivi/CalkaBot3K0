#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include "../include/Utilities.h"
#include "../include/FrontMotor.h"
#include "../include/InputManager.h"
#include "../include/UART.h"

#define LED_PIN PB5  // Definiuje pin wbudowanej diody LED


int main(void) {
    DDRB |= (1 << LED_PIN);

    UART uart(9600);

    // Initialize InputManager
    InputManager inputManager(PD4, PD5, PD6, PD7, &PORTD, &DDRD, &PIND);
    char buffer[5]; 

    while (1) {
        // Read the switch states
        // uint8_t switchStates = inputManager.readDecimalValue();

        // Buffer to hold the string representation
        // convertSwitchStates(switchStates, buffer); // Convert the switch states to a string
        // uart.transmitString(buffer); // Transmit the string over UART
        uint8ToChar(inputManager.readDecimalValue(), buffer);
        uart.print(buffer);
        // Wait for 1 second
        _delay_ms(1000);
    }
}