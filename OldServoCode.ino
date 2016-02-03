#include <Servo.h> 
 
Servo baseServo;  // create servo object to control base motor 
Servo elbowMotor; // creates servo object for rotation servo
Servo wristServo; // creates a servo object for wrist servo
Servo armMotor1; // creates a servo object for first arm motor
Servo armMotor2; // creates a servo object for second arm motor
Servo clawServo; // creates a servo object for claw servo

const int wristupPin = 3;    // buttton pin for wrist up button
const int wristdownPin = 4;  // button pin for wrist down button
const int clawbuttonPin = 5; // button pin for claw control button
const int xPin1 = 0;  // analog pin used for x axis of first joystick
const int yPin1 = 1;  // analog pin used for y axis of first joystick
const int xPin2 = 2;  // analog pin used for x axis of second joystick
const int yPin2 = 3;  // analog pin used for y axis of second joystick
int xVal1;      // variable to hold the value from the analog x pin for the first joysick
int yVal1;      // variable to hold the value from the analog y pin for the first joysick
int xVal2;      // variable to hold the value from the analog x pin for the second joysick
int yVal2;      // variable to hold the value from the analog y pin for the second joysick
int y2Val1;     // variable to hold the inverted value from the analog y pin for the first joysick
int wristVal = 90; // varialbe to hold the position of the wrist servo
boolean clawOpen = true; // boolean to hold the state of the claw, open or closed
int initially = 0;
int previous = 0;
 
void setup() 
{ 
  Serial.begin(9600);            // initializes serial communication over usb to IDE
  clawServo.attach(8);           // attaches the claw servo on pin 8 to the servo object 
  baseServo.attach(9);           // attaches the base servo on pin 9 to the servo object 
  armMotor1.attach(10);          // attaches the first arm motor on pin 10 to the servo object 
  armMotor2.attach(11);          // attaches the second arm motor on pin 11 to the servo object 
  wristServo.attach(12);         // attaches the wrist servo on pin 12 to the servo object
  elbowMotor.attach(13);          
  pinMode(wristupPin, INPUT);    // sets the wrist up button pin to input
  pinMode(wristdownPin, INPUT);  // sets the wrist down button pin to input
  pinMode(clawbuttonPin, INPUT); // sets the claw control button pin to input
} 
 
void loop() // Loops repeatedly
{ 
  
  //BASE SERVO CONTROL
  xVal1 = analogRead(xPin1);                   // reads the value of the first x axis potentiometer (value between 0 and 1023) 
  xVal1 = map(xVal1, 0, 1023, 0, 180);         // scales it to use it with the servo (0 to 180 degrees) 
  baseServo.write(xVal1);                     // writes that value to servo driver
  
  //ARM MOTORS CONTROL
  yVal1 = analogRead(yPin1);                   // reads the value of the first y axis potentiometer (value between 0 and 1023) 
  yVal1 = map(yVal1, 0, 1023, 1000, 2000);     // scales it to use it with the PWM motor (pulse length between 1000 and 2000) 
  armMotor1.writeMicroseconds(yVal1);          // writes that value to PWM driver
  y2Val1 = analogRead(yPin1);                                           
  y2Val1 = map(y2Val1, 0, 1023, 2000, 1000);                                          
  armMotor2.writeMicroseconds(y2Val1); 
  
  //ELBOW MOTOR CONTROL
  yVal2 = analogRead(yPin2);                   // reads the value of the second y axis potentiometer (value between 0 and 1023) 
  yVal2 = map(yVal2, 0, 1023, 1000, 2000);     // scales it to use it with the PWM motor (pulse length between 1000 and 2000) 
  elbowMotor.writeMicroseconds(yVal1);          // writes that value to PWM driver
  
  //WRIST SERVO CONTROL
  if (wristVal > 180) {
    wristVal = 180;
  }
    if (wristVal < 0) {
    wristVal = 0;
  }  
  if (digitalRead(wristdownPin) == HIGH){
    wristVal--;
    wristServo.write(wristVal);
    delay(10);
  }  
  if (digitalRead(wristupPin) == HIGH){
    wristVal++;
    wristServo.write(wristVal);
    delay(10);
  }
  
  //CLAW SERVO CONTROL 
  while ((digitalRead(clawbuttonPin) == HIGH)) {
    initially ++;
    if ((clawServo.read() >= 30) && (initially - previous >= 1800)){
      clawServo.write(0);
      previous = initially;
    }
    else if (clawServo.read() <= 30 && (initially - previous >= 1800)){
      clawServo.write(180);
      previous = initially;
    }
  }
} 
