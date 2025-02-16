#include "../include/FrontMotor.h"  //Dołączenie plików nagłówkowycg
#include "../include/InputManager.h"
#include "../include/BuildLED.h"
#include "../include/Sensor.h"
#include "../include/Robot.h"
#include "../lib/SoftPWM.h"

#define LEFT_FLOOR_THRESHOLD 100
#define RIGHT_FLOOR_THRESHOLD 100

#define FRONT_THRESHOLD 250
#define FRONT_RIGHT_THRESHOLD 200
#define FRONT_LEFT_THRESHOLD 200

#define LINE_DETCTION_TURN_LENGHT 200 
#define LINE_DETCTION_BACKWARD_LENGHT 150

#define ALIGNMENT_TURN_LENGHT 100
#define BACKWARDS_ALIGNMENT_TURN_LENGHT 300


SOFTPWM_DEFINE_CHANNEL(0, ROBOT_RIGHT_DDR, ROBOT_RIGHT_PORT, ROBOT_RIGHT_PIN);   // Soft PWM na Pin 13
SOFTPWM_DEFINE_CHANNEL(1, ROBOT_LEFT_DDR, ROBOT_LEFT_PORT, ROBOT_LEFT_PIN);      // Soft PWM na Pin 12
SOFTPWM_DEFINE_OBJECT_WITH_PWM_LEVELS(2, 255);                                   // Makra dla SoftPWM

Robot calkaBot(&DDRB, &PORTB, PB2, PB0, PB3, PB1);                      // Silniki w kołach
InputManager inputManager(&PORTD, &DDRD, &PIND, PD4, PD5, PD6, PD7);    // Switche na płytce
FrontMotor frontMotor(&PORTD, &DDRD, PD3);                              // Sterowanie ramionami
BuildLed errorLED(&PORTC, &DDRC, PC5);                                  // Wbudowana dioda informacyjna
Sensor floorLeft(0);                                                    // Czujnik linii, lewy
Sensor floorRight(1);                                                   // Czujnik linii, prawy
Sensor front(3);                                                        // Czujnik przeciwnika, środkowy
Sensor left(2);                                                         // Czujnik przeciwnika, lewy
Sensor right(4);                                                        // Czujnik przeciwnika, prawy

void setup() {
  Palatis::SoftPWM.begin(200);  // inicjalizacja SoftPWM z częstotliwością 200Hz
  Palatis::SoftPWM.set(0, 100); // Kanał 0 (pin 13): wartość 100
  Palatis::SoftPWM.set(1, 100); // Kanał 1 (pin 12): wartość 100
}

bool positioned = false;

void loop() {

    while (!positioned)
    {
        if (digitalRead(2))   // Sygnał startowy na złączu J6
        {
            frontMotor.on();    //Uruchom silniki w ramionach
            if (inputManager.readPin(4)) 
            {
                //Wykonaj program specjalny

            }else{
                if (inputManager.readPin(1))        //Przodem do siebie
                {
                    if (inputManager.readPin(2))            //korekta w lewo
                    {
                        calkaBot.leftTurn();
                        delay(ALIGNMENT_TURN_LENGHT);
                        positioned=true;
                    }else{                                 //korekta w prawo
                        calkaBot.rightTurn();
                        delay(ALIGNMENT_TURN_LENGHT);
                    }
                    
                }else{                              //Tyłem do siebie
                    if (inputManager.readPin(2))            //korekta w lewo
                    {
                        calkaBot.leftTurn();
                        delay(BACKWARDS_ALIGNMENT_TURN_LENGHT);
                    }else{                                 //korekta w prawo
                        calkaBot.rightTurn();
                        delay(BACKWARDS_ALIGNMENT_TURN_LENGHT);
                    }
                }
                
            }
            positioned=true;
        }
    }

    while(positioned){
        if (front.read()>FRONT_THRESHOLD)
        {
            calkaBot.forward();
        }else if(right.read()>FRONT_THRESHOLD){
            calkaBot.rightCurve();
        }else if(left.read()>FRONT_THRESHOLD){
            calkaBot.leftCurve();
        }else{
            if (inputManager.readPin(3))        //Przeszukiwanie włączone
            {
                if (floorLeft.read() > LEFT_FLOOR_THRESHOLD || floorRight.read() > RIGHT_FLOOR_THRESHOLD)
                {
                    calkaBot.backward();
                    _delay_ms(LINE_DETCTION_BACKWARD_LENGHT);
                    calkaBot.rightTurn();
                    _delay_ms(LINE_DETCTION_TURN_LENGHT);
                }else{
                    calkaBot.forward();
                }                
            }
        }
        
    }

}
