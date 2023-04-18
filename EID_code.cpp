//capacitive touch sensor, must download the ADAfruit library

#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

Adafruit_MPR121 cap = Adafruit_MPR121(;)

int16_t lasttouched = 0;
int16_t currtouched = 0;            //keep track of last pins touched


//FSR
#define sensorPin A0
int x = 0;


//Stepper motor
#include <Stepper.h>

const int stepsPerRevolution = 2038;        //Defines the no.of steps per rotation, can try decreasing the steps to make it faster? or see the diff

Stepper myStepper = Stepper(stepsPerRevolution, 8, 9, 10, 11);
float turn_ratio = 0;


//LED lights
int redlight = 8;
int yellow_light = 9;


void setup() {
    Serial.begin(115200);


    //MPR121 setup
    while (!Serial) {
        delay(10);
    }

    Serial.println("MPR121 touch sensor test");

    if (!cap.begin(0x5A)) {
        Serial.println("MPR121 not found");
        while (1);
    }

    Serial.println("MPR121 found");


    //LEDs setup
    pinMode(redlight, OUTPUT);
    pinMode(yellow_light, OUTPUT);

}



void loop()

    //touch sensor input
    //currtouched = cap.touched();
    
    //FSR input
    x = analogRead(sensorPin);
    Serial.println(x);

    while (x>...){
        if (cap.touched()){
            brake_arm(0.25);
            digitalWrite(yellow_light, HIGH);
        }

        else if (!cap.touched())
            break;
    }

    else{
        brake_arm(-0.25);
        while (True){
            digitalWrite(redlight, HIGH);
            if (x>...)break;
        }
    }


    



void brake_arm(turn_ratio)
    myStepper.setspeed(5);             //try different speeds see if it affects torque
    myStepper.step(turn_ratio*stepsPerRevolution);





    

