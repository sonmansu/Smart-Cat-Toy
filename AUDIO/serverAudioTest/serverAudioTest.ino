#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServerSecure.h>
#include "web.h"

//#define WIFI_SSID            "KT_GiGA_2G_sumin" // AP server name
//#define WIFI_PASSWORD        "sumin78900"         // AP server password

const char *ssid = "JJH";
const char* password = "Jeonjinhyeok0204";
const char *dname = "esp8266";

String sendHtml;

BearSSL::ESP8266WebServerSecure server(443);
ESP8266WebServer serverHTTP(80);

bool connectToWifi() {
  byte timeout = 50;

  Serial.println("\n\n");

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  for (int i = 0; i < timeout; i++) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nConnected to WiFi");
      Serial.print("Server can be accessed at https://");
      Serial.print(WiFi.localIP());
      if (MDNS.begin(dname)) {
        // https://superuser.com/questions/491747/how-can-i-resolve-local-addresses-in-windows
        Serial.print(" or at https://");
        Serial.print(dname);
        Serial.println(".local");
      }
      return true;
    }
    delay(5000);
    Serial.print(".");
  }

  Serial.println("\nFailed to connect to WiFi");
  Serial.println("Check network status and access data");
  Serial.println("Push RST to try again");
  return false;
}

void secureRedirect() {
  serverHTTP.sendHeader("Location", String("https://esp8266.local"), true);
  serverHTTP.send(301, "text/plain", "");
}

void handle_OnConnect() {
  Serial.println("Client connected");
  server.send(200, "text/html", sendHtml);
}


static const char serverCert[] PROGMEM = R"EOF(
//-----BEGIN CERTIFICATE-----
MIIC6jCCAlOgAwIBAgIUEyHrIFmH1Ug3LQI44Le0v+zuzBMwDQYJKoZIhvcNAQEL
BQAwejELMAkGA1UEBhMCUk8xCjAIBgNVBAgMAUIxEjAQBgNVBAcMCUJ1Y2hhcmVz
dDEbMBkGA1UECgwST25lVHJhbnNpc3RvciBbUk9dMRYwFAYDVQQLDA1PbmVUcmFu
c2lzdG9yMRYwFAYDVQQDDA1lc3A4MjY2LmxvY2FsMB4XDTIxMTEyNDA4NTIwNVoX
DTIyMTEyNDA4NTIwNVowejELMAkGA1UEBhMCUk8xCjAIBgNVBAgMAUIxEjAQBgNV
BAcMCUJ1Y2hhcmVzdDEbMBkGA1UECgwST25lVHJhbnNpc3RvciBbUk9dMRYwFAYD
VQQLDA1PbmVUcmFuc2lzdG9yMRYwFAYDVQQDDA1lc3A4MjY2LmxvY2FsMIGfMA0G
CSqGSIb3DQEBAQUAA4GNADCBiQKBgQDYqh3WqEShHmKcIQsbIRDXpizsVDBzbzgc
Rjdcwbv4qPeiwLZH3hWDzuc6Fb7LMkhH1eyLXbCfXy3NvadHoRb6N6DZcNHU07YH
9vUaMZL5nO2hKdYIsr1ph+190N1WGd6mT/org76ySMUYe3oa904Lf4kuMNmAwm2w
WhFUuyuFbQIDAQABo20wazAdBgNVHQ4EFgQU8e33IYFa5P5yVkOm8Ilzl/JFTTsw
HwYDVR0jBBgwFoAU8e33IYFa5P5yVkOm8Ilzl/JFTTswDwYDVR0TAQH/BAUwAwEB
/zAYBgNVHREEETAPgg1lc3A4MjY2LmxvY2FsMA0GCSqGSIb3DQEBCwUAA4GBACLB
VsPBAEHjlGTKuTkALWipMiGF0Hiq34VKrzz4I2hh500ypEQvk42ztsQPNiyKewCj
hBzNydOA8DKmTkLobDio28IfLbBZsoWHdSuhsSZKlBQ31tGmJnBpzOVwRVC+z1Ra
jFGjq5aurqsodAlVzjaypKWiNPkCGs31j+8+DHOO
//-----END CERTIFICATE-----
)EOF";

static const char serverKey[] PROGMEM =  R"EOF(
//-----BEGIN PRIVATE KEY-----
MIICdwIBADANBgkqhkiG9w0BAQEFAASCAmEwggJdAgEAAoGBANiqHdaoRKEeYpwh
CxshENemLOxUMHNvOBxGN1zBu/io96LAtkfeFYPO5zoVvssySEfV7ItdsJ9fLc29
p0ehFvo3oNlw0dTTtgf29Roxkvmc7aEp1giyvWmH7X3Q3VYZ3qZP+iuDvrJIxRh7
ehr3Tgt/iS4w2YDCbbBaEVS7K4VtAgMBAAECgYBTgl412m15XGjNnL7XGguP0vEF
tf1mwLtzymyUR+fXk+i+xmB7mtHYF+tvq+n6D8tkRMQDg30MMHdLEYpkRWbBHRB8
ORswpd56I27/3GpS9h9ri0zyxkNiGpjtF9NGGJfUu4Ze3m7mfo3Zopf7Ob1OXh0p
0EinssF/DHl/S4Cs0QJBAPCOv9ljPY45PPKyEQ0wTArHXRG44WKnnnRVuYeciUnW
touV6ztyZiZ60NnDrJeubkdjxOJBlNK/BV9XKhCrAYMCQQDmkrcbjXaglgxivs59
LtXxTzvBmZXeeYOWVsltSb1UC4f0cE6qV63l2ApqCXnUFb3wj2Ek5RtfRbx41i5Y
SlpPAkEAveHAGAVY6nHN5TifcwyjiYKSuVF5PxlWXzfnid8LE2jTkN0W4EbN0SPy
xWHKU7SRQfLDz2C665tyzy4LezqwpwJABJ2rTMHoPg7C8LchKyBk6A/OAnIwreOA
3uGd5rIzOBuC/UHCUWav9In+q2DFL5m/07ELINH1WlLrEwA2rU3PwQJBAK5OPmdW
04jmQXUZ70rmIX7DdKXoS9x332o8dyvcvuF7Fx/nsrwfnZQ9rkgNNK/0YmByoSId
WQxSHZUcCB7CfrA=
//-----END PRIVATE KEY-----
)EOF";

//IPAddress local_ip(172, 30, 1, 130); // 사용할 IP 주소
//IPAddress gateway(172, 30, 1, 254); // 게이트웨이 주소
//IPAddress subnet(255, 255, 255, 0); // 서브넷 주소



void setup() {
  Serial.begin(115200);

  sendHtml = MAIN_page;

  if(!connectToWifi()){
    delay(60000);
    ESP.restart();
  }
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  
  serverHTTP.on("/", secureRedirect);
  serverHTTP.begin();
  

  server.getServer().setRSACert(new BearSSL::X509List(serverCert), new BearSSL::PrivateKey(serverKey));
  server.on("/", handle_OnConnect);
  server.begin();
  
  Serial.println("ESP8266 server started.");
  
}

void loop() {
  serverHTTP.handleClient();
  server.handleClient();
  MDNS.update();
}
