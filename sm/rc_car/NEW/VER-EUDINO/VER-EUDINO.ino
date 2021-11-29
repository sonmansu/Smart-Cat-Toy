#include <Servo.h>     //서보모터 제어함수용 헤더

//#define MOTOR_B_b D9     //모터B의 -출력핀은 6번핀입니다
#define LEFT_MOTOR_PIN1   D6                  // 왼쪽모터의 +출력핀 주황
#define LEFT_MOTOR_PIN2   D7                  // 왼쪽모터의 -출력핀 노랑
#define RIGHT_MOTOR_PIN1  D8                  // 오른쪽모터의 +출력핀 초록
#define RIGHT_MOTOR_PIN2  D9                  // 왼쪽모터의 -출력핀 파랑

int MOTOR_SPEED = 1000; //모터의 기준속력입니다(0~255) 기준속력 변경시 제자리 회전 시간 변경이 필요합니다.
//#define ULTRASENS_T D10  //초음파센서 트리거 출력핀은 13번핀입니다.
//#define ULTRASENS_E D11  //초음파센서 에코 입력핀은 12번핀입니다.
//#define SERVO_PIN 9     //서보모터 제어용 출력핀은 9번핀 입니다.

int trigPin = D12;
int echoPin = D13;
long duration, distance;

void setup()
{
  Serial.begin(9600); //시리얼 통신 초기화

  pinMode(RIGHT_MOTOR_PIN1, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN2, OUTPUT);
  pinMode(LEFT_MOTOR_PIN1, OUTPUT);
  pinMode(LEFT_MOTOR_PIN2, OUTPUT);

  pinMode(echoPin, INPUT);   // echoPin 입력
  pinMode(trigPin, OUTPUT);  // trigPin 출력

  //  servo_drive(90);              //서보모터 초기 각도를 90도로 설정합니다.

  Serial.println("Hello!"); //터미널 작동 확인용 문자열
  delay(1000);        //1초간 작동대기
}

void loop()
{
  Forward(MOTOR_SPEED);
  delay(100);
  Obstacle_Check();
}
///////////장애물 확인 및 회피 방향 결정///////////
void Obstacle_Check() {
  int val = random(2);
  Distance_Measurement();

  Serial.println(distance);

  while (distance < 20) {
    if (distance < 18) {
      Backward(MOTOR_SPEED);
      delay(250);
      Stop();
      delay(50);
      Distance_Measurement();
    }
    else {
      if (val == 0) {
        Right(MOTOR_SPEED);
        delay(300);
      }
      else if (val == 1) {
        Left(MOTOR_SPEED);
        delay(300);
      }
      Distance_Measurement();
    }
  }
}
void Forward(int MOTOR_SPEED) {
  Serial.println("Go forward...");
  digitalWrite(LEFT_MOTOR_PIN1, LOW);
  analogWrite(LEFT_MOTOR_PIN2, MOTOR_SPEED);
  analogWrite(RIGHT_MOTOR_PIN1, MOTOR_SPEED);
  digitalWrite(RIGHT_MOTOR_PIN2, LOW);
}
void Backward(int MOTOR_SPEED) {
    Serial.println("Go backward...");

  analogWrite(LEFT_MOTOR_PIN1, MOTOR_SPEED);
  digitalWrite(LEFT_MOTOR_PIN2, LOW);
  digitalWrite(RIGHT_MOTOR_PIN1, LOW);
  analogWrite(RIGHT_MOTOR_PIN2, MOTOR_SPEED);
}
void Left(int MOTOR_SPEED) {
    Serial.println("Turn left...");

  analogWrite(LEFT_MOTOR_PIN1, MOTOR_SPEED);
  digitalWrite(LEFT_MOTOR_PIN2, LOW);
  analogWrite(RIGHT_MOTOR_PIN1, MOTOR_SPEED);
  digitalWrite(RIGHT_MOTOR_PIN2, LOW);
}
void Right(int MOTOR_SPEED) {
    Serial.println("Turn right...");

  digitalWrite(LEFT_MOTOR_PIN1, LOW);
  analogWrite(LEFT_MOTOR_PIN2, MOTOR_SPEED);
  digitalWrite(RIGHT_MOTOR_PIN1, LOW);
  analogWrite(RIGHT_MOTOR_PIN2, MOTOR_SPEED);
}
void Stop() {
    Serial.println("Stopped");

  digitalWrite(LEFT_MOTOR_PIN1, LOW);
  digitalWrite(LEFT_MOTOR_PIN2, LOW);
  digitalWrite(RIGHT_MOTOR_PIN1, LOW);
  digitalWrite(RIGHT_MOTOR_PIN2, LOW);
}

long Distance_Measurement() {
  digitalWrite(trigPin, HIGH);  // trigPin에서 초음파 발생(echoPin도 HIGH)
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);    // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  distance = ((float)(340 * duration) / 1000) / 2;
  Serial.print((String) "Distance_Measurement()함수" + distance);
  Serial.println("mm");
  distance = (float)distance/10;
  Serial.print((String) "Distance_Measurement()함수" + distance);
  Serial.println("cm");
  delay(500);
  return distance;
}
