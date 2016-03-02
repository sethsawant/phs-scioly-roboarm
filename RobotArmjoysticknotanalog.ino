#include <Servo.h>

Servo baseServo;//base Servo
Servo armServo;//arm servo
Servo elbowServo;//elbow servo
Servo wristServo;//wrist servo
Servo clawServo;//claw servo

int basePos = 90;//starting position for the base
int armPos = 90;//starting position for the arm
int elbowPos = 90;//starting position for elobow
int wristPos = 90;//starting position for wrist
int clawPos = 90;//starting position for claw

char baseUpKey = 'a';//key for moving the base up
char baseDownKey = 'd';//key for moving the base up
char armUpKey = 'w';//key for mojving the arm up
char armDownKey = 's';//key for moving the arm down
char elbowUpKey = 'i';//key for moving the elbow up
char elbowDownKey = 'k';//key for moving the elbow down
char wristUpKey = 'j';//key for moving the wrist up
char wristDownKey = 'l';//key for moving the wrist down
char clawOpenKey = 'v';//key for opening the claw
char clawCloseKey = 'b';//key for closing the claw

void setup() {
  Serial.begin(9600);//starts serial
  
  baseServo.attach(9);//attaches base to pin 5
  armServo.attach(10);//attaches arm to pin 6
  elbowServo.attach(11);// attaches elbow to pin 7
  wristServo.attach(12);//attaches wrist to pin 8
  clawServo.attach(13);//attaches claw to pin 9

}

void loop() {
  while(Serial.available() > 0){//sees if it is recieving serial input
    int input = Serial.read();//recieves input as ASCII
    if (input == baseUpKey){//if the input is the base up
      Serial.println("base Up");
      baseServo.write(120);
//      basePos++;//base increases
//      baseServo.write(basePos);//writes basePos to base servo
    } else if (input == baseDownKey){//if input is base down
      Serial.println("base down");
        baseServo.write(60);
//      basePos--;//base decreases
//      baseServo.write(basePos); //writes basePos to base servo     
    } else {
        baseServo.write(90);
    }
//    
    if (input == armUpKey && armPos < 180){//if the input is arm up
      Serial.println("arm Up");
      armPos+=3;//arm increases
      armServo.write(armPos);//writes arm pos to arm servo
    }
    if (input == armDownKey && armPos > 0){//if input is armdownkey
    Serial.println("arm down");      
      armPos-=3;//arm decreases
      armServo.write(armPos);//writes arm pos to arm servo      
    }
    if (input == elbowUpKey && elbowPos < 180){//if input is elbow up key
          Serial.println("elbow Up");
      elbowPos += 4;//elbow increases
      elbowServo.write(elbowPos);//writes elbow pos to elbow servo
    }
    if (input == elbowDownKey && elbowPos > 0){//if input is elbow down key
          Serial.println("elbow down");
      elbowPos -= 4;//elbow decreases
      elbowServo.write(elbowPos);//writes elbow pos to elbow servo      
    }
    if (input == wristUpKey && wristPos < 180){//if input is wrist up key
          Serial.println("wrist up");
      wristPos += 5;//wrist increases
      wristServo.write(wristPos);//writes wrist pos to wrist servo
    }
    if (input == wristDownKey && wristPos > 0){//if input is wrist downkey
          Serial.println("wrist down");
      wristPos-= 5;//wrist decreases
      wristServo.write(wristPos);//writes wrist pos to wrist servo      
    }
    if (input == clawOpenKey){//if input is claw open key
          Serial.println("claw open");
      clawServo.write(180);//writes claw to 180
    } 
    if (input == clawCloseKey){//if input is claw close key
      Serial.println("claw close");
      clawServo.write(0);//writes sclaw to 0
    }

    
  }

}
