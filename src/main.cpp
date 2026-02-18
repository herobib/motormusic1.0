#include <Arduino.h>
#include "motor.cpp"

Nema17 motors[]={
  Nema17(13,12,11),
  Nema17(10,9,8),
  Nema17(7,6,5),
  Nema17(4,3,2)
};

int motorInd=0;
int motorFreq=-1;
long motortime=-1;
void setup() {
  Serial.begin(115200);
}

#pragma region hand Input
// void SetTask(){
//   Serial.println("Enter motor index:");
//   while (Serial.available() == 0) {}
//   motorInd = Serial.parseInt();
//   Serial.print(motorInd);
//   Serial.println("Enter frequency:");
//   while (Serial.available() == 0) {}
//   motorFreq = Serial.parseInt();
//   Serial.print(motorFreq);
//   Serial.println("Enter runtime:");
//   while (Serial.available() == 0) {}
//   motortime = Serial.parseInt();
//   Serial.print(motortime);
//   if(motors[motorInd].getFree()){
//     motors[motorInd].setNote(motorFreq, motortime);
//   }
// }
#pragma endregion

int FindIndex(){
  for(int i=0; i<4; i++){
    if(motors[i].getFree()){
      return i;
    }
  }
  return -1;
}
String input = "";

void readSerial() {
    while (Serial.available()) {
        char c = Serial.read();

        if (c == '\n') {
            input.trim();
            Serial.println(input);
            char type;
            int freq;
            long duration;          
            int count = sscanf(input.c_str(), " %c %d %ld", &type, &freq, &duration);
            if(type=='M' && count==3){              
              int index= FindIndex();
              if(index!=-1){
                motors[index].setNote(freq, duration);      
              }        
            }
            input = "";
        } else {
            input += c;
        }
    }
}

void loop() {
  for(int i=0; i<4; i++){
    motors[i].playNote();
  }
  readSerial();
}
