#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h> //#include <ESP8266WebServer.h>
#include <Servo.h>
#include "html.h"
#include "wifi.h"
#include "pin_mapping.h"
#include "constant.h"

AsyncWebServer server(80);

/* 플래그 변수 모음 */
//RC카
int car_mode = STOP;                             // set car drive mode (0 = stop)
//서보모터_장난감 toy 
int sliderValue = 400; //초깃값
boolean flagToy = false;
const char* PARAM_INPUT = "value";
//서보모터_간식주기 door
boolean flagDoor = false;
Servo servoDoor;
Servo servoToy;


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
  car_control(STOP); // stop the car

  // 와이파이 연결
  //    WiFi.mode(WIFI_AP);
  //    WiFi.softAPConfig(local_ip, gateway, subnet);
  //    WiFi.softAP(SSID_AP, PASSWORD_AP);

  //  WiFi.config(local_ip, gateway, subnet);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  servoToy.attach(SERVO_TOY_PIN);

  // on 함수는 위에서 설명한 것과 같이 클라이언트의 요청에 따라 어떤 처리를 할 것인지 연결시켜주는 함수입니다.
  // server.on("/", HTTP_GET, handle_OnConnect);
  /* 클라이언트 요청에 대한 함수들로 HTML 웹페이지 코드를 넣어주고
    send 메소드를 통하여 클라이언트로 데이터를 전송해줍니다. */
  //void handle_OnConnect() {
  //  Serial.println("Client connected");
  //  server.send(200, "text/html", SendHTML);
  //}

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    Serial.println("Client connected");
    //    request->send_P(200, "text/html", MAIN_page);
    request->send(200, "text/html", MAIN_page);
  });
  server.on("/forward", HTTP_GET, [](AsyncWebServerRequest * request) {
    car_mode = GO_FORWARD;
    //    request->send(200, "text/plain", "OK");
    request->send(200, "text/html", MAIN_page);

  });
  server.on("/backward", HTTP_GET, [](AsyncWebServerRequest * request) {
    car_mode = GO_BACKWARD;
    //    request->send(200, "text/plain", "OK");
    request->send(200, "text/html", MAIN_page);

  });
  server.on("/left", HTTP_GET, [](AsyncWebServerRequest * request) {
    car_mode = TURN_LEFT;
    //    request->send(200, "text/plain", "OK");
    request->send(200, "text/html", MAIN_page);

  });
  server.on("/right", HTTP_GET, [](AsyncWebServerRequest * request) {
    car_mode = TURN_RIGHT;
    //    request->send(200, "text/plain", "OK");
    request->send(200, "text/html", MAIN_page);

  });
  server.on("/stop", HTTP_GET, [](AsyncWebServerRequest * request) {
    car_mode = STOP;
    //    request->send(200, "text/plain", "OK");
    request->send(200, "text/html", MAIN_page);
  });
  server.on("/obstacle", HTTP_GET, [](AsyncWebServerRequest * request) {
    //    request->send(200, "text/plain", "OK");
    car_mode = OBSTACLE;
    request->send(200, "text/html", MAIN_page);
//    obstacle_drive();
  });
  server.on("/toyButton", HTTP_GET, [](AsyncWebServerRequest * request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      flagToy = inputMessage == "1";
      Serial.println((String) "flagToy: " + flagToy);
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });
  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      sliderValue = inputMessage.toInt();
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });
  server.on("/doorButton", HTTP_GET, [] (AsyncWebServerRequest * request) {
    flagDoor = true;
//    runServoDoor();
    request->send(200, "text/plain", "OK");
  });

  //start server
  server.begin();
  Serial.println("ESP8266 car server started.");

  //초음파
  pinMode(TRIGPIN, OUTPUT);   //초음파센서 트리거핀을 출력모드로 설정합니다.
  pinMode(ECOPIN, INPUT);    //초음파센서 에코핀을 입력모드로 설정합니다.

}

// handle HTTP requests and control car
void loop() {
  car_control(car_mode);
  if (flagToy) {
    if (sliderValue == 900) runRandomDelay();
    else runServoToy(sliderValue);
  }
  if (flagDoor)  {
    runServoDoor();
  }  else {
    
  }
}

void runServoDoor() {
    Serial.println("runServoDoor()");
    servoDoor.attach(SERVO_DOOR_PIN);
    servoDoor.write(130); //문열음
    delay(60); //돌아가길 기다림
    servoDoor.detach();//진동 심해서 추가
    delay(3000); //3초 기다림
    servoDoor.attach(SERVO_DOOR_PIN);
    servoDoor.write(0);   //문닫음
    delay(60);
    servoDoor.detach(); 
    flagDoor = false;
}

void runServoToy(int delay_time) { //delay는 300이상 이어야..
  Serial.println((String) "delay_time: "+ delay_time);
//  while (true) {
    servoToy.write(180); //최대각도
    delay(delay_time);
      servoToy.write(0); //최소각도
    delay(delay_time);
//  }
}
void runRandomDelay() { //
  int delay_time;
//  while (true) {
    delay_time = random(300, 900);
    servoToy.write(0);
    delay(delay_time);
    servoToy.write(180);
    delay_time = random(300, 900);
    delay(delay_time);
//  }
}

void obstacle_drive() {
  while (true) {
    if (car_mode == STOP) break;
    Serial.println("obstacle_drive()");
//    long distance = Distance_Measurement();  //전방 거리측정
    long distance = Distance_Measurement();  //전방 거리측정
    Serial.println((String) "obstacle_drive함수내 distance: " + distance);

    if (distance > 30) //전방 거리가 30cm 초과일때 보통 속도로 전진
    {
      //      Forward(1000);
      car_control(GO_FORWARD);
    }
    else if (distance > 20) //30>= 전방거리 > 15cm 일때 장애물 회피
    {
      int val = random(2);
      if (val == 0) {
        //        Right(1000);
        car_control(TURN_RIGHT);
        delay(TURN90);
      }
      else if (val == 1) {
        //      Left(1000);
        car_control(TURN_LEFT);
        delay(TURN90);
      }
      car_control(STOP);
      //    Stop();
      delay(300); //
    } else { //전방거리 15센치 이하일떄 뒤로감
      //    Backward(1000);
      car_control(GO_BACKWARD);
      delay(500);
      //    Right(1000);
      //    delay(TURN90*2);
      car_control(STOP);
      delay(300); //
    }
  }
}
long Distance_Measurement() {
  long duration, distance;
  // Clears the trigPin
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIGPIN, HIGH);  // trigPin에서 초음파 발생(echoPin도 HIGH)
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  duration = pulseIn(ECOPIN, HIGH);    // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  distance = ((float)(SOUND_VELOCITY * duration) / 10000) / 2;
//  distance = duration * * SOUND_VELOCITY/2;
//  Serial.print((String) "Distance_Measurement()함수" + distance);
//  Serial.println("mm");
//  distance = (float)distance / 10;
  Serial.print((String) "Distance_Measurement()함수" + distance + "cm");
  return distance;
}
// control car movement
void car_control(int car_mode) { //매개변수 추가
  switch (car_mode) {
    case STOP: // stop car 정지: (정방향, 정방향)인데 속도값 0으로
      Serial.println("Stopped");
      digitalWrite(LEFT_MOTOR_PIN1, LOW);
      digitalWrite(LEFT_MOTOR_PIN2, LOW);
      digitalWrite(RIGHT_MOTOR_PIN1, LOW);
      digitalWrite(RIGHT_MOTOR_PIN2, LOW);
      break;
    case TURN_LEFT: // go forward 좌회전: (역방향, 정방향)
      Serial.println("Turn left...");
      analogWrite(LEFT_MOTOR_PIN1, MOTOR_SPEED);
      digitalWrite(LEFT_MOTOR_PIN2, LOW);
      analogWrite(RIGHT_MOTOR_PIN1, MOTOR_SPEED);
      digitalWrite(RIGHT_MOTOR_PIN2, LOW);
      break;
    case TURN_RIGHT: // go backward 제자리 우회전 (역방향, 정방향)
      Serial.println("Turn right...");
      digitalWrite(LEFT_MOTOR_PIN1, LOW);
      analogWrite(LEFT_MOTOR_PIN2, MOTOR_SPEED);
      digitalWrite(RIGHT_MOTOR_PIN1, LOW);
      analogWrite(RIGHT_MOTOR_PIN2, MOTOR_SPEED);
      break;
    case GO_FORWARD: // turn left 전진 - low, low일때 (정방향,정방향)
      Serial.println("Go forward...");
      digitalWrite(LEFT_MOTOR_PIN1, LOW);
      analogWrite(LEFT_MOTOR_PIN2, MOTOR_SPEED);
      analogWrite(RIGHT_MOTOR_PIN1, MOTOR_SPEED);
      digitalWrite(RIGHT_MOTOR_PIN2, LOW);
      break;
    case GO_BACKWARD: // turn right 후진 (역방향, 역방향)
      Serial.println("Go backward...");
      analogWrite(LEFT_MOTOR_PIN1, MOTOR_SPEED);
      digitalWrite(LEFT_MOTOR_PIN2, LOW);
      digitalWrite(RIGHT_MOTOR_PIN1, LOW);
      analogWrite(RIGHT_MOTOR_PIN2, MOTOR_SPEED);
      break;
    case OBSTACLE: // turn right 후진 (역방향, 역방향)
      obstacle_drive();
      break;
defalt:
      break;
  }
}
