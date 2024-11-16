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
#include "../include/Sensor.h"



int main(void) {
    

    UART uart(9600);
    
    InputManager inputManager(&PORTD, &DDRD, &PIND, PD4, PD5, PD6, PD7);
    FrontMotor FrontMotor(&PORTD, &DDRD, PD3);
    BuildLed errorLED(&PORTC, &DDRC, PC5); 
    Sensor floorLeft(0);
    Sensor floorRight(1);
    Sensor front(3);
      
    char buffer[10]; 

    while (1)
    {
        sprintf(buffer, "%d\n", front.read()); // Konwertujemy wartość na string
        uart.print(buffer);

        if (front.read()>500)
        {
            errorLED.on();
        }else{
            errorLED.off();
        }
        
        _delay_ms(200);         

        // errorLED.killError(inputManager.readDecimalValue());            
    }
    
}
