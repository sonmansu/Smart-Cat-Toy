//웹으로 제어하는 예제 
// Simple WiFi-controlled car on ESP8266 and L9110S motor drive board by Alan Wang
// https://www.hackster.io/alankrantas/simple-nodemcu-wifi-controlled-car-esp8266-c5491e
 /* 위 주소의 코드를 우리 상황에 맞게 수정함
  *  1. AP mode 를 station mode로 변경
  *  2. 핀 매핑 및 차 운전 방식은 키트 판매 싸이트 코드 따라함
  *  3. html 파일 분리 
  */
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "html.h"

// WiFi settings
#define WIFI_SSID            "KT_GiGA_2G_sumin" // AP server name
#define WIFI_PASSWORD        "sumin78900"         // AP server password

//#define WIFI_SSID            "winterz" // AP server name
//#define WIFI_PASSWORD        "201105166"         // AP server password

//#define SSID_AP            "ESP8266_WiFi_Car" // AP server name
//#define PASSWORD_AP        "12345678"         // AP server password

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
//900도 뭔가 밀어줘야 앞으로 나가서 걍 1000으로함..  (6v전압기준) 
#define RIGHT_MOTOR_SPEED 1000                // speed for right motor (0-1023)
#define LEFT_MOTOR_SPEED  1000                // speed for left motor (0-1023)
#define MOTOR_SPEED 1000 //모터의 기준속력입니다(0~255)

//카 운전 변수 설정
#define GO_FORWARD 0
#define GO_BACKWARD 1
#define TURN_LEFT 2
#define TURN_RIGHT 3
#define STOP 4

#define LED_PIN           2                   // built-in LED (D4)

  IPAddress local_ip(172, 30, 1, 130); // 사용할 IP 주소
  IPAddress gateway(172, 30, 1, 254); // 게이트웨이 주소
  IPAddress subnet(255, 255, 255, 0); // 서브넷 주소
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
//  WiFi.mode(WIFI_AP);
//  WiFi.softAPConfig(local_ip, gateway, subnet);
//  WiFi.softAP(SSID_AP, PASSWORD_AP);
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
  server.onNotFound(handle_NotFound);

  //start server
  server.begin();
  Serial.println("ESP8266 car server started.");
  digitalWrite(LED_PIN, LOW);

  SendHTML = MAIN_page;

}

// handle HTTP requests and control car
void loop() { 
  server.handleClient(); //클라이언트의 요청이 있는 경우 클라이언트와의 연결과 요청에 대한 처리를 하는 함수입니다.
  car_control();
}

/* 클라이언트 요청에 대한 함수들로 HTML 웹페이지 코드를 넣어주고 
send 메소드를 통하여 클라이언트로 데이터를 전송해줍니다. */
// HTTP request: on connect
void handle_OnConnect() {
  car_mode = 0;
  Serial.println("Client connected");
  server.send(200, "text/html", SendHTML);
}

// HTTP request: stop car
void handle_stop() {
  car_mode = STOP;
  Serial.println("Stopped");
  server.send(200, "text/html", SendHTML);
}

// HTTP request: go forward
void handle_forward() {
  car_mode = GO_FORWARD;
  Serial.println("Go forward...");
  server.send(200, "text/html", SendHTML);
}

// HTTP request: go backward
void handle_backward() {
  car_mode = GO_BACKWARD;
  Serial.println("Go backward...");
  server.send(200, "text/html", SendHTML);
}

// HTTP request: turn left
void handle_left() {
  car_mode = TURN_LEFT;
  Serial.println("Turn left...");
  server.send(200, "text/html", SendHTML);
}

// HTTP request: turn right
void handle_right() {
  car_mode = TURN_RIGHT;
  Serial.println("Turn right...");
  server.send(200, "text/html", SendHTML);
}

// HTTP request: other
void handle_NotFound() {
  car_mode = 0;
  Serial.println("Page error");
  server.send(404, "text/plain", "Not found");
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
    case TURN_RIGHT: // go backward 제자리 우회전 (정방향, 역방향)
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
  }
}

//// output HTML web page for user
//String SendHTML() {
//  String html = "<!DOCTYPE html>";
//  html += "<html>";
//  html += "<head>";
//  html += "<title>ESP8266 WiFi Car</title>";
//  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
//  html += "<style>body {background-color: Moccasin;} h1 {color: SaddleBrown;} h2 {color: Olive;}</style>";
//  html += "</head>";
//  html += "<body>";
//  html += "<div align=\"center\">";
//  html += "<h1>ESP8266 WiFi Car</h1>";
//  html += "<h2>Press \"stop\" after the server has been reset</h2>";
//  html += "<br>\n";
//  html += "<form method=\"GET\">";
//  html += "<input type=\"button\" value=\"Go forward\" onclick=\"window.location.href='/forward'\">";
//  html += "<br><br>\n";
//  html += "<input type=\"button\" value=\"Go backward\" onclick=\"window.location.href='/backward'\">";
//  html += "<br><br>\n";
//  html += "<input type=\"button\" value=\"Turn left\" onclick=\"window.location.href='/left'\">";
//  html += "<br><br>\n";
//  html += "<input type=\"button\" value=\"Turn right\" onclick=\"window.location.href='/right'\">";
//  html += "<br><br>\n";
//  html += "<input type=\"button\" value=\"Car stop\" onclick=\"window.location.href='/stop'\">";
//  html += "</form>\n";
//  html += "</div>\n";
//  html += "</body>\n";
//  html += "</html>\n";
//  return html;
//}
