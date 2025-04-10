#include "../include/Robot.h"
#include "FrontMotor.h"
#include <Arduino.h>
#include "../lib/SoftPWM.h"
#include "../include/config.h"
#include "../include/Sensor.h"


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

void Robot::position(FrontMotor* frontMotor, Sensor* left, Sensor* front, Sensor* right, int time, bool direction){
    
    int timeInMs;
    if (direction)
    {
        rightTurn();
        switch (time)
        {
            case 1:
                timeInMs =POSITIONING_RIGHT_TURN_1;
            break;
            case 2:
                timeInMs =POSITIONING_RIGHT_TURN_2;
            break;
            default:
                timeInMs =POSITIONING_RIGHT_TURN_3;
            break;
        }
    }else{
        leftTurn();
        switch (time)
        {
            case 1:
                 timeInMs =POSITIONING_LEFT_TURN_1;
            break;
            case 2:
                timeInMs =POSITIONING_LEFT_TURN_2;
            break;
            default:
                timeInMs =POSITIONING_LEFT_TURN_3;
            break;
        }
    }
    int i = 0;
    while ( i < timeInMs ){
        delay(10);
        i+=10;
        if(right->read() > FRONT_RIGHT_THRESHOLD && front->read()>FRONT_THRESHOLD && left->read() > FRONT_LEFT_THRESHOLD) //jak coś widzisz to przestań
            break;
    }
    
    frontMotor->on();
    stop();
}