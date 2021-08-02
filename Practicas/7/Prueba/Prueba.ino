#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define CW 2
#define CCW 3
#define Frec5 4
#define Frec32 5

int Demora;
int Pasos [4][4] = {
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {0, 0, 1, 0},
  {0, 0, 0, 1}};

void setup(){
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(CW, INPUT_PULLUP);
  pinMode(CCW, INPUT_PULLUP);
  pinMode(Frec5, INPUT_PULLUP);
  pinMode(Frec32, INPUT_PULLUP);
}

void loop(){
  if(digitalRead(Frec5)==HIGH){
    Demora = 50;
  }
  if(digitalRead(Frec32)==HIGH){
    Demora = 8;
  }
  
  if(digitalRead(CW)==HIGH){
      for (int j = 0; j < 4; j++){
        digitalWrite(IN1, Pasos[j][0]);
        digitalWrite(IN2, Pasos[j][1]);
        digitalWrite(IN3, Pasos[j][2]);
        digitalWrite(IN4, Pasos[j][3]);
        delay(Demora);
      }
  }

  if(digitalRead(CCW)==HIGH){
      for (int j = 3; j >= 0; j--){
        digitalWrite(IN1, Pasos[j][0]);
        digitalWrite(IN2, Pasos[j][1]);
        digitalWrite(IN3, Pasos[j][2]);
        digitalWrite(IN4, Pasos[j][3]);
        delay(Demora);
      }
  }
}
