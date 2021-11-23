/* 이 소스는 에듀이노(Eduino)에 의해서 번역, 수정, 작성되었고 소유권 또한 에듀이노의 것입니다.
    소유권자의 허락을 받지 않고 무단으로 수정, 삭제하여 배포할 시 법적인 처벌을 받을 수도 있습니다.

    에듀이노 교육용 2휠 아두이노 스마트카 구동예제
    - 초음파센서를 활용한 스마트카 자율주행-

    초음파 센서로 거리를 감지하여 전방에 장애물이 인식되면, 좌우로 회피하여
    자율주행이 가능한 소스입니다.
    방향은 Random() 함수를 이용해 무작위로 선정됩니다.

*/
//WEMOS D1 PIN MAPPING
#define LEFT_MOTOR_PIN1   D6                  // 왼쪽모터의 +출력핀 주황
#define LEFT_MOTOR_PIN2   D7                  // 왼쪽모터의 -출력핀 노랑
#define RIGHT_MOTOR_PIN1  D8                   // 오른쪽모터의 +출력핀 초록
#define RIGHT_MOTOR_PIN2  D9                  // 왼쪽모터의 -출력핀 파랑
#define MOTOR_SPEED 900 //모터의 기준속력입니다(0~255)

int i;

//초음파센서 출력핀(trig)과 입력핀(echo), 변수, 함수 선언//
int TrigPin = D12;
int EchoPin = D13;
long duration, distance;

void Obstacle_Check();
void Distance_Measurement();
void Forward();
void Backward();
void Right();
void Left();
void Stop();

void setup() {
  Serial.begin(9600);              // PC와의 시리얼 통신속도
  Serial.println("Eduino Smart Car Start!");

  pinMode(EchoPin, INPUT);   // EchoPin 입력
  pinMode(TrigPin, OUTPUT);  // TrigPin 출력

//  motor_L.setSpeed(175);              // 왼쪽 모터의 속도
//  motor_L.run(RELEASE);
//  motor_R.setSpeed(255);              // 오른쪽 모터의 속도
//  motor_R.run(RELEASE);
}

void loop() {
  Forward();
  delay(100);
  Obstacle_Check();
}

///////////장애물 확인 및 회피 방향 결정///////////
void Obstacle_Check() {
  int val = random(2);
  Distance_Measurement();

  Serial.println(distance);

  while (distance < 200) {
    if (distance < 180) {
      Serial.println(distance);
      Backward();
      delay(250);
      Stop();
      delay(50);
      Distance_Measurement();
    }
    else {
      if (val == 0) {
        Right();
        delay(400);
      }
      else if (val == 1) {
        Left();
        delay(400);
      }
      Distance_Measurement();
    }
  }
}


////////거리감지///////////
void Distance_Measurement() {
  digitalWrite(TrigPin, LOW);
  delay(2);
  digitalWrite(TrigPin, HIGH);  // trigPin에서 초음파 발생(echoPin도 HIGH)
  delayMicroseconds(10);
  digitalWrite(TrigPin, LOW);
  duration = pulseIn(EchoPin, HIGH);    // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  distance = ((float)(340 * duration) / 1000) / 2;
  delay(5);
}
#define MAX_SPEED 900 //원랜 200
#define MAX_SPPED_TURN 700 //원랜 180

///////////모터 제어 함수////////////
void Forward() {
  Serial.println("Forward()");
  digitalWrite(LEFT_MOTOR_PIN1, LOW);
  digitalWrite(RIGHT_MOTOR_PIN2, LOW);
  for (i = 0; i < MAX_SPEED; i = i + 20) {
      analogWrite(LEFT_MOTOR_PIN2, i);
      analogWrite(RIGHT_MOTOR_PIN1, i);
    delay(2);
  }
 
  for (i = MAX_SPEED; i < 0; i = i - 20) {
      analogWrite(LEFT_MOTOR_PIN2, i);
      analogWrite(RIGHT_MOTOR_PIN1, i);
    delay(2);
  }
}

void Backward() {
    Serial.println("Backward()");

      digitalWrite(LEFT_MOTOR_PIN2, LOW);
      digitalWrite(RIGHT_MOTOR_PIN1, LOW);

  for (i = 0; i < MAX_SPEED; i = i + 20) {
      analogWrite(LEFT_MOTOR_PIN1, i);
      analogWrite(RIGHT_MOTOR_PIN2, i);
    delay(2);
  }
  for (i = MAX_SPEED; i < 0; i = i - 20) {
      analogWrite(LEFT_MOTOR_PIN1, i);
      analogWrite(RIGHT_MOTOR_PIN2, i);
    delay(2);
  }
}

void Right() {
  Serial.println("Right()");
  digitalWrite(LEFT_MOTOR_PIN1, LOW);
  digitalWrite(RIGHT_MOTOR_PIN1, LOW);
  for (i = 0; i < MAX_SPPED_TURN; i = i + 20) {
    //j = i*1.3;     if(j >= 200) j = 200;
      analogWrite(LEFT_MOTOR_PIN2, i);
      analogWrite(RIGHT_MOTOR_PIN2, i);

    delay(2);
  }
  for (i = MAX_SPPED_TURN; i < 0; i = i - 20) {
      analogWrite(LEFT_MOTOR_PIN2, i);
      analogWrite(RIGHT_MOTOR_PIN2, i);
      delay(2);
  }
}

void Left() {
  Serial.println("Left()");

  digitalWrite(LEFT_MOTOR_PIN2, LOW); 
  digitalWrite(RIGHT_MOTOR_PIN2, LOW); 
  
  for (i = 0; i < MAX_SPPED_TURN; i = i + 20) {
      //j = i*1.3;     if(j >= 200) j = 200;
    analogWrite(LEFT_MOTOR_PIN1, i);
    analogWrite(RIGHT_MOTOR_PIN1, i);
    delay(2);
  }
  
  for (i = MAX_SPPED_TURN; i < 0; i = i - 20) {
     analogWrite(LEFT_MOTOR_PIN1, i);
     analogWrite(RIGHT_MOTOR_PIN1, i);
     delay(2);
  }
}

void Stop() {
   digitalWrite(LEFT_MOTOR_PIN1, LOW);
   digitalWrite(RIGHT_MOTOR_PIN2, LOW);

  for (i = MAX_SPEED ; i >= 0; i = i - 20) {
      analogWrite(LEFT_MOTOR_PIN2, i);
      analogWrite(RIGHT_MOTOR_PIN1, i);
    delay(2);
  }
}
