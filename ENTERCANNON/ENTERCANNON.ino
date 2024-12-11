#include "Keyboard.h"

bool led_state = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  for (uint8_t i = 0; i < 5; i++){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
 
  Keyboard.begin();
}

void loop() {
  digitalWrite(LED_BUILTIN, !led_state);
  led_state = !led_state;

  Keyboard.press(KEY_RETURN);
  delay(10);
  Keyboard.releaseAll();
  delay(10);
}