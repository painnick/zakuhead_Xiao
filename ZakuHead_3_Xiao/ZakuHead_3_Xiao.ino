#include  "Scenario.h"

#define LED_PIN   1
#define SERVO_PIN 5
#define SOUND_SENSOR_PIN 3

Scenario *scenario;

void setup() {
  scenario = new Scenario(LED_PIN, SERVO_PIN, SOUND_SENSOR_PIN);
  #ifdef USE_SERIAL
    Serial.begin(115200);
  #endif
  scenario->attach();
}

int loop_index = 0;

void loop() {
  if(loop_index == 0) {
    scenario->resetClapped();
    scenario->scenario1();
  }

  scenario->breathe1(1000, 100, 15, 195);
  if (scenario->isClapped()) {
    loop_index = 0;
  } else {
    if(scenario->waitUntilClapping(500)) {
      loop_index = 0;
    } else {
      analogWrite(LED_PIN, 127);
      if (scenario->waitUntilClapping(3000)) {
        loop_index = 0;
      } else {
        loop_index = (loop_index + 1) % 1000;
      }
    }
  }
}
