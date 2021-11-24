#include <SoftwareSerial.h> 
#include <AFMotor.h>       // L293D 모터 드라이브 라이브러리
 
AF_DCMotor motor_1(1);     // 모터 1 객체         
 
 
void setup() {
  motor_1.setSpeed(150);    // 모터 1 속도 설정          
  motor_1.run(RELEASE);     // 모터 1 돌리지 않는 상태
}
 
void loop() {
 // 모터 1
 motor_1.run(FORWARD);    // 정방향으로 회전
 delay(1000);
 motor_1.run(RELEASE);    // 쉬기
 delay(1000);
 motor_1.run(BACKWARD);   // 역방향 회전
 delay(1000);
 motor_1.run(RELEASE);    // 쉬기
 delay(1000);
}
