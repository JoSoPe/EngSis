#include <Wire.h>
#include <ADXL345.h> /*https://github.com/sparkfun/SparkFun_ADXL345_Arduino_Library/blob/master/src/SparkFun_ADXL345.h */
#include <stdio.h>
#include <Timer-2.1.h>/* https://playground.arduino.cc/Code/Timer
https://github.com/JChristensen/Timer   */
#include <avr/io.h>
#include <stdbool.h>

typedef struct {//per guardar les dades
  int x;//x value
  int y;
  int z;
  bool moviment = false;  //true si havia variat
  char estat = 'E0';
  char eix;
} lect;

void setup() {// put your setup code here, to run once:
  Serial.begin(9600); 
  adxl.powerOn();   
  start = 1;
  mark_up = 60;
  lect a,b;
}

lect read(lect a){ //llegir el sensor
  adxl.readXYZ(&a.x, &a.y, &a.z)
    return a;
    }

bool movx(lect a,lect b,int c){
  if ((a.x != b.x+c) or (a.x != b.x-c )){
    //moviment brus en eix X
    return true;
  }
  else
    return false;
}
bool movy(lect a,lect b,int c){
  if ((a.y != b.y+c) or (a.y != b.y-c )){
    //moviment brus en eix y
    return true;
  }
  else
    return false;
}
bool movz(lect a,lect b,int c){
  if ((a.z != b.z+c) or (a.z != b.z-c )){
    //moviment brus en eix z
    return true;
  }
  else
    return false;
}

lect moviment(lect a,lect b,int c,char eix){//comparem si ha variat algun dels tres eixos  i ho guardem com a bool a l'actual
  bool a,b,c;
  switch (eix){
  case eix == x:
    a = movx(a,b,c);
  case eix == y:
    b = movy(a,b,c);
  case eix == z:
    c = movz(a,b,c);
  case eix ==yz:
    b = movy(a,b,c); 
    c = movz(a,b,c);
  }

  if (((a == true) or (b == true)) or (c == true)){
    a.moviment = true;
  }
  return a
}


lect state_machine(lect a){ // maquina de estats
  switch (a.estat){
  case a.estat == 'E0':
    b=a;
    a=read(a);
    
    
  }
    
}

void E0(){  //accións a fer en E0 
  
  
  return state;
}

void main(){
  lect d;
  d.moviment=false;
  last x;
  last y;
  last z;
  adxl.readXYZ(&x.a, &z.a, &z.a)
  
  State state = (E0);
  
}


void loop() {  // put your main code here, to run repeatedly:
  state = (State)(*state)(); //cada estat retorna el seu valor
  
}
