/* 이 소스는 에듀이노(Eduino)에 의해서 번역, 수정, 작성되었고 소유권 또한 에듀이노의 것입니다. 
  소유권자의 허락을 받지 않고 무단으로 수정, 삭제하여 배포할 시 법적인 처벌을 받을 수도 있습니다. 
*/
#include <SoftwareSerial.h>
#include <AFMotor.h>
AF_DCMotor motor_L(1);            
AF_DCMotor motor_R(4); 

#define BT_RXD A5
#define BT_TXD A4
SoftwareSerial bluetooth(BT_RXD, BT_TXD);      

char rec_data;
bool rec_chk = false;

int i;
int j;

//초음파센서 출력핀(trig)과 입력핀(echo) 설정
int trigPin = A0;
int echoPin = A1;

void setup(){
  Serial.begin(9600);              // PC와의 시리얼 통신속도
  bluetooth.begin(9600);            // 스마트폰 블루투스 통신속도
  Serial.println("Eduino Smart Car Start!");

  pinMode(echoPin, INPUT);   // echoPin 입력
  pinMode(trigPin, OUTPUT);  // trigPin 출력

  // turn on motor
  motor_L.setSpeed(200);              // 왼쪽 모터의 속도   
  motor_L.run(RELEASE);
  motor_R.setSpeed(200);              // 오른쪽 모터의 속도   
  motor_R.run(RELEASE);
}


void loop(){
 
  if(bluetooth.available()){         // 블루투스 명령 수신
     rec_data = bluetooth.read();
     Serial.write(rec_data);
     rec_chk = true;
  }  

  if(rec_data == 'g'){  // 전진, go
     motor_L.run(FORWARD);  motor_R.run(FORWARD);        
  } 
  else if(rec_data == 'b'){ // 후진, back
     motor_L.run(BACKWARD);  motor_R.run(BACKWARD);    
  }
  else if(rec_data == 'l'){ // 좌회전, Go Left
   motor_L.run(RELEASE);  motor_R.run(FORWARD);     
  }
  else if(rec_data == 'r'){ // 우회전, Go Right
    motor_L.run(FORWARD);  motor_R.run(RELEASE);                
  }
  else if(rec_data == 'q'){ // 제자리 회전, Left Rotation
     motor_L.run(BACKWARD);   motor_R.run(FORWARD);      
  }
  else if(rec_data == 'w'){ // 제자리 회전, Right Rotation
      motor_L.run(FORWARD);   motor_R.run(BACKWARD);    
  }
  else if(rec_data == 's'){ // Stop 
    motor_L.run(RELEASE);       motor_R.run(RELEASE);
    } 

    
  if(rec_data == 'f' ){       // 정지
    if(rec_chk == true){
       for (i=250; i>=0; i=i-20) {
          motor_L.setSpeed(i);  motor_R.setSpeed(i);  
          delay(10);
       }  
       
    }
  }

     
}
