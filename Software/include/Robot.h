#ifndef ROBOT_H
#define ROBOT_H

#include <avr/io.h>
#include "FrontMotor.h"
#include "../include/Sensor.h"

#define ROBOT_RIGHT_DDR DDRB
#define ROBOT_RIGHT_PORT PORTB
#define ROBOT_RIGHT_PIN PORTB5  

#define ROBOT_LEFT_DDR DDRB
#define ROBOT_LEFT_PORT PORTB
#define ROBOT_LEFT_PIN PORTB4   //Definicje w preprocesorze potrzebne dla poprawnego działania biblioteki SoftPWM

class Robot {
private:
    volatile uint8_t* ddr;    // Wskaźnik na DDR
    volatile uint8_t* port;   // Wskaźnik na PORT
    uint8_t pinForwardL;      // Pin dla lewego przodu
    uint8_t pinForwardR;      // Pin dla prawego przodu
    uint8_t pinBackwardL;     // Pin dla lewego tyłu
    uint8_t pinBackwardR;     // Pin dla prawego tyłu

public:
    Robot(volatile uint8_t* ddr, volatile uint8_t* port, 
          uint8_t pinForwardL, uint8_t pinForwardR, uint8_t pinBackwardL, uint8_t pinBackwardR);

    void setSpeed(uint8_t speed1, uint8_t speed2);

    void forward();
    void backward();
    void leftTurn();
    void rightTurn();
    void leftCurve();
    void rightCurve();
    void stop();

    void position(FrontMotor* frontMotor, Sensor* left, Sensor* front, Sensor* right,  int time, bool direction); // 0 - left, 1 - right
};

#endif
