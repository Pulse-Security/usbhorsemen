#include "Keyboard.h"

void setup() {
  delay(1000);
  Keyboard.begin();
}

void loop() {
  Keyboard.press(KEY_RETURN);
  delay(10);
  Keyboard.releaseAll();
  delay(10);
}
