/*
SG-90 Servo Characterization Test Rig

Uses a BMX160 to characterize the motion of a SG-90 servo.
Code will follow a predetermined pattern to apply different PWM
signals to servo and record response.

Written by Jasper Grant 2023-03-24

Pins of BMX160:
D : A5
C : A4
- : GND
+ : 5V

Pins of SG-90:
Orange  : Pin 6 (Signal)
Red     : 5V
Brown   : GND
*/

//Define signal pin of Servo
#define SERVO_PWM_PIN 6

void setup() {
  //Start serial
  Serial.begin(115200);
  //Set servo pin to output
  pinMode(SERVO_PWM_PIN, OUTPUT);
}

void loop() {


}
