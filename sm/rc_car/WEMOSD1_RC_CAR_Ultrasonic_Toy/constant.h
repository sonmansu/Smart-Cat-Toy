/* rc car */
//원래 값 1023은 너무빠른데 삐소리아예 안남. 800은 적당한데 삐소리가 조금나서 900으로 설정함.
#define RIGHT_MOTOR_SPEED 900                // speed for right motor (0-1023)
#define LEFT_MOTOR_SPEED  900                // speed for left motor (0-1023)
int MOTOR_SPEED = 500; //모터의 기준속력입니다(0~255)
//카 운전 변수 설정
#define GO_FORWARD 0
#define GO_BACKWARD 1
#define TURN_LEFT 2
#define TURN_RIGHT 3
#define STOP 4
#define OBSTACLE 5
#define TURN90  600     //제자리 90도 회전 Delay

/*초음파센서*/
#define SOUND_VELOCITY 340
