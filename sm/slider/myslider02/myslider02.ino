//https://randomnerdtutorials.com/esp8266-nodemcu-web-server-slider-pwm/
/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-web-server-slider-pwm/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/
//별 시행착오 포함된 코드

// Import required libraries
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Servo.h>
#include "index_html.h"

// Replace with your network credentials
const char* ssid = "KT_GiGA_2G_sumin";
const char* password = "sumin78900";

const int output = 2;

String sliderValue = "0";
boolean flagServo = false;

const char* PARAM_INPUT = "value";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

Servo myservo;

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  myservo.attach(2);
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/slider?value=<inputMessage>
  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputMessage;
    // GET input1 value on <ESP_IP>/slider?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      sliderValue = inputMessage;
      //      int intSliderVal = sliderValue.toInt();
      //      if (intSliderVal == 900) runRandomDelay();
      //      else runServo(intSliderVal);
      analogWrite(output, sliderValue.toInt());
//      runServo(sliderValue.toInt());
      flagServo = true;
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
//  int intSliderVal = sliderValue.toInt();
//  if (intSliderVal == 900) runRandomDelay();
//  else runServo(intSliderVal);
  if (flagServo) runServo(sliderValue.toInt());
}
//void myDelay(int delay_time) {
//  for (int i = 0; i < delay_time; i++) {}
//}
//void runServo(int delay_time) { //delay는 300이상 이어야..
////  while (true) {
//    myservo.write(180); //최대각도
//    myDelay(delay_time);
//    myservo.write(0); //최소각도
//    myDelay(delay_time);
////  }
//}

//void runServo(int delay_time) { //delay는 300이상 이어야..
//    unsigned long time_now = 0;
//    int angle = 0;
//
//  while  (true) {
//    if (millis() > time_now + delay_time) {
//      angle = (angle == 0) ? 180 : 0; //0이면 180사용, 0이 아니면 0 사용 
//      myservo.write(angle); //최소각도
//      time_now = millis();
//    }
//  }
//}

void runServo(int delay_time) { //delay는 300이상 이어야..
  while (true) {
//    if (Serial.available()) break; //end
    myservo.write(180); //최대각도
    delay(delay_time);
      myservo.write(0); //최소각도
    delay(delay_time);
  }
}

void runRandomDelay() { //
  int delay_time;
  while (true) {
//    if (Serial.available()) break;
    delay_time = random(300, 900);
    myservo.write(0);
    delay(delay_time);
    myservo.write(180);
    delay_time = random(300, 900);
    delay(delay_time);
  }
}
