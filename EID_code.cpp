//Force Sensor
#define sensorPin A0
int x = 0;

//Using Force Sensor2 as a capacitance sensor
#define sensorPin1 A1
int capacitance = 0;


//Stepper motor
const int stepPin = 7; 
const int dirPin = 6; 
const int enPin = 5;


//LED lights
int redlight = 12;
int greenlight = 13;


void setup() {
    Serial.begin(9600);

    //Motor speed
    pinMode(stepPin,OUTPUT); 
    pinMode(dirPin,OUTPUT);
    pinMode(enPin,OUTPUT);
    digitalWrite(enPin,LOW);

    /*
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
    */


    //LEDs setup
    pinMode(redlight, OUTPUT);
    pinMode(greenlight, OUTPUT);

}


void brake(){                                 //turn ratio is out of stepsPerRevolution
  digitalWrite(dirPin,HIGH);
  for(int y = 0; y < 300; y++) {                  //x is the control
      //Serial.println(y);
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(1000); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(1000); 
    }
    //delay(1000); // One second delay
    //digitalWrite(dirPin,LOW); //Changes the direction of rotation
    /*
    for(int x = 0; x < 800; x++) {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(500);
    }
    delay(1000); 
}
*/
}


void unbrake(){
  digitalWrite(dirPin,LOW); //Changes the direction of rotation
    
    for(int y = 0; y < 100; y++) {
      //Serial.println(y);
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(1000);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(1000);
    }
   // delay(1000); 
}



void loop(){

    //touch sensor input
    //currtouched = cap.touched();
    
    //FSR input
    x = analogRead(sensorPin);
    //x1 = analogRead(sensorPin1);
    Serial.println(x);

    int z = 0;

    while (x>50){
        capacitance = analogRead(sensorPin1);
        
        if (capacitance>100 && z==0){
        //if (cap.touched()){
            Serial.println("brake released");
            unbrake();
            digitalWrite(greenlight, HIGH);
            digitalWrite(redlight, LOW);
            delay(2000);  
            z=z+1;
            

        }

        else if (capacitance<100){
          Serial.println("user still holding");
          break;
        }

        else{
          z=z+1;
        }
    }

    if (x<50){
        Serial.println("Engaging brakes");
        brake();
        //z = z+1;
        Serial.println("Braked");
        digitalWrite(redlight, HIGH);
        digitalWrite(greenlight, LOW);
        Serial.println("Safe");
        delay(2000);
        
        while(true){  
            x = analogRead(sensorPin); 
            Serial.println(x);   
            if (x>100){
              Serial.println("User has returned");
              break;
            }
        }
        

        /*
        x = analogRead(sensorPin);
        if (x>100)Serial.println("User has returned");
        */
    }
}
