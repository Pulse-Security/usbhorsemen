#include "Keyboard.h"

uint8_t modifier = 0;
uint8_t code = 0;
int loops = 0;
uint8_t mode = 0;

uint8_t modifiers[] = {
  KEY_LEFT_CTRL,
  KEY_LEFT_SHIFT,
  KEY_LEFT_ALT,
  KEY_LEFT_GUI,
  KEY_RIGHT_CTRL,
  KEY_RIGHT_SHIFT,
  KEY_RIGHT_ALT,
  KEY_RIGHT_GUI
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
  Keyboard.begin();
}

void loop() {
  if (mode == 0) {  
    /* press modifiers */
    for (uint8_t i = 0; i != 8; i++) {
      if (modifier & (1 << i)) {
        Keyboard.press(modifiers[i]);
        delay(2);
      }
    }
  
    /* skip modifiers I guess */
    if (code == 128) {
      code = 136;
    }
    
    /* press and release key */
    Keyboard.press(code);  
    delay(10 + random(0, 10));
    Keyboard.release(code);
  
    /* release modifiers */
    for (uint8_t i = 0; i != 8; i++) {
      if (modifier & (1 << i)) {
        Keyboard.release(modifiers[i]);
        delay(2);
      }
    }
  } else {
    Keyboard.press(random(0,255));
    delay(2);
    Keyboard.press(random(0,255));
    delay(2);
    Keyboard.press(random(0,255));
    delay(10 + random(0,10));
    Keyboard.releaseAll();
  }    
  loops++;
  modifier++;
  code++;

  if (loops == 65536) {
    Keyboard.releaseAll();
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    loops = 0;
    if (mode == 0) {
      mode = 1;
    } else {
      mode = 0;
    }
  }
}
