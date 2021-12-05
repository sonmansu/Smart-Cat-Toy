//https://blog.naver.com/PostView.nhn?blogId=dokkosam&logNo=221422422662&categoryNo=0&parentCategoryNo=0&viewDate=&currentPage=1&postListTopCurrentPage=1&from=postView
//걍 스피커 피에조부저처럼 울려보는 테스트
int speaker = D13;
void setup() {
  // put your setup code here, to run once:
  pinMode(speaker, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  tone(speaker, 262); //도
  delay(1000);
  noTone(speaker);
  delay(500);
  
  tone(speaker, 294); //레
  delay(1000);
  noTone(speaker);
  delay(500);
}
