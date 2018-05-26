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
int mark_up,mark_upx,mark_upyz;
bool movment;
lect a,b,avg;
Timer t;
mark_upx = 300;
mark_upyz = 145;

/*-------------------*/    
void setup(){
  Serial.begin(9600);
  adxl.powerOn();
  start = 1;
  mark_upx = 300;
  mark_upyz = 145;
  movment = false;
  Timer1.initialize(5000); //top timer counter 1
  Timer1.attachInterrupt( timerIsr ); //timer interruption service routine
}

/*-------------------*/    
lect sensordata(lect a){
  adxl.readXYZ(&a.x, &a.y, &a.z); 
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
  return moviment;
}

/*-------------------*/    
void timerIsr(){
  Timer1.stop();        //stop the counter
  a = sensordata(a);
  toprint(a);
  //el que fem dintre el interrupcio
  Timer1.restart();     //set the clock to zero
}

/*-------------------*/    
void loop(){
  }
