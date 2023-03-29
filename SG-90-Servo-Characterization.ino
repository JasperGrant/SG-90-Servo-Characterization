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
  //Display position
  Serial.print("Position: ");
  ;Serial.print(pos);
  //Display the Gyro
  Serial.print(", Gyro:[ ");
  Serial.print(Ogyro.x); Serial.print(",");
  Serial.print(Ogyro.y); Serial.print(",");
  Serial.print(Ogyro.z); Serial.print(" ]");
  Serial.print(", Accel:[ ");
  Serial.print(Oaccel.x); Serial.print(",");
  Serial.print(Oaccel.y); Serial.print(",");
  Serial.print(Oaccel.z); Serial.print(" ]\n");

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
  myservo.attach(SERVO_PWM_PIN);
 }
}

int temp_pos = 0;

//Main loop
void loop() {
  //For every PWM
  for(pos = 0; pos < 180; pos+=5){
    //Stay at 0 for 2s
    myservo.write(0);
     //Temp pos allows you to print 0 when your pos is not actually 0.
    temp_pos = pos;
    pos = 0;
    delayWhileprintOut(2);
    pos = temp_pos;
    //Go to angle for 2s
    myservo.write(pos);
    
    delayWhileprintOut(2);
  }

}
