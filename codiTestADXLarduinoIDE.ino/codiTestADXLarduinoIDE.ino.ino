#include <Wire.h>
#include <ADXL345.h> /*https://github.com/sparkfun/SparkFun_ADXL345_Arduino_Library/blob/master/src/SparkFun_ADXL345.h */
#include <stdio.h>
#include <Timer.h>
ADXL345 adxl; //variable adxl is an instance of the ADXL345 library


typedef struct{//per guardar les dades
  int x;//x value
  int y;
  int z;
} lect;
/*-------------------*/    
  int x,y,z;
  int start;
  int mark_up,mark_upx,mark_upyz;
  bool movment;
  lect a,b;
  Timer t;
/*-------------------*/    
void setup(){
  Serial.begin(9600);
  adxl.powerOn();
  start = 1;
  mark_upx = 300;
  mark_upyz = 145;
  movment = false;
}

lect sensordata(lect a){
  adxl.readXYZ(&a.x, &a.y, &a.z); 
  return a;
}
  
void toprint(lect a){
  Serial.print(a.x);
  Serial.print(" , ");
  Serial.print(a.y);
  Serial.print(" , ");
  Serial.println(a.z);
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
void test(){
  Serial.print("dintre");
  Serial.print(" , ");
}

void loop(){
  void(*foo)(void);
  foo = &test;
  t.every(25,test);
}

