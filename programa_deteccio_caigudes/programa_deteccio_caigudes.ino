#include <Wire.h>
#include <Timer.h>
#include <ADXL345.h>
#include <stdio.h>
#include <TimerOne.h>
ADXL345 adxl; //variable adxl is an instance of the ADXL345 library


typedef struct{//to host data
  int x;//x value
  int y;
  int z;
} lect;

/*-------------------*/    
int x,y,z;
int start;
int isrmili, ISRmicro;
int mark_upx = 300;
int mark_upyz = 145;
bool movment,estat = false;
lect a,b,avg;
Timer t;

/*-------------------*/    
void setup(){
  noInterrupts();
  Serial.begin(9600);
  adxl.powerOn();
  isrmili = 500; //10
  ISRmicro = isrmili * 1000;
  start = 0;
  mark_upx = 300;
  mark_upyz = 145;
  movment = false;
  Timer1.initialize(ISRmicro); //top timer counter in microseconds
  Timer1.attachInterrupt( timerIsr ); //timer interruption service routine
  Serial.print("setup");
  Serial.print(" ");
  //attachInterrupt(void *intent(),50000);
  interrupts();
}

/*-------------------*/    
lect sensordata(lect a){
  adxl.readXYZ(&a.x, &a.y, &a.z); 
  /*Serial.print(a.x);
  Serial.print(" , ");
  Serial.print(a.y);
  Serial.print(" , ");
  Serial.println(a.z);*/
  //Serial.print(a.x);
  //return a;
  return a;
}

/*-------------------*/    
void toprint(lect a){
  Serial.print(a.x);
  Serial.print(" , ");
  Serial.print(a.y);
  Serial.print(" , ");
  Serial.println(a.z);
  //Serial.print("ok");
}

/*-------------------*/    
bool sudden(lect a,char axis){
  bool movement;
  switch (axis){
    case 'x':
      if ((a.x >= mark_upx) or (a.x <= - mark_upx)){
        movement = true;
      }
      else{
        movement = false;
      }
    case 'y':
      if ((a.y >= mark_upyz) or (a.y <= - mark_upyz)){
        movement = true;
      }
      else{
        movement = false;
      }
    default:
      if ((a.z >= mark_upyz) or (a.z <= - mark_upyz)){
        movement = true;
      }
      else{
        movement = false;
      }
  }
  return movement;
}

/*-------------------*/    
void intent(void){
  noInterrupts();
  lect c;
  lect d;
  d = sensordata(c);
  c = d;
  toprint(sensordata(a));
  interrupts();  
}

/*-------------------*/    
void timerIsr(){
  a = b;
//  intent();
}

/*-------------------*/    
void loop(){
  noInterrupts();
  intent();
  interrupts();
  //delay(10);
  Serial.print(start);
}     
  
