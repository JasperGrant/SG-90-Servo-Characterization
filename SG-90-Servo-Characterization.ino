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

//Include IMU library
#include <DFRobot_BMX160.h>
//Include Servo library
#include <Servo.h>

//Define signal pin of Servo
#define SERVO_PWM_PIN 9

//Declare global IMU object
DFRobot_BMX160 bmx160;
//Declare objects to represent data from each device in IMU
bmx160SensorData Omagn, Ogyro, Oaccel;
//I2C address for Gyro
const int8_t i2c_addr = 0x69;

//Declare global servo object
Servo myservo;

//Global PWM so that printOut can print it
int pos = 0;

//Function to print out IMU data along with Servo PWM
void printOut() {
  //Get data from I2C registers
  bmx160.getAllData(&Omagn, &Ogyro, &Oaccel);
  //Display PWM
  //Serial.print(angle);
  //Display the Gyro
  Serial.print(" Gyro:[ ");
  Serial.print(Ogyro.x); Serial.print(" ");
  Serial.print(Ogyro.y); Serial.print(" ");
  Serial.print(Ogyro.z); Serial.print(" ]\n");

}

//Function to delay while printing out data
//Takes number of seconds to delay
void delayWhileprintOut(int seconds){
  //Set starting time
  int start_time = millis();
  //While number of seconds has not yet passed
  while(millis() < start_time + seconds*1000){
    //Print out data
    printOut();
    //Delay 100ms to make the sampling frequency 10 times/second or 0.1Hz
    delay(100);
  }

}

void setup() {
  //Start serial
  Serial.begin(115200);
  //Set servo pin to output
  //pinMode(SERVO_PWM_PIN, OUTPUT);
  //Ensure Gyro is set up
  while (bmx160.begin() != true){
  Serial.print("init false");
  //Attach servo to servo pin
  myservo.attach(9);
 }
}

//Main loop
void loop() {
  //For every PWM 
  /*
  for(angle = 1; angle<= 180; angle++){
    //Sit at 0 for 2s
    myservo.write(angle);
    delay(15);
  
    /*
    delayWhileprintOut(2);
    //Go to chosen PWM for 2s
    myservo.write(90);
    delayWhileprintOut(2);
/*
*/
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position

  }

}
