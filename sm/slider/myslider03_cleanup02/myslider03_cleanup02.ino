//https://randomnerdtutorials.com/esp8266-nodemcu-web-server-slider-pwm/ 에 수정함.
//myslider02를 정리한 코드

// Import required libraries
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Servo.h>
#include "index_html.h"

// Replace with your network credentials
//const char* ssid = "KT_GiGA_2G_sumin";
//const char* password = "sumin78900";
const char* ssid = "winterz";
const char* password = "201105166";

const int output = 2;

int sliderValue = 400; //초깃값
boolean flagToy = false;

const char* PARAM_INPUT = "value";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

Servo myservo;

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
//  Serial.begin(9600);
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

    myservo.attach(D14);

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
  });
  server.on("/servoButton", HTTP_GET, [](AsyncWebServerRequest * request) {
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
  // Send a GET request to <ESP_IP>/slider?value=<inputMessage>
  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      sliderValue = inputMessage.toInt();
//      analogWrite(output, sliderValue.toInt()); //led키는거 
//      runServo(sliderValue.toInt()); //여기선 동작안함
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });

  // Start server
  server.begin();
}

void loop() {
  if (flagToy) {
    if (sliderValue == 900) runRandomDelay();
    else runServo(sliderValue);
  }
}

void runServo(int delay_time) { //delay는 300이상 이어야..
  Serial.println((String) "delay_time: "+ delay_time);
//  while (true) {
//    if (Serial.available()) break; //end
    myservo.write(180); //최대각도
    delay(delay_time);
      myservo.write(0); //최소각도
    delay(delay_time);
//  }
}

void runRandomDelay() { //
  int delay_time;
//  while (true) {
//    if (Serial.available()) break;
    delay_time = random(300, 900);
    myservo.write(0);
    delay(delay_time);
    myservo.write(180);
    delay_time = random(300, 900);
    delay(delay_time);
//  }
}
