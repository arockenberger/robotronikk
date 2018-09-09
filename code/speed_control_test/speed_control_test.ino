// this constant won't change:
const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int wheelCirc = 221; //Wheel cicumferance i mm
const int pulses = 20; // pulses per rotation
const int travel = wheelCirc/pulses; // traveled distance per pulse
int currentSpeed = 0;

#include <Servo.h>

Servo myservo;  

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
int targetSpeed = 20; // pul per s
 
void setup() {
  // put your setup code here, to run once:
        // initialize serial communication:
    Serial.begin(9600);
        // initialize the button pin as a input:
    pinMode(buttonPin, INPUT);
  myservo.attach(9); 

}

void loop() {


while( pos < 180){
  count = counter(); // run all the time to listen.
myservo.write(pos);
 if (millis()-time1 >= 500){
  pos++;
 time1 = millis();
 speedCount = count - countLast;
 countLast = count;

Serial.print(pos); // ca en cm per pul
Serial.print(" "); // ca en cm per pul
Serial.println(speedCount); // ca en cm per pul

 }
} 
pos = 90;
}



int counter(){
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH && millis()-timer >= 50 ){
      timer = millis();
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
    } 
    }
 lastButtonState = buttonState;
  return buttonPushCounter;
}


int speed(){ //can't call this too often
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) { // if the state has changed
      lastButtonState = buttonState;// save the current state as the last state, for next time through the loop
    if (buttonState == HIGH) { // if the current state is HIGH then the button went from off to on:
int diff = millis()-timer; // how long has past since last rising edge
// could insert a minimum requirement here for debounce!
timer = millis(); // reset the timer
currentSpeed = 100*travel /diff; // in cm /s
if ( currentSpeed > 100){
  return 0;
}else {
  return currentSpeed;
  }
    }
}
}


