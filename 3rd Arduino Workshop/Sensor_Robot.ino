#include <AFMotor.h>

AF_DCMotor motor1(2);     //defining the left motor at terminal 2
AF_DCMotor motor2(3);     //defining the right motor at terminal 3

const int echoPin = A0;
const int trigPin = A1;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void forward(int time_taken,int speed){
  motor1.setSpeed(speed);
  motor2.setSpeed(speed+50); //these are offsets since my robot chasis wheel isnt perfect
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
  motor2.setSpeed(speed+50);    //offsets
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


void loop() 
{
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;    //1/29.1 approx to 0.034 cm/us
  Serial.print(distance);
  Serial.println(" cm");
  if (distance<10)
  {
    forward(20,200);
    stop1(50);
  }
  else
  {
    turnleft1(20,200);
    stop1(200);
  }
}
