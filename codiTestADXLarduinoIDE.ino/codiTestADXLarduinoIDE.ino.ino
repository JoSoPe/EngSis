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
const int led = 13; 
int LEDState;
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

/*-------------------*/    
void setup(){
  Serial.begin(9600);
  adxl.powerOn();
/*--globalvariable_settings--*/
  LEDState = LOW;
  pinMode(led,OUTPUT);
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
  interrupts();
}

/*-------------------*/    
lect sensordata(lect value){
  interrupts();
  adxl.readXYZ(&value.x, &value.y, &value.z); 
  noInterrupts();
  //toprint(value);
  return value;
}

/*-------------------*/ 


  
void toprint(lect a){
  Serial.print(a.x);
  Serial.print("\n");
  /*
  Serial.print(" , ");
  Serial.print(a.y);
  Serial.print(" , ");
  Serial.println(a.z);
  */
  //Serial.print("correcte");
}

bool moviment_brusc(lect a,char eix){
  bool moviment;
  switch (eix){
    case 'x':
      if ((a.x >= mark_upx) or (a.x <= - mark_upx)){
        moviment = true;
      }
      else{
        moviment = false;
      }
    case 'y':
      if ((a.y >= mark_upyz) or (a.y <= - mark_upyz)){
        moviment = true;
      }
      else{
        moviment = false;
      }
    default:
      if ((a.z >= mark_upyz) or (a.z <= - mark_upyz)){
        moviment = true;
      }
      else{
        moviment = false;
      }
  }
  return moviment;
}

/*void loop(){
  
	adxl.readXYZ(&x, &y, &z); //read the accelerometer values and store them in variables  x,y,z
	// Output x,y,z values 
	//Serial.print("values : ");
	toprint(x,y,z);
	//Serial.println(start); 
  if (start = 1) {
    delay (250); 
    adxl.readXYZ(&x2, &y2, &z2);
    start = 0;
  }
  if (start == 0){
    //Serial.print("dintre");
    //Serial.println(x-x2);
    if ((x >= x2 + mark_up) or (x <= x2 - mark_up)){
      if ((y >= y2 + mark_up) or (y <= y2 - mark_up)){
        movment = true;
        //Serial.println("movment = true;");  
      } //fi Y   
      else{
        movment = false;
      } //else Y
    } //fi X
    else{
      movment = false;
    } //else X
  } // start = 0
	delay (50); 
  adxl.readXYZ(&x2, &y2, &z2);
  //Serial.print("values2: ");
  toprint(x2,y2,z2);
  //Serial.println(start);
  
  if ((x >= x2 + mark_up) or (x <= x2 - mark_up)){
    if ((y >= y2 + mark_up) or (y <= y2 - mark_up)){
      movment = true;
      //Serial.println("movment = true;");  
      } //fi Y   
    else{
      movment = false;
    } //else Y
  } //fi X
  else{
    movment = false;
  } //else X
  delay(50); 
}
*/
void intern(lect a){
  a=sensordata(a);
  toprint(a);
}
void timerIsr(){
  //noInterrupts();
  //Serial.print("dintre");
  //Serial.print(" , ");
  intern(b);
  //interrupts();
}

void loop(){
  //t.every(1,test,0);
  delay(10);
  intern(a);  
  moviment_brusc(a,'x');
  }

