#include "../include/Robot.h"


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

void Robot::leftTurn() {
    *port |= (1 << pinForwardL) | (1 << pinBackwardR);
    *port &= ~((1 << pinBackwardL) | (1 << pinForwardR));
}

void Robot::rightTurn() {
    *port |= (1 << pinForwardR) | (1 << pinBackwardL);
    *port &= ~((1 << pinForwardL) | (1 << pinBackwardR));
}

void Robot::stop() {
    *port &= ~((1 << pinForwardL) | (1 << pinForwardR) 
             | (1 << pinBackwardL) | (1 << pinBackwardR));
}
