/* 모터 핀 */
//NODE MCU PIN MAPPING
//#define RIGHT_MOTOR_PIN1  5                   // pin 1 of right motor (D1)
//#define RIGHT_MOTOR_PIN2  4                   // pin 2 of right motor (D2)
//#define LEFT_MOTOR_PIN1   0                  // pin 1 of left motor (D3)
//#define LEFT_MOTOR_PIN2   2                  // pin 2 of left motor (D5)
//WEMOS D1 PIN MAPPING
//#define LEFT_MOTOR_PIN1   D6                  // 왼쪽모터의 +출력핀 주황
//#define LEFT_MOTOR_PIN2   D7                  // 왼쪽모터의 -출력핀 노랑
//#define RIGHT_MOTOR_PIN1  D8                   // 오른쪽모터의 +출력핀 초록
//#define RIGHT_MOTOR_PIN2  D9                  // 왼쪽모터의 -출력핀 파랑
//위치 변경
#define LEFT_MOTOR_PIN1   D2                  // 왼쪽모터의 +출력핀 주황
#define LEFT_MOTOR_PIN2   D3                  // 왼쪽모터의 -출력핀 노랑
#define RIGHT_MOTOR_PIN1  D4                   // 오른쪽모터의 +출력핀 초록
#define RIGHT_MOTOR_PIN2  D5                  // 왼쪽모터의 -출력핀 파랑
/* 초음파 센서 */
#define TRIGPIN D6
#define ECOPIN D7

/* 서보모터 */
int SERVO_TOY_PIN = D10; //(파랑선) //원래 D8이었는데 자꾸 저절로 HIGH가 되는듯 9도. 11핀갑자기아예안되네
//10번핀도 갑자기 계속 빙글빙글돔..디테치넣어서해결...
int SERVO_DOOR_PIN = D12;// (주황선)

/* PIR센서 */
int PIR = D8;                      // PIR을 2로 설정합니다.

/* 임시 LED PIN */
#define LED_PIN           2                   // built-in LED (D4)
