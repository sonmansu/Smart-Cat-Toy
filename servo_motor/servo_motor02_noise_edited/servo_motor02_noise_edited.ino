//https://www.youtube.com/watch?v=ZsvNVPCetmI&ab_channel=H_World 보고 서보모터 소음잡는 코드로 수정
#include <Servo.h>
Servo myservo; // create servo object to control a servo
int pos = 0; // variable to store the servo position
int powerButton = D12;
int servoAngle = 0;
void setup()
{
  // attaches the servo on pin 10 to the servo object
  Serial.begin(9600);

  pinMode(powerButton, INPUT);
}

void loop()
{
  // sweeps from 0 degrees to 180 degrees
//  if(digitalRead(powerButton) == LOW) {
//    Serial.println(servoAngle);
//    myservo.attach(D11);
//    servoAngle +=5;
//    myservo.write(servoAngle);
//    delay(250);
//    myservo.detach();
//  }
  
  for (pos = 0; pos <= 180; pos += 1) // sweeps from 180 degrees to 0 degrees for(pos = 180; pos>=0; pos-=1)
  {
    Serial.println(pos);
     myservo.attach(D11);
    myservo.write(pos);
    delay(60);
    myservo.detach();
  }
}
