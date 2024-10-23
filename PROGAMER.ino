#include <Mouse.h>

uint8_t modifier = 0;
uint8_t code = 0;
int loops = 0;
uint8_t mode = 0;

uint8_t modifiers[] = {
  MOUSE_RIGHT,
  MOUSE_MIDDLE,
  MOUSE_LEFT,
};

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  for (uint8_t i = 0; i < 8; i++){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
 
  randomSeed(analogRead(0));
 
  Mouse.begin();
}

void loop() {
  /* press buttons */
  for (uint8_t i = 0; i != 3; i++) {
    if (modifier & (1 << i)) {
      Mouse.press(modifiers[i]);
      delay(2);
    }
  }

  Mouse.move(random(-127, 127), random(-127, 127), random(-127, 127));
  /* release buttons */
  for (uint8_t i = 0; i != 3; i++) {
    if (modifier & (1 << i)) {
      Mouse.release(modifiers[i]);
      delay(2);
    }
  }

  loops++;
  modifier++;
  code++;

  if (loops == 65536) {
    for (int b = 0; b < 10000; b++)
      Mouse.move(-127, -127, 0);
  }
}
