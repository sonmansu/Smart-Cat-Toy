// Simple WiFi-controlled car on ESP8266 and L9110S motor drive board by Alan Wang
// https://www.hackster.io/alankrantas/simple-nodemcu-wifi-controlled-car-esp8266-c5491e
/* 위 주소의 코드(웹에서 차 주행)를 우리 상황에 맞게 수정함
    1. AP mode 를 station mode로 변경
    2. 핀 매핑 및 차 운전 방식은 키트 판매 싸이트 코드 따라함
    3. html 파일 분리
    4. 초음파센서 연결, 자율주행 기능 : https://m.blog.naver.com/no1_devicemart/221312209045
    5. 서보모터 - 장난감 
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "html.h"

// WiFi settings
#define WIFI_SSID            "KT_GiGA_2G_sumin" // AP server name
#define WIFI_PASSWORD        "sumin78900"         // AP server password
IPAddress local_ip(172, 30, 1, 130); // 사용할 IP 주소
IPAddress gateway(172, 30, 1, 254); // 게이트웨이 주소
IPAddress subnet(255, 255, 255, 0); // 서브넷 주소
//#define WIFI_SSID "JJH"
//#define WIFI_PASSWORD "Jeonjinhyeok0204"

//#define SSID_AP            "ESP8266_WiFi_Car" // AP server name
//#define PASSWORD_AP        "12345678"         // AP server password
//IPAddress local_ip(192, 168, 188, 1);           //IP for AP mode
//IPAddress gateway(192, 168, 188, 184);          //IP for AP mode
//IPAddress subnet(255, 255, 255, 0);  

// motor settings
//NODE MCU PIN MAPPING
//#define RIGHT_MOTOR_PIN1  5                   // pin 1 of right motor (D1)
//#define RIGHT_MOTOR_PIN2  4                   // pin 2 of right motor (D2)
//#define LEFT_MOTOR_PIN1   0                  // pin 1 of left motor (D3)
//#define LEFT_MOTOR_PIN2   2                  // pin 2 of left motor (D5)
//WEMOS D1 PIN MAPPING
#define LEFT_MOTOR_PIN1   D6                  // 왼쪽모터의 +출력핀 주황
#define LEFT_MOTOR_PIN2   D7                  // 왼쪽모터의 -출력핀 노랑
#define RIGHT_MOTOR_PIN1  D8                   // 오른쪽모터의 +출력핀 초록
#define RIGHT_MOTOR_PIN2  D9                  // 왼쪽모터의 -출력핀 파랑
//원래 값 1023은 너무빠른데 삐소리아예 안남. 800은 적당한데 삐소리가 조금나서 900으로 설정함.
#define RIGHT_MOTOR_SPEED 900                // speed for right motor (0-1023)
#define LEFT_MOTOR_SPEED  900                // speed for left motor (0-1023)
int MOTOR_SPEED = 500; //모터의 기준속력입니다(0~255)
//카 운전 변수 설정
#define GO_FORWARD 0
#define GO_BACKWARD 1
#define TURN_LEFT 2
#define TURN_RIGHT 3
#define STOP 4
//초음파 센서
#define TRIGPIN D12
#define ECOPIN D13

#define TURN90  600     //제자리 90도 회전 Delay
#define LED_PIN           2                   // built-in LED (D4)

ESP8266WebServer server(80);

int car_mode = 0;                             // set car drive mode (0 = stop)
String SendHTML;
// initialize
void setup() {

  //  Serial.begin(115200);
  Serial.begin(9600);

  Serial.println("ESP8266 Wifi Car");
  pinMode(RIGHT_MOTOR_PIN1, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN2, OUTPUT);
  pinMode(LEFT_MOTOR_PIN1, OUTPUT);
  pinMode(LEFT_MOTOR_PIN2, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  car_control(); // stop the car

  // 와이파이 연결
//    WiFi.mode(WIFI_AP);
//    WiFi.softAPConfig(local_ip, gateway, subnet);
//    WiFi.softAP(SSID_AP, PASSWORD_AP);
  WiFi.config(local_ip, gateway, subnet);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  // setup web server to handle specific HTTP requests
  // on 함수는 위에서 설명한 것과 같이 클라이언트의 요청에 따라 어떤 처리를 할 것인지 연결시켜주는 함수입니다.
  server.on("/", HTTP_GET, handle_OnConnect);
  server.on("/forward", HTTP_GET, handle_forward);
  server.on("/backward", HTTP_GET, handle_backward);
  server.on("/left", HTTP_GET, handle_left);
  server.on("/right", HTTP_GET, handle_right);
  server.on("/stop", HTTP_GET, handle_stop);
  server.on("/obstacle", HTTP_GET, handle_obstacle);
  server.on("/toy", HTTP_GET, handle_toy);


  server.onNotFound(handle_NotFound);

  //start server
  server.begin();
  Serial.println("ESP8266 car server started.");

  SendHTML = MAIN_page;

  //초음파
  pinMode(TRIGPIN, OUTPUT);   //초음파센서 트리거핀을 출력모드로 설정합니다.
  pinMode(ECOPIN, INPUT);    //초음파센서 에코핀을 입력모드로 설정합니다.

}

// handle HTTP requests and control car
void loop() {
  server.handleClient(); //클라이언트의 요청이 있는 경우 클라이언트와의 연결과 요청에 대한 처리를 하는 함수입니다.
//  car_control();
}

/* 클라이언트 요청에 대한 함수들로 HTML 웹페이지 코드를 넣어주고
  send 메소드를 통하여 클라이언트로 데이터를 전송해줍니다. */
// HTTP request: on connect
void handle_OnConnect() {
  Serial.println("Client connected");
  server.send(200, "text/html", SendHTML);
}
void handle_toy(){
  
}

void handle_obstacle() {
  server.send(200, "text/html", SendHTML);
  obstacle_drive();
}

// HTTP request: stop car
void handle_stop() {
  server.send(200, "text/html", SendHTML);
  Stop();
}

// HTTP request: go forward
void handle_forward() {  Forward(MOTOR_SPEED);
  car_mode = 0;
  server.send(200, "text/html", SendHTML);
}

// HTTP request: go backward
void handle_backward() {
  server.send(200, "text/html", SendHTML);
  Backward(MOTOR_SPEED);
}

// HTTP request: turn left
void handle_left() {
  server.send(200, "text/html", SendHTML);
  Left(MOTOR_SPEED);
}

// HTTP request: turn right
void handle_right() {
  server.send(200, "text/html", SendHTML);
  Right(MOTOR_SPEED);
}

// HTTP request: other
void handle_NotFound() {
  Serial.println("Page error");
  server.send(404, "text/plain", "Not found");
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
void obstacle_drive() {
//  while(true) {
    long distance = Distance_Measurement();  //전방 거리측정
    Serial.println((String) "obstacle_drive함수내 distance: " + distance);
  
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
//  }
}
long Distance_Measurement() {
  long duration, distance;
  digitalWrite(TRIGPIN, HIGH);  // trigPin에서 초음파 발생(echoPin도 HIGH)
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  duration = pulseIn(ECOPIN, HIGH);    // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  distance = ((float)(340 * duration) / 1000) / 2;
  Serial.print((String) "Distance_Measurement()함수" + distance);
  Serial.println("mm");
  distance = (float)distance/10;
  Serial.print((String) "Distance_Measurement()함수" + distance);
  Serial.println("cm");
  return distance;
}
// control car movement
void car_control() {
  switch (car_mode) {
    case STOP: // stop car 정지: (정방향, 정방향)인데 속도값 0으로
      digitalWrite(LEFT_MOTOR_PIN1, LOW);
      digitalWrite(LEFT_MOTOR_PIN2, LOW);
      digitalWrite(RIGHT_MOTOR_PIN1, LOW);
      digitalWrite(RIGHT_MOTOR_PIN2, LOW);
      break;
    case TURN_LEFT: // go forward 좌회전: (역방향, 정방향)
      analogWrite(LEFT_MOTOR_PIN1, MOTOR_SPEED);
      digitalWrite(LEFT_MOTOR_PIN2, LOW);
      analogWrite(RIGHT_MOTOR_PIN1, MOTOR_SPEED);
      digitalWrite(RIGHT_MOTOR_PIN2, LOW);
      break;
    case TURN_RIGHT: // go backward 제자리 우회전 (역방향, 정방향)
      digitalWrite(LEFT_MOTOR_PIN1, LOW);
      analogWrite(LEFT_MOTOR_PIN2, MOTOR_SPEED);
      digitalWrite(RIGHT_MOTOR_PIN1, LOW);
      analogWrite(RIGHT_MOTOR_PIN2, MOTOR_SPEED);
      break;
    case GO_FORWARD: // turn left 전진 - low, low일때 (정방향,정방향)
      digitalWrite(LEFT_MOTOR_PIN1, LOW);
      analogWrite(LEFT_MOTOR_PIN2, MOTOR_SPEED);
      analogWrite(RIGHT_MOTOR_PIN1, MOTOR_SPEED);
      digitalWrite(RIGHT_MOTOR_PIN2, LOW);
      break;
    case GO_BACKWARD: // turn right 후진 (역방향, 역방향)
      analogWrite(LEFT_MOTOR_PIN1, MOTOR_SPEED);
      digitalWrite(LEFT_MOTOR_PIN2, LOW);
      digitalWrite(RIGHT_MOTOR_PIN1, LOW);
      analogWrite(RIGHT_MOTOR_PIN2, MOTOR_SPEED);
      break;
  }
}
