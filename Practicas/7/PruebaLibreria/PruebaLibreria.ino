#include <Stepper.h>

Stepper motor1(2048, 8, 10, 9, 11);

void setup(){
  motor1.setSpeed(10);
}

void loop(){
  motor1.step(512);

}
