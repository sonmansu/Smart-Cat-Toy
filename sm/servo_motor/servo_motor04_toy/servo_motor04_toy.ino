//https://www.youtube.com/watch?v=ZsvNVPCetmI&ab_channel=H_World 보고 서보모터 소음잡는 코드로 수정
#include <Servo.h>
Servo myservo; // create servo object to control a servo
int pos = 0; // variable to store the servo position

int servoAngle = 0;
void setup()
{
  // attaches the servo on pin 10 to the servo object
  Serial.begin(9600);
  myservo.attach(2);
}

void loop()
{
//위에거랑 소음이 비슷한거같아서 그냥 이거 쓰기로..
  if (Serial.available()) {
    if (Serial.read() == 'd') {
      Serial.println('d');
      myservo.write(130); //문열음
      delay(3000); //3초 기다림
      myservo.write(0);   //문닫음
    }
  }
}
