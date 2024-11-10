#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include "../include/Utilities.h"
#include "../include/FrontMotor.h"
#include "../include/InputManager.h"
#include "../include/UART.h"
#include "../include/BuildLED.h"



int main(void) {
    

    UART uart(9600);
    
    InputManager inputManager(PD4, PD5, PD6, PD7, &PORTD, &DDRD, &PIND);
    FrontMotor FrontMotor(&PORTD, PD3);
    BuildLed errorLED(&PORTC, PC5);  

    while (1)
    {
        errorLED.killError(inputManager.readDecimalValue());            
    }
    
}
