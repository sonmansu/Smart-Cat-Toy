#include <ESP8266WiFi.h>

const char* ssid = "KT_GiGA_2G_sumin";
const char* password = "sumin78900";

WiFiServer server(80);

void setup() {
  delay(10);

  Serial.begin(115200);

  Serial.println();
  Serial.println();
  Serial.println("connecting to my ssid.");
  
  WiFi.begin(ssid, password);  
   while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.println(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");

  // start the server
  server.begin();
  Serial.println("Server started");
  Serial.println("Use this URL to connect");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  WiFiClient client = server.available();  

  if(!client){
    return;
  }
  else{
    Serial.println("New client connect...");
    boolean blank_line = true;
    while(client.connected()){
      char c = client.read();
      if(c == '\n' && blank_line){
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println();

        client.println("<!DOCTYPE html>");
        client.println("")
      }
    }
  }

}
