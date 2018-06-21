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
int get_up_count,get_up;
int x,y,z;
int start;
int fallcheck,doublefallcheck,read_count,fallcheck_isr,doublefallcheck_isr; 
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
  fallcheck = 7000;         // Waiting time (ms) to decide whether its a fall or not.
  fallcheck_isr = fallcheck/isrmili; //Waiting ISR to decide whether its a fall or not
  doublefallcheck_isr = 1000/isrmili; //Ms after fall detected before lookingfor a stand-up-like try /interrupt lenght.
  get_up_count = 0; //cunter of doublefalcheck_isr done
  get_up = 2;           // times to count to doublefallcheck after first one has passed
  mark_upx = 300;         //Top X value to detect a fall
  mark_upyz = 145;        //Top Y & Z valuesto detect a fall when mark_upx is surpassed
  movment = false;
  state = 0;
/*--Timer_configuration--*/  
  noInterrupts();
  Timer1.initialize(ISRmicro);        //top timer counter in microseconds
  Timer1.attachInterrupt( timerIsr ); //timer interruption service routine
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
      if (abs(value.x) > mark_upx){
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
void E0(){
  int a,b;
  a = abs(value.x);
  b = a - 300;
  start = 0;
  if (b >= 0){
    a = 1;
  }
  else{
    a = 0;
  }    
  if (a == 1){
    state = 1;
  }
  else{
    state = 0;
  }
}
/*-------------------*/

void E1(){
  if ((sudden(value,'y')) or (sudden(value,'z'))){
    state = 2;
  }
  else{
    state = 0;
  }
}

/*-------------------*/
void E2(){
  int reset;
  reset = 0;
  if (start >= (fallcheck_isr/2)){
    start = start + 1;
    if (start == fallcheck_isr){
      state = 4;
    }
    if ((sudden(value,'x')) or ((sudden(value,'y')) or (sudden(value,'z')))){
      reset = 1;
      state = 3;
    }

  }
  else{
    start = start + 1;
  }
  if (reset == 1){
    start = 0; 
  }
}  
/*-------------------*/
void E3(){
  Serial.print("fall");
  if (start == doublefallcheck_isr){//inactive time has ended
    //Serial.print("Xeic!!");
    if (get_up_count == get_up){//and of waiting for activity and no activity detected
      state = 4; //fall detected
      start = 0;
      get_up_count = 0;
    }
    else{
      get_up_count = get_up_count + 1; //keep waiting for a try to get_up
      if ((sudden(value,'x')) or (sudden(value,'y')) or (sudden(value,'z'))){
        state = 0;//got up -> false alarm
        Serial.print("False alarm");
      }
    }
  }
  else{
    start = start+1;
  }
}  

/*-------------------*/
void E4(){
  Serial.print("Still on the floor");
}

/*-------------------*/    
void timerIsr(){
  Timer1.stop();
  value = sensordata(value);
  switch (state){    
    case 0:
      //Serial.print("E0");
      E0();
      break;
    
    case 1:
      //Serial.print("E1");
      E1();
      break;
      
    case 2:
      //Serial.print("E2");
      E2();
      break;

    case 3:
      //Serial.print("E3");
      E3();
      break;      

    case 4:
      //Serial.print("\n");
      E4();
      break;
  }       

  Timer1.resume();
}
/*-------------------*/    
void loop(){
}     
