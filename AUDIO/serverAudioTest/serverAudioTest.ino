#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "web.h"

#define WIFI_SSID            "KT_GiGA_2G_sumin" // AP server name
#define WIFI_PASSWORD        "sumin78900"         // AP server password


IPAddress local_ip(172, 30, 1, 130); // 사용할 IP 주소
IPAddress gateway(172, 30, 1, 254); // 게이트웨이 주소
IPAddress subnet(255, 255, 255, 0); // 서브넷 주소
ESP8266WebServer server(80);


String sendHtml;

void setup() {
  delay(10);
  Serial.begin(115200);
  
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

    server.on("/", handle_OnConnect);


  server.begin();
  Serial.println("ESP8266 server started.");
  sendHtml = MAIN_page;
}
void handle_OnConnect() {
//  car_mode = 0;
  Serial.println("Client connected");
  server.send(200, "text/html", sendHtml);
}

void loop() {
  server.handleClient();
//  server.send(200, "text/html", sendHtml);
}
