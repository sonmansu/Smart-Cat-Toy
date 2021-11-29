//최종사용코드
#include <Servo.h>
Servo myservo; // create servo object to control a servo

int servoAngle = 0;
void setup()
{
  // attaches the servo on pin 10 to the servo object
  Serial.begin(9600);
  myservo.attach(2);
  Serial.println("hi");
}
void loop()
{
  //위에거랑 소음이 비슷한거같아서 그냥 이거 쓰기로..
  if (Serial.available()) {
    char c = Serial.read();
    Serial.println(c);
    if (c == '3') runServo(300);
    else if (c == '4') runServo(400);
    else if (c == '5') runServo(500);
    else if (c == '6') runServo(600);
    else if (c == '7') runServo(700);
    else if (c == '8') runServo(800);

    else if (c == 'e') runServo1(300);
    else if (c == 'r') runServo1(400);

    else if (c == 'p') runRandomAngle(); //쓰레기임 
    else if (c == 'l') runRandomDelay();

  }
}
void runServo(int speed) { //delay는 300이상 이어야..
  while(true) {
    if (Serial.available()) break; //end
    myservo.write(180); //최대각도
    delay(speed);
    myservo.write(0); //최소각도
    delay(speed);
  }
}
void runServo1(int speed) { //소음 감소 코든데 똑같은듯 걍 위에꺼 쓰자..
  while(true) {
    myservo.attach(2);
    if (Serial.available()) break; //end
    myservo.write(180); //최대각도
    delay(speed);
    myservo.write(0); //최소각도
    delay(speed);
    myservo.detach();
  }
}
void runRandomAngle() { //영 노잼 
  while(true) {
    if (Serial.available()) break; 
    int angle = random(0, 90);
    myservo.write(angle);
    delay(300);
  }
}
void runRandomDelay() { // 
  int delay_time;
  while(true) {
    if (Serial.available()) break; 
    delay_time = random(300, 900);
    myservo.write(0);
    delay(delay_time);
    myservo.write(180);
    delay_time = random(300, 900);
    delay(delay_time);
  }
}
