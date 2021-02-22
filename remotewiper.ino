#include <Servo.h>
#include <Mouse.h>

const int PIN_ANALOG_INPUT = 3; //イヤホンの赤をアナログの3に，オレンジをGNDに

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;//サーボの角度,（噴射＋ワイプ）の繰り返し回数,ワイパーの往復回数
unsigned long elapsed_time = 0;


void setup() {
  Serial.begin( 9600 );
    myservo.attach(9);  // サーボの黄色をデジタルの9に，赤を5Vに，黒をGNDに

}

void software_reset() {
  asm volatile ("  jmp 0");  
}



void loop() {
  int i = analogRead( PIN_ANALOG_INPUT );
  delay( 2 );
  int i2 = analogRead( PIN_ANALOG_INPUT );
  delay( 2 );
  int i3 = analogRead( PIN_ANALOG_INPUT );
  delay( 2 );
  int i4 = analogRead( PIN_ANALOG_INPUT );
  delay( 2 );
  int i5 = analogRead( PIN_ANALOG_INPUT );

  int i6 = (i + i2 + i3 + i4 + i5);    //シリアル値の合計，音を出した直後は低くなる
  
  //Serial.print("i1:");//シリアルモニタで見たいときはコメントアウトを外す
  //Serial.println( i );
  //Serial.print("i2:");
  //Serial.println( i2 );
  //Serial.print("i3:");
  //Serial.println( i3 );
  //Serial.print("i4:");
  //Serial.println( i4 );  
  //Serial.print("i5:");
  //Serial.println( i5 );
  //Serial.print("i6:");
  //Serial.println( i6 );

  
  if(i6 < 20){    //i6が20より低いとき
    analogWrite(5, 255);
    delay(15);
    int pos1 = myservo.read();      //初期位置を180に指定
    delay(15);
    
  {
    for (pos = pos1; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
     myservo.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15ms for the servo to reach the position
   }
   
   for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
                         // in steps of 1 degree
     myservo.write(pos);               // tell servo to go to position in variable 'pos'
     delay(15);                        // waits 15ms for the servo to reach the position
  }
  //delay(15);                        // waits 15ms for the servo to reach the position


  }
  }else
  {  
   // analogWrite(5, 0);
    delay( 1 );               //0.1秒ごとに
    }
   
  
  if( 600000UL <= elapsed_time && elapsed_time <= 600001UL ){
    //通電から24時間毎に作動＆リセット
    analogWrite(5, 255);
    delay(15);
    int pos1 = myservo.read();      //初期位置を現在地に指定
    delay(15);
    
   {
    for (pos = pos1; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
     myservo.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15ms for the servo to reach the position
    }
   
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
                         // in steps of 1 degree
     myservo.write(pos);               // tell servo to go to position in variable 'pos'
     delay(15);                        // waits 15ms for the servo to reach the position
    }
   software_reset();                 // COUNTS RESET BY MILLIS
   
  }
  
 }
}
