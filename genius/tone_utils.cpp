#include "tone_utils.h"
#include <Arduino.h> 

void playTone(int pin, int frequency, int duration) {
  tone(pin, frequency, duration);
}