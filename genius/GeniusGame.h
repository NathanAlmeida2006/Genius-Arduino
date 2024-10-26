#ifndef GENIUS_GAME_H
#define GENIUS_GAME_H

#include <Arduino.h>
#include "DynamicArray.h"

enum {
  NUM_LEDS = 4,
  NUM_BOTOES = 4
};

class GeniusGame {
private:
  const int buzzer = A0;
  int leds[NUM_LEDS] = {13, 12, 11, 10};
  int botoes[NUM_BOTOES] = {9, 8, 7, 6};
  const int tones[NUM_LEDS] = {261, 329, 392, 523};
  const int successTones[4] = {261, 294, 329, 349};
  const int failureTones[4] = {349, 329, 294, 261};
  DynamicArray sequence;
  int inputIndex;
  int score;

public:
  GeniusGame();
  void setup();
  void loop();
  void acendeLed(int ledIndex);
  void apagaLed(int ledIndex);
  int getButtonPressed();
  void playSuccessTone();
  void playFailureTone();
};

#endif