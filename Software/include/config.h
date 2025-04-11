#ifndef CONFIG_H
#define CONFIG_H

#define LEFT_FLOOR_THRESHOLD 100        //Podłoża
#define RIGHT_FLOOR_THRESHOLD 100

#define LINE_DETCTION_RIGHT_TURN_LENGHT 200 
#define LINE_DETCTION_LEFT_TURN_LENGHT 200 
#define LINE_DETCTION_BACKWARD_LENGHT 250

#define FRONT_THRESHOLD 250             //Przeciwnika
#define FRONT_RIGHT_THRESHOLD 200
#define FRONT_LEFT_THRESHOLD 250

#define FRONT_FULLSPEED_THRESHOLD 500   //kiedy załączamy max power
#define FULL_SPEED  255
#define SEARCH_SPEED 110                //prędkości przed i po thresholdzie

#define POSITIONING_LEFT_TURN_1 150
#define POSITIONING_LEFT_TURN_2 200
#define POSITIONING_LEFT_TURN_3 250

#define POSITIONING_RIGHT_TURN_1 350
#define POSITIONING_RIGHT_TURN_2 400
#define POSITIONING_RIGHT_TURN_3 450             //długość obrotu przy positioningu


#define SEARCH_RIGHT_CURVE 120            //Jak długo powinien skręcać w daną stronę podczas szukania
#define SEARCH_LEFT_CURVE 120

#endif 