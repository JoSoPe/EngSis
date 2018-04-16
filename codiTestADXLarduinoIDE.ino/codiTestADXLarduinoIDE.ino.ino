#include <Wire.h>
#include <ADXL345.h> /*https://github.com/sparkfun/SparkFun_ADXL345_Arduino_Library/blob/master/src/SparkFun_ADXL345.h */
#include <stdio.h>

ADXL345 adxl; //variable adxl is an instance of the ADXL345 library
int x2,y2,z2;
int x,y,z; 
int start;
int mark_up; 
bool movment;
  
void setup(){
  Serial.begin(9600);
  adxl.powerOn();
  start = 1;
  mark_up = 10;
  movment = false;
}

void loop(){
  
	adxl.readXYZ(&x, &y, &z); //read the accelerometer values and store them in variables  x,y,z
	// Output x,y,z values 
	Serial.print("values : ");
	Serial.print(x);
	Serial.print(" , ");
	Serial.print(y);
	Serial.print(" , ");
	Serial.println(z);
  delay (250); 
  //Serial.println(start); 
  if (start = 1) {
    start = 0;
  }
  if (start == 0){
    //Serial.print("dintre");
    Serial.println(x-x2);
    if ( (x >= x2 + mark_up) or (x <= x2 - mark_up)  ){
      movment = true;
      Serial.println("movment=true;");  
    }
    else{
      movment = false;
    }
  }
	
 adxl.readXYZ(&x2, &y2, &z2);
  Serial.print("values2: ");
  Serial.print(x2);
  Serial.print(" , ");
  Serial.print(y2);
  Serial.print(" , ");
  Serial.println(z2);
  //Serial.println(start);
  if ( (x = x2) or (x = x2 + mark_up) or (x = x2 - mark_up) ){
      movment = false;
    }
  else{
    movment = true;
    Serial.println("movment=true;");
    }
  delay(250); 
}
