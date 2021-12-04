/* 서보모터 떨림증상 잡기 위한 코드
 *  https://rasino.tistory.com/250 걍 디테치어테치 하는게 최선인듯 
 */
#include <Servo.h>
Servo myservo; // create servo object to control a servo
int pos = 0; // variable to store the servo position

int SERVO_TOY_PIN = D15; //(주황선) //원래 D8이었는데 자꾸 저절로 HIGH가 되는듯 9도
//int SERVO_DOOR_PIN = D12;// (파랑선)
Servo servoDoor;
Servo servoToy;
int currVar = 0;
int preVar = 0;
void setup()
{
  Serial.begin(9600);
  Serial.println("hi ");

  // attaches the servo on pin 10 to the servo object
//  servoToy.attach(SERVO_TOY_PIN);
//  servoDoor.attach(SERVO_DOOR_PIN);
}

void loop()
{
  if (Serial.available()) {
    if (Serial.read() == 'd') {
      Serial.println('d');
      servoToy.attach(SERVO_TOY_PIN);
      servoToy.write(130); //문열음
      delay(3000); //3초 기다림
      servoToy.write(0);   //문닫음
      delay(60);
      servoToy.detach(); //이래야되네..
    }
  }
  
  // sweeps from 0 degrees to 180 degrees
//  for (pos = 0; pos <= 180; pos += 1) // sweeps from 180 degrees to 0 degrees for(pos = 180; pos>=0; pos-=1)
//  {
//    servoToy.write(pos);
//    delay(15);
//  }
//
//  for (pos = 0; pos <= 180; pos += 1) // sweeps from 180 degrees to 0 degrees for(pos = 180; pos>=0; pos-=1)
//  {
//    servoDoor.write(pos);
//    delay(15);
//  }
}
