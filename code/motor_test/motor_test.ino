/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(10);  // attaches the servo on pin 9 to the servo object
}

void loop() {

    myservo1.write(90);              // tell servo to go to position in variable 'pos'
        delay(10);
            myservo1.write(160);              // tell servo to go to position in variable 'pos'
        delay(1000);
             myservo1.write(90);              // tell servo to go to position in variable 'pos'       
        delay(10);
             myservo1.write(10);              // tell servo to go to position in variable 'pos'       
        delay(1000);

}

