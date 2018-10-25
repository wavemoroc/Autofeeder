#include <Servo.h>

Servo myservo;
int pos = 0 ;

void Servo_setup() {
  myservo.attach(13);
  myservo.write(180);
  }
  
void sweep() {
  
    myservo.write(0);
   delay(vol*1000);
    myservo.write(180);
    return;
}


