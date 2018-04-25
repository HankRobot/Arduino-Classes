#include <AFMotor.h>

AF_DCMotor motor1(2);     //defining the left motor at terminal 2
AF_DCMotor motor2(3);     //defining the right motor at terminal 3

void setup() { //delete this

}

void forward(int time_taken,int speed){
  motor1.setSpeed(speed);
  motor2.setSpeed(speed+25); //these are offsets since my robot chasis wheel isnt perfect
  motor1.run(FORWARD);
  motor2.run(FORWARD); 
  delay(time_taken);
}

void backward(int time_taken,int speed){
  motor1.setSpeed(speed);
  motor2.setSpeed(speed+10);    //offsets
  motor2.run(BACKWARD);
  motor1.run(BACKWARD); 
  delay(time_taken);
}

void stop1(int time_taken){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  delay(time_taken);  
}

void turnleft1(int time_taken,int speed){ //turns left at centre between two wheels
  motor1.setSpeed(speed);
  motor2.setSpeed(speed+10);    //offsets
  motor2.run(BACKWARD);
  motor1.run(FORWARD); 
  delay(time_taken);  
}

void turnright1(int time_taken,int speed){ //turns right at centre between two wheels
  motor1.setSpeed(speed);
  motor2.setSpeed(speed+10);    //offsets
  motor2.run(FORWARD);
  motor1.run(BACKWARD); 
  delay(time_taken);  
}

void loop() {
  turnleft1(1000,100); 
  stop1(1000);
  turnright1(1000,100);
  stop1(1000);
}
