// Simple WiFi-controlled car on ESP8266 and L9110S motor drive board by Alan Wang
// https://www.hackster.io/alankrantas/simple-nodemcu-wifi-controlled-car-esp8266-c5491e
/* 위 주소의 코드(웹에서 차 주행)를 우리 상황에 맞게 수정함
    1. AP mode 를 station mode로 변경
        2. 핀 매핑 및 차 운전 방식은 키트 판매 싸이트 코드 따라함
        3. html 파일 분리
        4. 초음파센서 연결, 자율주행 기능 : https://m.blog.naver.com/no1_devicemart/221312209045
        5. 서보모터 - 장난감
        6. ESP8266WebServer.h를 ESPAsyncWebServer.h 바꿨음 (Slider)
        7. 서보모터 - 문 여닫기 
            */
