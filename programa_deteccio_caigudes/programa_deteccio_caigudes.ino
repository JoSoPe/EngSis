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
int state = 0;
int isrmili, ISRmicro;
int mark_upx = 300;
int mark_upyz = 145;
bool movment = false;
lect a,b,avg;
Timer t;

/*-------------------*/    
void setup(){
  Serial.begin(9600);
  adxl.powerOn();
  isrmili = 1000; //10
  ISRmicro = isrmili * 1000;
  start = 0;
  mark_upx = 300;
  mark_upyz = 145;
  movment = false;
  noInterrupts();
  Timer1.initialize(ISRmicro); //top timer counter in microseconds
  Timer1.attachInterrupt( timerIsr ); //timer interruption service routine
  Serial.print("0");
  Serial.print(" ");
  interrupts();
}

/*-------------------*/    
lect sensordata(lect a){
  interrupts();
  adxl.readXYZ(&a.x, &a.y, &a.z); 
  noInterrupts();
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
  //Serial.print("2.0");
  lect c;
  lect d;
  d = sensordata(c);
  c = d;
  //toprint(sensordata(a)); 
}

/*-------------------*/    
void timerIsr(){
  Timer1.stop();
  if (state == 5){
    state = 0;
  }
  else {
      state = state + 1;
  }
  Timer1.resume();
}

/*-------------------*/    
void loop(){
  intent();
  Serial.print(state);
  Serial.print("\n");
}     

  
