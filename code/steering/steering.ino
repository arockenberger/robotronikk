// this constant won't change:
const int  pinLeft = 4;    // the pin that the pushbutton is attached to
const int  pinRight = 2;    // the pin that the pushbutton is attached to
boolean flagLeft = 0;
boolean flagRight = 0; 

const int wheelCirc = 221; //Wheel cicumferance i mm
const int pulses = 20; // pulses per rotation
const int travel = wheelCirc/pulses; // traveled distance per pulse
const int forward = 50;
const int backward = 137;
const int stopped = 90;
int currentSpeed = 0;
int left = 0;
int right =0;
unsigned long timerL = 0;
unsigned long timerR = 0;


#include <Servo.h>

Servo myservoLeft;  
Servo myservoRight;  

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
unsigned long timer = 0;
int pos =90;
int speedCount = 0;
int countLast = 0;
int count = 0;
unsigned long time1 = 0;


 
void setup() {
  // put your setup code here, to run once:
        // initialize serial communication:
    Serial.begin(9600);
        // initialize the button pin as a input:
    pinMode(pinLeft, INPUT);
        pinMode(pinRight, INPUT);
  myservoLeft.attach(10); 
  myservoRight.attach(9); 
  left  = 20; // drive X cm forward on the left side
right = 10; // drive X cm forward on the right side

}

void loop() {


drive();
counter();
if (millis() % 600 > 300){
Serial.print(left);
Serial.print(" " );
Serial.print(right);
Serial.println();
}
 
}



void drive(){

if (left > right && left > 0 ) {
    myservoLeft.write(backward); //soldered it backward
} 
if (right > left && right > 0 ) {
    myservoRight.write(forward); 
} 

if (right == left && left > 0) {
    myservoRight.write(forward); 
    myservoLeft.write(backward); //soldered it backward
} 

if (left  < 0 ) {
    myservoLeft.write(stopped); 
} 
if (right  < 0 ) {
    myservoRight.write(stopped); 
    Serial.println("here");
} 

  
}




int counter(){
  boolean leftState = digitalRead(pinLeft);
  boolean rightState = digitalRead(pinRight);
  if (rightState != flagRight && rightState == HIGH && millis()-timerR >= 50 ) {
    timerR = millis();
    right = right - 1;

    }
  if (leftState != flagLeft && leftState == HIGH && millis()-timerL >= 50 )  {
    timerL = millis();
    left = left - 1;
    }
 flagLeft = leftState;
 flagRight = rightState;
}


