// this constant won't change:
const int  pinLeft = 4;    // the pin that the pushbutton is attached to
const int  pinRight = 2;    // the pin that the pushbutton is attached to
const int wheelCirc = 221; //Wheel cicumferance i mm
const int pulses = 20; // pulses per rotation
const int travel = wheelCirc/pulses; // traveled distance per pulse
const int forward = 50; // PWM setting for the motor driver
const int backward = 137;// PWM setting for the motor driver
const int stopped = 90; // PWM setting for the motor driver


const int pingPin = 7; //the arduino pin that communicates with the ultrasound sensor:
const long timeout = 400 * 29 * 2; //Timeout in microseconds for a max range of 400 cm
long duration, mm;

// Variables will change:
int left = 0; //how far to drive 
int right =0; //how far to drive 
unsigned long timerL = 0; // debounce timer
unsigned long timerR = 0; // debounce timer
boolean flagLeft = 0; // for the pulse counter
boolean flagRight = 0; // for the pulse counter
int servoPos = 90; //goes from 0 to 180 deg, 90 is in the middle (actually 100)
int scanStep = 15; //the ultrasound can see 15 deg
boolean scanDir = 0; // the direction the scanner is moving
int scanTime = 150; // for timing of the scanner
unsigned long scanTimer = 0; // for timing of the scanner
int dir = 0; //direction
int dirLongest = 0;
int longest = 0;
int distance =0; 
int reporter = 500;

#include <Servo.h>
Servo motorLeft;  
Servo motoRight;  
Servo myservo;  //holds the ultrasound sensor

void setup() {
  // put your setup code here, to run once:
        // initialize serial communication:
    Serial.begin(9600);
        // initialize the button pin as a input:
    pinMode(pinLeft, INPUT);
        pinMode(pinRight, INPUT);
  motorLeft.attach(10); // motor driver 
  motoRight.attach(9); // motor driver 
    myservo.attach(3); // Servo on pin 3
left  = 0; // drive X cm forward on the left side
right = 0; // drive X cm forward on the right side

}

void loop() {


drive();
counter();
int directionDrive = scan();
if(directionDrive != 0){  //Change so that it can use the measured longest distance and middle direction
  if (directionDrive < 0){
    right= -directionDrive;
      // right
  }else {
left= directionDrive;
   // left
  }
}

}



void drive(){

if (left > right && left > 0 ) {
    motorLeft.write(backward); //soldered it backward
} 
if (right > left && right > 0 ) {
    motoRight.write(forward); 
} 

if (right == left && left > 0) {
    motoRight.write(forward); 
    motorLeft.write(backward); //soldered it backward
} 

if (left  < 0 ) {
    motorLeft.write(stopped); 
    left = 0;
} 
if (right  < 0 ) {
    motoRight.write(stopped); 
    right= 0;
 
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

int scan(){
if(millis() - scanTimer > scanTime){// only act if it's time to scan
  scanTimer = millis(); // reset the timer
  myservo.write(servoPos);              // tell servo to go to position in variable 'servoPos'
 if (scanDir == 0) {
     servoPos = servoPos - scanStep;
     dir = dir -1 ;
    }else {
       servoPos = servoPos + scanStep;
       dir = dir+1;
    }


distance = ping();
if (distance > longest ){
longest = distance;
dirLongest = dir; // current dir
}

    
 if (servoPos >= 135 || servoPos <= 45){   //Invert scanDir if we have reached either end
    scanDir = !scanDir; 
    return dirLongest;
     longest = 0; // reset
    } else {
      return 0;}



}
}

int ping(){

  // The sensor is triggered by a HIGH signal for 10 microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse and 
  // to reset the sensor if it didn't register an echo from the last ping:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(10);  //replace with timer
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10); //replace with timer
  digitalWrite(pingPin, LOW);
  // The same pin is used to read the signal from the Sensor: A HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH,timeout);
  // convert the time into a distance
  mm = microsecondsToMillimeters(duration);
return mm;
}

long microsecondsToMillimeters(long microseconds) {
  // The speed of sound is 343 m/s or 2.9215 microseconds per millimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds * 10000 /29215 / 2;
}

