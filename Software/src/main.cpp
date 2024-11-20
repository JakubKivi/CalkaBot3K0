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
#include "../include/Robot.h"
#include "../lib/SoftPWM.h"
#include "../lib/SoftPWM.h"

SOFTPWM_DEFINE_CHANNEL(0, ROBOT_RIGHT_DDR, ROBOT_RIGHT_PORT, ROBOT_RIGHT_PIN); // Pin 13
SOFTPWM_DEFINE_CHANNEL(1, ROBOT_LEFT_DDR, ROBOT_LEFT_PORT, ROBOT_LEFT_PIN); // Pin 12
SOFTPWM_DEFINE_OBJECT_WITH_PWM_LEVELS(2, 255);

Robot calkaBot(&DDRB, &PORTB, PB2, PB0, PB3, PB1);
InputManager inputManager(&PORTD, &DDRD, &PIND, PD4, PD5, PD6, PD7);    //Switche na płytce
FrontMotor frontMotor(&PORTD, &DDRD, PD3);  //Sterowanie ramionami
BuildLed errorLED(&PORTC, &DDRC, PC5);      //Wbudowana dioda informacyjna
Sensor floorLeft(0);                        //Lewy czujnik linii
Sensor floorRight(1);                       //Prawy czujnik linii
Sensor front(3);                            //Czujnik przeciwnika, środkowy

void setup() {
  Palatis::SoftPWM.begin(200);  //SoftPWM init z częstotliwością 200Hz
  Palatis::SoftPWM.set(0, 100); // Kanał 0 (pin 13): wartość 50
  Palatis::SoftPWM.set(1, 100); // Kanał 1 (pin 12): wartość 50
  Serial.begin(9600);
}

void loop() {

  switch (inputManager.readDecimalValue())
  {
    case 0:
        errorLED.off();
        if (front.read()>500)
        {
            calkaBot.backward();
            _delay_ms(200);
            calkaBot.rightTurn();
            _delay_ms(200);
        }else{
            calkaBot.forward();
        }
    break;
    case 1:
        calkaBot.stop();
        errorLED.toggle();
        frontMotor.toggle();
        _delay_ms(2000);
    break;

    default:
        calkaBot.stop();
        Serial.println("Floor L: "+String(floorLeft.read()) + " R: "+String(floorRight.read())+ "   Front: "+ String(front.read())+ "      Inputs: "+String(inputManager.readDecimalValue()));
        delay(500);
        errorLED.toggle();
    break;
  }
  
  

  // if (front.read()>500)
  // {
  //     calkaBot.backward();
  //     _delay_ms(200);
  //     calkaBot.rightTurn();
  //     _delay_ms(200);
  // }else{
  //     calkaBot.forward();
  // }
  // _delay_ms(10);
  // Pętla może pozostać pusta — PWM działa w tle
}
