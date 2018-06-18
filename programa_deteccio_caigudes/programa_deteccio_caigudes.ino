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
int fallcheck,read_count; 
int state;
int isrmili, ISRmicro;
int mark_upx,mark_upyz;
bool movment;
lect value,value2,avg;
Timer t;

/*-------------------*/    
void setup(){
  Serial.begin(9600);
  adxl.powerOn();
/*--globalvariable_settings--*/
  isrmili = 10;           // Period of executing the timerIsr interrupt.
  ISRmicro = isrmili * 1000;
  start = 0;
  fallcheck = 50;         // Waiting time to decide whether its a fall or not.
  read_count = fallcheck/isrmili;
  mark_upx = 300;         //Top X value to detect a fall
  mark_upyz = 145;        //Top Y & Z valuesto detect a fall when mark_upx is surpassed
  movment = false;
  state = 0;
/*--Timer_configuration--*/  
  noInterrupts();
  Timer1.initialize(ISRmicro);        //top timer counter in microseconds
  Timer1.attachInterrupt( timerIsr ); //timer interruption service routine
  Serial.print("0");
  Serial.print(" ");
  interrupts();
}

/*-------------------*/    
lect sensordata(lect value){
  interrupts();
  adxl.readXYZ(&value.x, &value.y, &value.z); 
  noInterrupts();
  return value;
}

/*-------------------*/    
void toprint(lect value){
  Serial.print(value.x);
  Serial.print(" , ");
  Serial.print(value.y);
  Serial.print(" , ");
  Serial.println(value.z);
}

/*-------------------*/    
bool sudden(lect value,char axis){
  bool movement;
  switch (axis){
    case 'x':
      if ((value.x >= mark_upx) or (value.x <= - mark_upx)){
        movement = true;
      }
      else{
        movement = false;
      }
    case 'y':
      if ((value.y >= mark_upyz) or (value.y <= - mark_upyz)){
        movement = true;
      }
      else{
        movement = false;
      }
    default:
      if ((value.z >= mark_upyz) or (value.z <= - mark_upyz)){
        movement = true;
      }
      else{
        movement = false;
      }
  }
  return movement;
}

/*-------------------*/    
void timerIsr(){
  Timer1.stop();
  switch (state){
    
    case 0:
      if (sudden(value,'x')){
        state = 1;
      }
      else{
        state = 0;
      }
      break;
    
    case 1:
      if ((sudden(value,'y')) or (sudden(value,'z'))){
        state = 2;
      }
      else{
        state = 0;
      }
      break;
    
    case 2:
      if (start = fallcheck){
        start = 0;
        state = 3;
      }
      else{
        if ((sudden(value,'x')) or (sudden(value,'y')) or (sudden(value,'z'))){
          start = 0;
          state = 4;
        }
        else{
          start = start+1;
        }
      }
      break;

    case 3:
     if (start = fallcheck){
        start = 0;
        state = 0; //false alarm
      } 
      else{
        if ((sudden(value,'x')) or (sudden(value,'y')) or (sudden(value,'z'))){
          start = 0;
          state = 4;
        }
        else{
          start = start+1;
        }
      }
      break;      

    case 4:
      //fall deteted
      //blink_led
      break;
  }      

  
  

  Timer1.resume();
}

/*-------------------*/    
void loop(){
}     

  
