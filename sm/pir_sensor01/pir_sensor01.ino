int PIR = D10;                      // PIR을 2로 설정합니다.
void setup() {
  Serial.begin(9600);        // 시리얼 통신을 사용하기 위해 보드레이트를 9600으로 설정합니다.
  pinMode(PIR, INPUT);   // PIR를 입력핀으로 설정합니다.
}
void loop() {
  if (digitalRead(PIR) == HIGH) {    // PIR핀의 디지털 입력이 HIGH라면
    Serial.println("감지O");   // "SENSOR ON"을 시리얼 통신으로 출력하고 줄을 바꿉니다.
  } else {                                   // PIR핀의 디지털 입력이 HIGH가 아니라면
    Serial.println("감지X");                    // 줄을 바꿉니다.
  }
  delay(100);                              // 0.1초만큼 지연합니다.
}
