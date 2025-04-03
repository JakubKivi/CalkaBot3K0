#include "../include/Robot.h"
#include "FrontMotor.h"
#include <Arduino.h>


Robot::Robot(volatile uint8_t* ddr, volatile uint8_t* port, 
             uint8_t pinForwardL, uint8_t pinForwardR, uint8_t pinBackwardL, uint8_t pinBackwardR) 
    : ddr(ddr), port(port), pinForwardL(pinForwardL), pinForwardR(pinForwardR), 
      pinBackwardL(pinBackwardL), pinBackwardR(pinBackwardR){

       

        *ddr |= (1 << pinForwardL) | (1 << pinForwardR)
          | (1 << pinBackwardL) | (1 << pinBackwardR);

        *port &= ~((1 << pinForwardL) | (1 << pinForwardR) 
            | (1 << pinBackwardL) | (1 << pinBackwardR));
      }

void Robot::setSpeed(uint8_t speedLeft, uint8_t speedRight) {
    // Ustawienie prędkości PWM (0-255)
    
}

void Robot::forward() {
    *port |= (1 << pinForwardL) | (1 << pinForwardR);
    *port &= ~((1 << pinBackwardL) | (1 << pinBackwardR));
}

void Robot::backward() {
    *port |= (1 << pinBackwardL) | (1 << pinBackwardR);
    *port &= ~((1 << pinForwardL) | (1 << pinForwardR));
}

void Robot::rightTurn() {
    *port |= (1 << pinForwardL) | (1 << pinBackwardR);
    *port &= ~((1 << pinBackwardL) | (1 << pinForwardR));
}

void Robot::leftTurn() {
    *port |= (1 << pinForwardR) | (1 << pinBackwardL);
    *port &= ~((1 << pinForwardL) | (1 << pinBackwardR));
}

void Robot::stop() {
    *port &= ~((1 << pinForwardL) | (1 << pinForwardR) 
             | (1 << pinBackwardL) | (1 << pinBackwardR));
}

void Robot::leftCurve() {
    // Lewe koło porusza się do przodu, prawe koło zatrzymane
    *port |= (1 << pinForwardL); // Włącz napęd lewego koła do przodu
    *port &= ~((1 << pinBackwardL) | (1 << pinForwardR) | (1 << pinBackwardR)); // Wyłącz inne kierunki
}

void Robot::rightCurve() {
    // Prawe koło porusza się do przodu, lewe koło zatrzymane
    *port |= (1 << pinForwardR); // Włącz napęd prawego koła do przodu
    *port &= ~((1 << pinBackwardR) | (1 << pinForwardL) | (1 << pinBackwardL)); // Wyłącz inne kierunki
}

void Robot::position(FrontMotor* frontMotor, int time, bool direction){
    
    frontMotor->on();
    direction ? rightTurn() : leftTurn();
    switch (time)
    {
        case 1:
            _delay_ms(300);
        break;
        case 2:
            _delay_ms(350);
        break;
        default:
            _delay_ms(400);
        break;
    }
    stop();
}