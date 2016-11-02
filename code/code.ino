#include <Wire.h>
#include <Servo.h>
#def DESIRED_HEADING 1
#def SERVO_PIN 9 //PLEASE CHANGE
int HMC6352Address = 0x42;
// This is calculated in the setup() function
int slaveAddress;
byte headingData[2];
int i, headingValue;

Servo rudderServo;

void setup()
{
// Shift the device's documented slave address (0x42) 1 bit right
// This compensates for how the TWI library only wants the
// 7 most significant bits (with the high bit padded with 0)
slaveAddress = HMC6352Address >> 1;   // This results in 0x21 as the address to pass to TWI
//IMPORTANT NOTE A5 is Yellow wire, SCL
//IMPORTANT NOTE A4 is green, SDA

rudderServo.attach(SERVO_PIN);

Serial.begin(9600);
Wire.begin();
}


void loop()
{
  // Send a "A" command to the HMC6352
  // This requests the current heading data
  Wire.beginTransmission(slaveAddress);
  Wire.write("A");              // The "Get Data" command
  Wire.endTransmission();
  delay(10);                   // The HMC6352 needs at least a 70us (microsecond) delay
  // after this command.  Using 10ms just makes it safe
  // Read the 2 heading bytes, MSB first
  // The resulting 16bit word is the compass heading in 10th's of a degree
  // For example: a heading of 1345 would be 134.5 degrees
  Wire.requestFrom(slaveAddress, 2);        // Request the 2 byte heading (MSB comes first)
  i = 0;
  while(Wire.available() && i < 2)
  { 
    headingData[i] = Wire.read();
    i++;
  }
  headingValue = headingData[0]*256 + headingData[1];  // Put the MSB and LSB together //headingValue comes out as 0 to 3600 
  Serial.print("Current heading: ");
 // Serial.print(int (headingValue / 10));     // The whole number part of the heading
  //Serial.print(".");
  //Serial.print(int (headingValue % 10));     // The fractional part of the heading
  //Serial.println(" degrees");
  Serial.println(headingValue);
  delay(500);

//calibrate compass here
 int kP = 1;
 int error = (DESIRED_HEADING - headingValue) / 20; //This can now be sent to the servo (should be from 0 - 180)
 int drive = (error*kP);
 int rudderAngle = 
 rudderServo.write(
 int previousError = error;
     
}

//If at 0 degrees, no change in propeller direction









  


