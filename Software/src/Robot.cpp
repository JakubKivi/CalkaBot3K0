#include "../include/Robot.h"
#include "FrontMotor.h"
#include <Arduino.h>
#include "../lib/SoftPWM.h"


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
    
//   Palatis::SoftPWM.set(0, 255); // Kanał 0 (pin 13): wartość 100
//   Palatis::SoftPWM.set(1, 255); // Kanał 1 (pin 12): wartość 100
    
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
    // Lewe  do przodu, prawe zatrzymane
    

    *port |= (1 << pinForwardR); 
    *port &= ~((1 << pinBackwardR) | (1 << pinForwardL) | (1 << pinBackwardL)); 
}

void Robot::rightCurve() {
    // Prawe do przodu, lewe zatrzymane
    
    *port |= (1 << pinForwardL); 
    *port &= ~((1 << pinBackwardL) | (1 << pinForwardR) | (1 << pinBackwardR)); 
}

void Robot::position(FrontMotor* frontMotor, int time, bool direction){
    
    frontMotor->on();
    if (direction)
    {
        rightTurn();
        switch (time)
        {
            case 1:
                _delay_ms(450);
            break;
            case 2:
                _delay_ms(500);
            break;
            default:
                _delay_ms(550);
            break;
        }
    }else{
        leftTurn();
        switch (time)
        {
            case 1:
                _delay_ms(200);
            break;
            case 2:
                _delay_ms(250);
            break;
            default:
                _delay_ms(300);
            break;
        }
    }
    
    
    stop();
}