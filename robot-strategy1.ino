#include <Servo.h>
#include <AceRoutine.h>

// strategy1: 自己rotate 加被動攻擊 加超音波可能沒有什麼軟用的干擾

using namespace ace_routine;

Servo motors[6]; 
const int trigPins[4] = {7,11,9,5};

void attack(int trigPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  delay(1);
}

void setup() {
  motors[0].attach(13); // 前左輪360
  motors[2].attach(2);  // 後左輪360
  motors[1].attach(3);  // 前右輪360
  motors[3].attach(4);  // 後右輪360
  motors[4].attach(6);  // 右邊0~180
  motors[5].attach(8);  // 左邊0~180
  pinMode(trigPins[0], OUTPUT);
  pinMode(trigPins[1], OUTPUT);
  pinMode(trigPins[2], OUTPUT);
  pinMode(trigPins[3], OUTPUT);
}


COROUTINE(move) {
  COROUTINE_LOOP(){
    // <90 順轉 
    // >90 逆轉
    // 只能20~160
    // forward
    motors[0].write(160);  // 前左輪
    motors[2].write(160);  // 後左輪
    motors[1].write(20); // 前右輪
    motors[3].write(20); // 後右輪
    COROUTINE_DELAY(2800);
    // reverse
    motors[0].write(20);  // 前左輪
    motors[2].write(20);  // 後左輪
    motors[1].write(160); // 前右輪
    motors[3].write(160); // 後右輪
    COROUTINE_DELAY(2800);
  }
}


COROUTINE(kick) {
  COROUTINE_LOOP(){
    motors[4].write(0);   // 右邊攻擊
    motors[5].write(0);   // 左邊攻擊
    COROUTINE_DELAY(500);
    motors[4].write(180); // 右邊攻擊
    motors[5].write(180); // 左邊攻擊
    COROUTINE_DELAY(600);
  }
}

COROUTINE(air_attack) {
  COROUTINE_LOOP(){
    static int i = 0;
    for (i = 0; i < 4; i++) {
      digitalWrite(trigPins[i], LOW);
      COROUTINE_DELAY_MICROS(2);
      digitalWrite(trigPins[i], HIGH);
      COROUTINE_DELAY_MICROS(10);
      digitalWrite(trigPins[i], LOW);
      COROUTINE_DELAY_MICROS(500);
    }
  }
}

void loop() {
  //foot.runCoroutine();
  //kick.runCoroutine();
  air_attack.runCoroutine();
  move.runCoroutine();
}

