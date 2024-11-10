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


    BuildLed errorLED(&PORTC, PC5);  
    // timer_init();  // Inicjalizacja timera



    while (1)
    {
        switch (inputManager.readDecimalValue())
        {
        case 0:
            errorLED.killError(10);
            break;
        case 1:
            errorLED.showError(1);
            break;
        case 2:
            errorLED.showError(2);
            break;
        case 3:
            errorLED.showError(3);
            break;
        case 4:
            errorLED.showError(4);
            break;
        case 5:
            errorLED.showError(5);
            break;
        case 6:
            errorLED.showError(6);
            break;
        case 7:
            errorLED.showError(7);
            break;
        default:
            break;
        }
    }
    
}
