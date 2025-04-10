#include "../include/config.h"
#include "../include/FrontMotor.h"  
#include "../include/InputManager.h"
#include "../include/BuildLED.h"
#include "../include/Sensor.h"
#include "../include/Robot.h"
#include "../lib/SoftPWM.h"



SOFTPWM_DEFINE_CHANNEL(0, ROBOT_RIGHT_DDR, ROBOT_RIGHT_PORT, ROBOT_RIGHT_PIN);   // Soft PWM na Pin 13
SOFTPWM_DEFINE_CHANNEL(1, ROBOT_LEFT_DDR, ROBOT_LEFT_PORT, ROBOT_LEFT_PIN);      // Soft PWM na Pin 12
SOFTPWM_DEFINE_OBJECT_WITH_PWM_LEVELS(2, 255);                                   // Makra dla SoftPWM

Robot calkaBot(&DDRB, &PORTB, PB3, PB0, PB2, PB1);                      // Silniki w kołach
InputManager inputManager(&PORTD, &DDRD, &PIND, PD4, PD5, PD6, PD7);    // Switche na płytce
FrontMotor frontMotor(&PORTD, &DDRD, PD3);                              // Sterowanie ramionami
BuildLed buildLed(&PORTC, &DDRC, PC5);                                  // Wbudowana dioda informacyjna

Sensor floorLeft(0);                                                    // Czujniki linii, lewy
Sensor floorRight(1);                                                   //               , prawy

Sensor front(3);                                                        // Czujniki przeciwnika , środkowy
Sensor left(4);                                                         //                      , lewy
Sensor right(2);                                                        //                      , prawy


void setup() {
    Palatis::SoftPWM.begin(200);  
    Palatis::SoftPWM.set(0, FULL_SPEED); 
    Palatis::SoftPWM.set(1, FULL_SPEED);    //dla pozycjonowania na starcie


    pinMode(2, INPUT_PULLUP);
    Serial.begin(9600);

}

bool positioned = false;

bool curve = true;

void loop() {
    if (digitalRead(2)){  
        switch (inputManager.readDecimalValue())
        {
            case 0:
                positioned = false;
                calkaBot.stop();
                frontMotor.off();
                Serial.println("Left: "+ String(left.read()) + "    Mid: " + String(front.read()) +"       Right: " + String(right.read() ));
                
                if (front.read() > FRONT_THRESHOLD or right.read() > FRONT_RIGHT_THRESHOLD or left.read() > FRONT_LEFT_THRESHOLD)
                {
                    buildLed.on();
                }else{
                    buildLed.off();
                }
                _delay_ms(500);
            break;
            


            case 1:
            break;
            case 2:                    
            case 3:         //lewo bez szukania
            case 5:
            case 6:
            case 7:         //prawo bez szukania
            case 9:
            case 10:
            case 11:        //lewo z szukaniem
            case 13:
            case 14:
            case 15:        //prawo z szukaniem
                if (!positioned)
                {
                    delay(3000);
                    int positioningTime = 1;
                    if(inputManager.readPin(PD4)) positioningTime+=1;
                    if(inputManager.readPin(PD5)) positioningTime+=2;
                    calkaBot.position(&frontMotor, &left, &front, &right, positioningTime, inputManager.readPin(PD6));
                    positioned = true; 

                }else{

                    if(front.read() > FRONT_FULLSPEED_THRESHOLD){           //NA BLISKO RURA!
                        Palatis::SoftPWM.set(0, FULL_SPEED); 
                        Palatis::SoftPWM.set(1, FULL_SPEED); 
                    }else{
                        Palatis::SoftPWM.set(0, SEARCH_SPEED); 
                        Palatis::SoftPWM.set(1, SEARCH_SPEED); 
                    }

                    if (front.read()>FRONT_THRESHOLD)
                    {
                        calkaBot.forward();
                    }else if(right.read() > FRONT_RIGHT_THRESHOLD){
                        calkaBot.rightCurve();
                    }else if(left.read() > FRONT_LEFT_THRESHOLD){
                        calkaBot.leftCurve();
                    }else{
                        if (inputManager.readPin(PD7))        //Kręcenie włączone
                        {
                            if (floorLeft.read() < LEFT_FLOOR_THRESHOLD || floorRight.read() < RIGHT_FLOOR_THRESHOLD)
                            {
                                calkaBot.backward();
                                _delay_ms(LINE_DETCTION_BACKWARD_LENGHT);
                                calkaBot.rightTurn();
                                _delay_ms(LINE_DETCTION_TURN_LENGHT);
                            }else{
                                if (curve)
                                {
                                    calkaBot.leftTurn();
                                    _delay_ms(SEARCH_LEFT_CURVE);  //TODO sprawdzanie w trakcie
                                }else{
                                    calkaBot.rightTurn();
                                    _delay_ms(SEARCH_RIGHT_CURVE);
                                }
                                curve = !curve;
                            }
                        }else{
                            calkaBot.stop();
                        }
                    }
                }
            break;

            case 4:
            case 8:
            case 12:            
                frontMotor.off();
                calkaBot.forward();
                buildLed.toggle();
                _delay_ms(100);
            break;
            
            default:
                positioned = false;
                frontMotor.off();
                calkaBot.stop();
                buildLed.toggle();
                _delay_ms(100);
            break;
        }
    }else{
        positioned = false;
        frontMotor.off();
        calkaBot.stop();
        buildLed.toggle();
        _delay_ms(100);
    }
}

    // ===================================== INŻYNIERKA ====================(tak. z błędami. późno było xd ale padaka xd)======== //
    // while (!positioned)
    // {
    //     if (digitalRead(2))   // Sygnał startowy na złączu J6
    //     {
    //         frontMotor.on();    //Uruchom silniki w ramionach
    //         if (inputManager.readPin(4)) 
    //         {
    //             //Wykonaj program specjalny

    //         }else{
    //             if (inputManager.readPin(1))        //Przodem do siebie
    //             {
    //                 if (inputManager.readPin(2))            //korekta w lewo
    //                 {
    //                     calkaBot.leftTurn();
    //                     delay(ALIGNMENT_TURN_LENGHT);
    //                     positioned=true;
    //                 }else{                                 //korekta w prawo
    //                     calkaBot.rightTurn();
    //                     delay(ALIGNMENT_TURN_LENGHT);
    //                 }
                    
    //             }else{                              //Tyłem do siebie
    //                 if (inputManager.readPin(2))            //korekta w lewo
    //                 {
    //                     calkaBot.leftTurn();
    //                     delay(BACKWARDS_ALIGNMENT_TURN_LENGHT);
    //                 }else{                                 //korekta w prawo
    //                     calkaBot.rightTurn();
    //                     delay(BACKWARDS_ALIGNMENT_TURN_LENGHT);
    //                 }
    //             }
                
    //         }
    //         positioned=true;
    //     }
    // }

    // while(positioned){
    //     if (front.read()>FRONT_THRESHOLD)
    //     {
    //         calkaBot.forward();
    //     }else if(right.read()>FRONT_THRESHOLD){
    //         calkaBot.rightCurve();
    //     }else if(left.read()>FRONT_THRESHOLD){
    //         calkaBot.leftCurve();
    //     }else{
    //         if (inputManager.readPin(3))        //Przeszukiwanie włączone
    //         {
    //             if (floorLeft.read() > LEFT_FLOOR_THRESHOLD || floorRight.read() > RIGHT_FLOOR_THRESHOLD)
    //             {
    //                 calkaBot.backward();
    //                 _delay_ms(LINE_DETCTION_BACKWARD_LENGHT);
    //                 calkaBot.rightTurn();
    //                 _delay_ms(LINE_DETCTION_TURN_LENGHT);
    //             }else{
    //                 calkaBot.forward();
    //             }                
    //         }
    //     }
        
    // }

