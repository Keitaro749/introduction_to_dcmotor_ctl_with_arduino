#include <MsTimer2.h>
byte state = 0;     //停止状態：０　高速状態：１　低速状態：２
byte count = 0;     //タイマー割込みが起こった回数をカウントする。
bool ledlight = true;
byte button = 2;
int btn = 0;
int prebtn = 0;

void setup() {
  pinMode(A0,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  digitalWrite(A0,ledlight);
  analogWrite(10,0);  
  MsTimer2::set(500,timerwarikomi);
  MsTimer2::start();
}

void timerwarikomi(){
  count++;
    switch(state){
    case 0:
      if(count >= 10){
        digitalWrite(A0,ledlight = ledlight^1);
        count=0;
      }
      break;
    case 1:
      digitalWrite(A0,ledlight = ledlight^1);
      if(count >= 10){ 
        analogWrite(10,100);
        state = 2;
        count = 0;
      }
      break;    
    case 2:
      if(count >= 4){
        digitalWrite(A0,ledlight = ledlight^1);
        count = 0;
      }
      break;
  }
}

void loop() {
  btn = digitalRead(button);
  if(btn = LOW && prebtn == HIGH){
    switch(state){
      case 0:
        analogWrite(10,200);
     　　   state=1;
        count = 0;
        break;
      case 1:
        break;
      case 2:
        analogWrite(10,0);
        state = 0;
        count = 0;
        break;
    }
  }
  prebtn = btn;
}
