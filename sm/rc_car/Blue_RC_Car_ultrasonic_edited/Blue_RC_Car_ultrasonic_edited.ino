//이게 그나마 쓸만한 자율주행코드..
#include <Servo.h>     //서보모터 제어함수용 헤더

//우노용 핀매핑
//#define MOTOR_A_a 3     //모터A의 +출력핀은 3번핀입니다
//#define MOTOR_A_b 11    //모터A의 -출력핀은 11번핀입니다
//#define MOTOR_B_a 5     //모터B의 +출력핀은 5번핀입니다
//#define MOTOR_B_b 6     //모터B의 -출력핀은 6번핀입니다
////위모스d1용
//#define MOTOR_A_a D6     //모터A의 +출력핀은 3번핀입니다
//#define MOTOR_A_b D7    //모터A의 -출력핀은 11번핀입니다
//#define MOTOR_B_a D8     //모터B의 +출력핀은 5번핀입니다
//#define MOTOR_B_b D9     //모터B의 -출력핀은 6번핀입니다
#define LEFT_MOTOR_PIN1   D6                  // 왼쪽모터의 +출력핀 주황
#define LEFT_MOTOR_PIN2   D7                  // 왼쪽모터의 -출력핀 노랑
#define RIGHT_MOTOR_PIN1  D8                  // 오른쪽모터의 +출력핀 초록
#define RIGHT_MOTOR_PIN2  D9                  // 왼쪽모터의 -출력핀 파랑

//#define MOTOR_SPEED 1000 //모터의 기준속력입니다(0~255) 기준속력 변경시 제자리 회전 시간 변경이 필요합니다.
//#define ULTRASENS_T D10  //초음파센서 트리거 출력핀은 13번핀입니다.
//#define ULTRASENS_E D11  //초음파센서 에코 입력핀은 12번핀입니다.
//#define SERVO_PIN 9     //서보모터 제어용 출력핀은 9번핀 입니다.
#define TURN90  600     //제자리 90도 회전 Delay
int trigPin = D12;
int echoPin = D13;
//Servo servo;           //서보 제어용 변수 선언

unsigned char m_a_spd = 0, m_b_spd = 0; //모터의 속력을 저장하는 전역변수
boolean m_a_dir = 0, m_b_dir = 0; //모터의 방향을 결정하는 전역변수

void setup()
{
  Serial.begin(9600); //시리얼 통신 초기화

  //모터 제어 핀들을 출력으로 설정합니다.
  //  pinMode(MOTOR_A_a, OUTPUT);
  //  pinMode(MOTOR_A_b, OUTPUT);
  //  pinMode(MOTOR_B_a, OUTPUT);
  //  pinMode(MOTOR_B_b, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN1, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN2, OUTPUT);
  pinMode(LEFT_MOTOR_PIN1, OUTPUT);
  pinMode(LEFT_MOTOR_PIN2, OUTPUT);

  //  servo.attach(SERVO_PIN);      //서보 제어핀 선언

  //  pinMode(ULTRASENS_T, OUTPUT);   //초음파센서 트리거핀을 출력모드로 설정합니다.
  //  pinMode(ULTRASENS_E, INPUT);    //초음파센서 에코핀을 입력모드로 설정합니다.
  //  digitalWrite(ULTRASENS_T, LOW); //초음파센서 트리거핀 LOW로 초기화

  pinMode(echoPin, INPUT);   // echoPin 입력
  pinMode(trigPin, OUTPUT);  // trigPin 출력

  //  servo_drive(90);              //서보모터 초기 각도를 90도로 설정합니다.

  Serial.println("Hello!"); //터미널 작동 확인용 문자열
  delay(1000);        //1초간 작동대기
}

void loop()
{
  dodgewall_val();  //입력된 데이터에 따라 모터에 입력될 변수를 조정하는 함수
  //  motor_drive();  //모터를 구동하는 함수
//  delay(100);
}

void dodgewall_val() //입력된 데이터에 따라 모터에 입력될 변수를 조정하는 함수
{
  long distance = Distance_Measurement();  //전방 거리측정
  Serial.println((String) "dodgewall함수내 distance: " + distance);

  if (distance > 30) //전방 거리가 30cm 초과일때 보통 속도로 전진
  {
    Forward(1000);
  }
  else if (distance > 20) //30>= 전방거리 > 15cm 일때 장애물 회피
  {
    int val = random(2);
    if (val == 0) {
      Right(1000);
      delay(TURN90);
    }
    else if (val == 1) {
      Left(1000);
      delay(TURN90);
    }
    Stop();
    delay(300); //
  } else { //전방거리 15센치 이하일떄 뒤로감
    Backward(1000);
    delay(500);
//    Right(1000);
//    delay(TURN90*2);
    Stop();
    delay(300); //
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


long get_distance() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delay(2);
  digitalWrite(trigPin, HIGH);                        // trigPin에서 초음파 발생(echoPin도 HIGH)
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);                  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  distance = ((float)(340 * duration) / 1000) / 2;
  Serial.print("distance:");                          // 물체와 초음파 센서간 거리를 표시
  Serial.print(distance);
  Serial.println("mm");
  return distance;
}

long Distance_Measurement() {
  long duration, distance;
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
  return distance;
}

//void motor_drive()  //모터를 구동하는 함수
//{
//  if (m_a_dir == 0)
//  {
//    digitalWrite(MOTOR_A_a, LOW);     //모터A+ LOW
//    analogWrite(MOTOR_A_b, m_a_spd);  //모터A-의 속력을 PWM 출력
//  }
//  else
//  {
//    analogWrite(MOTOR_A_a, m_a_spd);  //모터A+의 속력을 PWM 출력
//    digitalWrite(MOTOR_A_b, LOW);     //모터A- LOW
//  }
//  if (m_b_dir == 1)
//  {
//    digitalWrite(MOTOR_B_a, LOW);     //모터B+ LOW
//    analogWrite(MOTOR_B_b, m_b_spd);  //모터B-의 속력을 PWM 출력
//  }
//  else
//  {
//    analogWrite(MOTOR_B_a, m_b_spd);  //모터B+의 속력을 PWM 출력
//    digitalWrite(MOTOR_B_b, LOW);     //모터B- LOW
//  }
//}
//
//void servo_drive(unsigned char deg) //서보모터를 구동하는 함수
//{
//  deg = constrain(deg, 0, 180); //구동범위를 0도에서 180도로 제한
//  servo.write(deg);             //제한된 범위로 서보모터 구동
//}
