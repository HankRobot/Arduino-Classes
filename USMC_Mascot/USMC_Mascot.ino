#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); //TX 2, RX 3

byte data[5];
int  serInIndx  = 0;    // index of serInString[] in which to insert the next incoming byte
int  serOutIndx = 0;    // index of the outgoing serInString[] array;
int dely = 250;

//Motor Ids
int LeftEn = 6;
int LeftDir = 4;
int RightEn = 5;
int RightDir = 7;

//Line Sensor
#define S0 12
#define S1 11
#define S2 9
#define S3 10
#define sensorOut 13

int LeftSen   = A1;      //Left Sensor
int LeftMSen  = A2;      //Left Middle Sensor
int MidSen    = A3;      //Middle Sensor
int RightMSen = A4;      //Right Middle Sensor
int RightSen  = A5;      //Right Sensor

int IR_Left   = 0;   //OUT1
int IR_MLeft  = 0;   //OUT2
int IR_Middle = 0;   //OUT3
int IR_MRight = 0;   //OUT4
int IR_Right  = 0;   //OUT5

void setup()
{
  // Setting the outputs for line sensor
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  Serial.begin(9600); //Start the serial on computer
  
  mySerial.begin(9600); //Start the serial on bluetooth
  
  //Motor Driver Pin Setup
  pinMode(RightEn, OUTPUT);
  pinMode(RightDir, OUTPUT);
  pinMode(LeftEn, OUTPUT);
  pinMode(LeftDir, OUTPUT);
}

void turnleft(int speed, int time)
{
  digitalWrite(RightDir, HIGH);
  digitalWrite(LeftDir, HIGH);
  analogWrite(RightEn, speed);   //PWM Speed Control
  analogWrite(LeftEn, speed);   //PWM Speed Control
  delay(time);
}

void turnright(int speed, int time)
{
  digitalWrite(RightDir, LOW);
  digitalWrite(LeftDir, LOW);
  analogWrite(RightEn, speed);   //PWM Speed Control
  analogWrite(LeftEn, speed);   //PWM Speed Control
  delay(time);
}

void moveforward(int speed, int time)
{
  digitalWrite(RightDir, LOW);
  digitalWrite(LeftDir, HIGH);
  analogWrite(RightEn, speed);   //PWM Speed Control
  analogWrite(LeftEn, speed+30);   //PWM Speed Control
  delay(time);
}

void movebackward(int speed, int time)
{
  digitalWrite(RightDir, HIGH);
  digitalWrite(LeftDir, LOW);
  analogWrite(RightEn, speed);   //PWM Speed Control
  analogWrite(LeftEn, speed);   //PWM Speed Control
  delay(time);
}

void stop_motion(int time)
{
  analogWrite(RightEn, 0);   //PWM Speed Control
  analogWrite(LeftEn, 0);   //PWM Speed Control
  delay(time);
}

void readSensor ()
{
  IR_Left   = digitalRead(LeftSen);      //OUT1
  IR_MLeft  = digitalRead(LeftMSen);     //OUT2
  IR_Middle = digitalRead(MidSen);       //OUT3
  IR_MRight = digitalRead(RightMSen);    //OUT4
  IR_Right  = digitalRead(RightSen);     //OUT5

//  Serial.print("SL = ");
//  Serial.print(IR_Left );
//  Serial.print("\t");
//  Serial.print("SML = ");
//  Serial.print(IR_MLeft);
//  Serial.print("\t");
//  Serial.print("SM = ");
//  Serial.print(IR_Middle);
//  Serial.print("\t");
//  Serial.print("SMR = ");
//  Serial.print(IR_MRight);
//  Serial.print("\t");
//  Serial.print("SR = ");
//  Serial.print(IR_Right);
//
//  Serial.println();
}

void followline()
{
  if ((digitalRead(LeftSen) == 0) && (digitalRead(LeftMSen) == 0) && (digitalRead(MidSen) == 1) && (digitalRead(RightMSen) == 0) && (digitalRead(RightSen) == 0))
  {
    //move forward
    digitalWrite(RightDir, LOW);
    digitalWrite(LeftDir, HIGH);
    analogWrite(RightEn,85);   //PWM Speed Control
    analogWrite(LeftEn, 75);   //PWM Speed Control
  }

  else if ((digitalRead(LeftSen) == 0) && (digitalRead(LeftMSen) == 1) && (digitalRead(MidSen) == 1) && (digitalRead(RightMSen) == 1) && (digitalRead(RightSen) == 0))
  {
    // go forward
    digitalWrite(RightDir, LOW);
    digitalWrite(LeftDir, HIGH);
    analogWrite(RightEn,85);    //PWM Speed Control
    analogWrite(LeftEn, 75);   //PWM Speed Control
  }

  /////////////////////////////////////////////////////////////////////////turn right begins here///////////////////////////////////////////////////////////////////
  
  else if ((digitalRead(LeftSen) == 0) && (digitalRead(LeftMSen) == 0) && (digitalRead(MidSen) == 1) && (digitalRead(RightMSen) == 1) && (digitalRead(RightSen) == 0))
  {
    // turn right
    digitalWrite(RightDir, LOW);
    digitalWrite(LeftDir, HIGH);
    analogWrite(RightEn,52);    //PWM Speed Control
    analogWrite(LeftEn, 97);   //PWM Speed Control
  }

  else if ((digitalRead(LeftSen) == 0) && (digitalRead(LeftMSen) == 0) && (digitalRead(MidSen) == 1) && (digitalRead(RightMSen) == 1) && (digitalRead(RightSen) == 1))
  {
    // turn right even more
    digitalWrite(RightDir, LOW);
    digitalWrite(LeftDir, HIGH);
    analogWrite(RightEn,5);   //PWM Speed Control
    analogWrite(LeftEn, 95);   //PWM Speed Control
  }
  
  else if ((digitalRead(LeftSen) == 0) && (digitalRead(LeftMSen) == 0) && (digitalRead(MidSen) == 0) && (digitalRead(RightMSen) == 1) && (digitalRead(RightSen) == 1))
  {
    // turn right even more
    digitalWrite(RightDir, LOW);
    digitalWrite(LeftDir, HIGH);
    analogWrite(RightEn,0);    //PWM Speed Control
    analogWrite(LeftEn, 105);   //PWM Speed Control
  }
  
  else if ((digitalRead(LeftSen) == 0) && (digitalRead(LeftMSen) == 0) && (digitalRead(MidSen) == 0) && (digitalRead(RightMSen) == 1) && (digitalRead(RightSen) == 0))
  {
    // max turn right
  digitalWrite(RightDir, LOW);
  digitalWrite(LeftDir, HIGH);
  analogWrite(RightEn, 0);   //PWM Speed Control
  analogWrite(LeftEn, 105);   //PWM Speed Control
  }
  
  else if ((digitalRead(LeftSen) == 0) && (digitalRead(LeftMSen) == 0) && (digitalRead(MidSen) == 0) && (digitalRead(RightMSen) == 0) && (digitalRead(RightSen) == 1))
  {
    // max turn right
  digitalWrite(RightDir, LOW); 
  digitalWrite(LeftDir, HIGH);
  analogWrite(RightEn, 0);   //PWM Speed Control
  analogWrite(LeftEn, 115);   //PWM Speed Control
  }

  //////////////////////////////////////////////////////////////////////////////////turn left begins here/////////////////////////////////////////////////////////////////////////////////
  
  else if ((digitalRead(LeftSen) == 0) && (digitalRead(LeftMSen) == 1) && (digitalRead(MidSen) == 1) && (digitalRead(RightMSen) == 0) && (digitalRead(RightSen) == 0))
  {
    // turn left
  digitalWrite(RightDir, LOW);
  digitalWrite(LeftDir, HIGH);
  analogWrite(RightEn, 107);   //PWM Speed Control
  analogWrite(LeftEn, 77);   //PWM Speed Control
  }
  
  else if ((digitalRead(LeftSen) == 1) && (digitalRead(LeftMSen) == 1) && (digitalRead(MidSen) == 0) && (digitalRead(RightMSen) == 0) && (digitalRead(RightSen) == 0))
  {
    // turn left
  digitalWrite(RightDir, LOW);
  digitalWrite(LeftDir, HIGH);
  analogWrite(RightEn, 115-10);   //PWM Speed Control
  analogWrite(LeftEn, 50-5);   //PWM Speed Control
  }

  else if ((digitalRead(LeftSen) == 1) && (digitalRead(LeftMSen) == 1) && (digitalRead(MidSen) == 1) && (digitalRead(RightMSen) == 0) && (digitalRead(RightSen) == 0))
  {
    // turn left
  digitalWrite(RightDir, LOW);
  digitalWrite(LeftDir, HIGH);
  analogWrite(RightEn, 115-10);   //PWM Speed Control
  analogWrite(LeftEn, 50-5);   //PWM Speed Control
  }

  else if ((digitalRead(LeftSen) == 0) && (digitalRead(LeftMSen) == 1) && (digitalRead(MidSen) == 0) && (digitalRead(RightMSen) == 0) && (digitalRead(RightSen) == 0))
  {
    // max turn left
  digitalWrite(RightDir, LOW);
  digitalWrite(LeftDir, HIGH);
  analogWrite(RightEn, 115);   //PWM Speed Control
  analogWrite(LeftEn, 10);   //PWM Speed Control
  }
  
  else if ((digitalRead(LeftSen) == 1) && (digitalRead(LeftMSen) == 0) && (digitalRead(MidSen) == 0) && (digitalRead(RightMSen) == 0) && (digitalRead(RightSen) == 0))
  {
    // max turn left
  digitalWrite(RightDir, LOW);
  digitalWrite(LeftDir, HIGH);
  analogWrite(RightEn, 125);   //PWM Speed Control
  analogWrite(LeftEn,10);  //PWM Speed Control
  }
  else
  {
    moveforward(70, 0);
  }
}

void readSerialString () 
{
    byte data0;
    byte data1;
    byte data2;
    byte data3;
    byte data4;   
    if(mySerial.available()) 
    { 
      data0 = mySerial.read();
      data1 = mySerial.read();
      data2 = mySerial.read();
      data3 = mySerial.read();
      data4 = mySerial.read();
      if(data0 == 255 && data1 == 255 && data2 != 255 && data3 != 255 && data4 != 255)
        {
          //if all goes well
          data[0] = data0;
          data[1] = data1;
          data[2] = data2;
          data[3] = data3;
          data[4] = data4;
        }
       else if(data0 != 255 && data1 == 255 && data2 == 255 && data3 != 255 && data4 != 255)
       {
        // 255 heading shifts to the left
        data[0] = data1;
        data[1] = data2;
        data[2] = data3;
        data[3] = data4;
        data[4] = mySerial.read();
       }
       else if(data0 != 255 && data1 != 255 && data2 == 255 && data3 == 255 && data4 != 255)
       {
        // 255 heading shifts to the left again
        data[0] = data2;
        data[1] = data3;
        data[2] = data4;
        data[3] = mySerial.read();
        data[4] = mySerial.read();
       }
       else if(data0 != 255 && data1 != 255 && data2 != 255 && data3 == 255 && data4 == 255)
       {
        // 255 heading shifts to the left double
        data[0] = data3;
        data[1] = data4;
        data[2] = mySerial.read();
        data[3] = mySerial.read();
        data[4] = mySerial.read();
       }
       else if(data0 == 255 && data1 != 255 && data2 != 255 && data3 == 255 && data4 != 255)
       {
        // 255 heading shifts to the left double
        data[1] = mySerial.read(); //this reads the leftover 255
        data[2] = mySerial.read();
        data[3] = mySerial.read();
        data[4] = mySerial.read();
       }
       else if(data0 == 255 && data1 == 255 && data2 == 255 && data3 == 255 && data4 == 255)
       {
        data[0] = 255;
        data[1] = 255;
        data[2] = 255;
        data[3] = 255;
        data[4] = 255;
       }
      serInIndx = 5;
    }  
}

void printSerialString() 
{
  if( serInIndx > 0) 
  {
    Serial.print("Arduino memorized that you said: ");     
    for(serOutIndx=0; serOutIndx < serInIndx; serOutIndx++)
    {
      Serial.print(data[serOutIndx]);    //print out the byte at the specified index
    }        
    serOutIndx = 0;
    serInIndx  = 0;
    Serial.println();
  }
}

void loop () 
{
  if(data[2]==120 && data[3]==117 && data[4]==112)
  {
    moveforward(200,0);
  }
  if(data[2]==120 && data[3]==117 && data[4]==114)
  {
    stop_motion(20);
  }
  
  if(data[2]==120 && data[3]==108 && data[4]==112)
  {
    turnleft(150,0);
  }
  if(data[2]==120 && data[3]==108 && data[4]==114)
  {
    stop_motion(0);
  }
  
  if(data[2]==120 && data[3]==114 && data[4]==112)
  {
    turnright(150,0);
  }
  if(data[2]==120 && data[3]==114 && data[4]==114)
  {
    stop_motion(20);
  }
  
  if(data[2]==120 && data[3]==100 && data[4]==112)
  {
    movebackward(200,0);
  }
  if(data[2]==120 && data[3]==100 && data[4]==114)
  {
    stop_motion(20);
  }
  
  if(data[2]==98 && data[3]==53)
  {
    dely = 0;
    readSensor();
    followline();    
  }
  if(data[0]==255 && data[1]==255 && data[2]==255 && data[3]==255 && data[4] ==255)
  {
    dely = 250;
  }
  
  readSerialString();
  delay(dely);
  printSerialString();
  
}
