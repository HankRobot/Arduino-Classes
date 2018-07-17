#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978

#define melodyPin 8
#include <CapacitiveSensor.h>

CapacitiveSensor cs_3_2 = CapacitiveSensor(3,2); // 10 megohm resistor between pins 2 & 3, pin 2 is sensor pin, add wire, foil
CapacitiveSensor cs_5_4 = CapacitiveSensor(5,4); // 10 megohm resistor between pins 4 & 5, pin 4 is sensor pin, add wire, foil
CapacitiveSensor cs_7_6 = CapacitiveSensor(7,6); // 10 megohm resistor between pins 6 & 7, pin 6 is sensor pin, add wire, foil

CapacitiveSensor cs_11_10 = CapacitiveSensor(11,10); // 10 megohm resistor between pins 10 & 11, pin 10 is sensor pin, add wire, foil
CapacitiveSensor cs_13_12 = CapacitiveSensor(13,12); // 10 megohm resistor between pins 12 & 13, pin 12 is sensor pin, add wire, foil

void setup(){
cs_3_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
cs_5_4.set_CS_AutocaL_Millis(0xFFFFFFFF);
cs_7_6.set_CS_AutocaL_Millis(0xFFFFFFFF);
cs_11_10.set_CS_AutocaL_Millis(0xFFFFFFFF);
cs_13_12.set_CS_AutocaL_Millis(0xFFFFFFFF);

Serial.begin(9600);
pinMode(8, OUTPUT);

}

void loop(){
  long start = millis();

  long total1 = cs_3_2.capacitiveSensor(30);
  long total2 = cs_5_4.capacitiveSensor(30);
  long total3 = cs_7_6.capacitiveSensor(30);
  long total4 = cs_11_10.capacitiveSensor(30);
  long total5 = cs_13_12.capacitiveSensor(30);
  
  Serial.print(total1);
  Serial.print("\t");
  Serial.print(total2);
  Serial.print("\t");
  Serial.print(total3);
  Serial.print("\t");
  Serial.print(total4);
  Serial.print("\t");
  Serial.print(total5);
  Serial.println("");
  delay(10); // arbitrary delay to limit data to serial port

  if (total1>10000){
    tone(melodyPin,NOTE_C4,20);
  }

  if (total2>10000){
    tone(melodyPin,NOTE_D4,20);
  }

  if (total3>15000){
    tone(melodyPin,NOTE_E4,20);
  }

  if (total4>10000){
    tone(melodyPin,NOTE_F4,20);
  }

  if (total5>10000){
   tone(melodyPin,NOTE_G4,20);
  }
}
