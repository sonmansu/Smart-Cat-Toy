/* 이 소스는 에듀이노(Eduino)에 의해서 번역, 수정, 작성되었고 소유권 또한 에듀이노의 것입니다. 
  소유권자의 허락을 받지 않고 무단으로 수정, 삭제하여 배포할 시 법적인 처벌을 받을 수도 있습니다. 
*/
#include <SoftwareSerial.h>
#include <AFMotor.h>

AF_DCMotor motor_L(1);              
AF_DCMotor motor_R(4); 

void setup() {
  motor_L.setSpeed(175);              
  motor_L.run(RELEASE);
  motor_R.setSpeed(200);                 
  motor_R.run(RELEASE);
}

void loop() {
 motor_L.run(FORWARD); 
 motor_R.run(FORWARD); 
 delay(2000);
 
 motor_L.run(RELEASE);
 motor_R.run(RELEASE);
 delay(1000);
 
 motor_L.run(BACKWARD);
 motor_R.run(BACKWARD);
 delay(2000);

 motor_L.run(RELEASE); 
 motor_R.run(RELEASE); 
 delay(1000);
}
