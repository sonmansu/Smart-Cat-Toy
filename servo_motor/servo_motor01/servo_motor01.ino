#include <Servo.h>
Servo myservo; // create servo object to control a servo
int pos = 0; // variable to store the servo position
void setup()
{
  // attaches the servo on pin 10 to the servo object
  myservo.attach(D10);
}

void loop()
{
  // sweeps from 0 degrees to 180 degrees
  for (pos = 0; pos <= 180; pos += 1) // sweeps from 180 degrees to 0 degrees for(pos = 180; pos>=0; pos-=1)
  {
    myservo.write(pos);
    delay(15);
  }
}
