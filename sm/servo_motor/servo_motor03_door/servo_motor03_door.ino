//https://www.youtube.com/watch?v=ZsvNVPCetmI&ab_channel=H_World 보고 서보모터 소음잡는 코드로 수정
#include <Servo.h>
Servo myservo; // create servo object to control a servo
int pos = 0; // variable to store the servo position
//int powerButton = D12;

int servoAngle = 0;
void setup()
{
  // attaches the servo on pin 10 to the servo object
  Serial.begin(9600);
  myservo.attach(D11);
//  myservo.attach(5);//node mcu에서 d1
}

void loop()
{
//뭔가 지지직동작해서 별로임
//  if (Serial.available()) {
//    if (Serial.read() == 'd') {
//      Serial.println('d');
//      myservo.attach(D11);
//      myservo.write(130); //문열음
//      delay(2000); //3초 기다림
//      myservo.detach();
//      delay(1000);
//      myservo.attach(D11);
//      myservo.write(0);   //문닫음
//      delay(150);
//      myservo.detach();
//    }
//  }
//if (Serial.available()) {
//    if (Serial.read() == 'd') {
//      Serial.println('d');
//      myservo.attach(D11);
//      myservo.write(130); //문열음
//      delay(2000); //3초 기다림
//      myservo.write(0);   //문닫음
//      delay(1000);
//      myservo.detach();
//    }
//  }
//위에거랑 소음이 비슷한거같아서 그냥 이거 쓰기로..
  if (Serial.available()) {
    if (Serial.read() == 'd') {
      Serial.println('d');
      myservo.write(130); //문열음
      delay(3000); //3초 기다림
      myservo.write(0);   //문닫음
    }
  }
  
//  for (pos = 0; pos <= 180; pos += 1) // sweeps from 180 degrees to 0 degrees for(pos = 180; pos>=0; pos-=1)
//  {
//    Serial.println(pos);
//     myservo.attach(D11);
//    myservo.write(pos);
//    delay(60);
//    myservo.detach();
//  }

  // sweeps from 0 degrees to 180 degrees
//  if(digitalRead(powerButton) == LOW) {
//    Serial.println(servoAngle);
//    myservo.attach(D11);
//    servoAngle +=5;
//    myservo.write(servoAngle);
//    delay(250);
//    myservo.detach();
//  }
}
