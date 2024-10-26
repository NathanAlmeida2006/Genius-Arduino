#include "GeniusGame.h"

GeniusGame::GeniusGame() : inputIndex(0), score(0) {}

void GeniusGame::setup() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(leds[i], OUTPUT);
  }

  for (int i = 0; i < NUM_BOTOES; i++) {
    pinMode(botoes[i], INPUT_PULLUP);
  }

  pinMode(buzzer, OUTPUT);

  randomSeed(analogRead(0));
}

void GeniusGame::loop() {
  sequence.push_back(random(NUM_LEDS));

  for (int i = 0; i < sequence.size(); i++) {
    int delayTime = 500;
    acendeLed(sequence[i]);
    delay(delayTime);
    apagaLed(sequence[i]);
    delay(delayTime / 2);
  }

  inputIndex = 0;
  while (inputIndex < sequence.size()) {
    int buttonPressed = getButtonPressed();
    if (buttonPressed != -1) {
      if (buttonPressed == sequence[inputIndex]) {
        acendeLed(buttonPressed);
        delay(500);
        apagaLed(buttonPressed);
        inputIndex++;
      } else {
        playFailureTone();
        delay(1000);
        sequence.clear();
        score = 0;
        return;
      }
    }
  }

  score++;
  playSuccessTone();
  delay(1000);
}

void GeniusGame::acendeLed(int ledIndex) {
  if (ledIndex < 0 || ledIndex >= NUM_LEDS) return;
  digitalWrite(leds[ledIndex], HIGH);
  tone(buzzer, tones[ledIndex], 200);
}

void GeniusGame::apagaLed(int ledIndex) {
  if (ledIndex < 0 || ledIndex >= NUM_LEDS) return;
  digitalWrite(leds[ledIndex], LOW);
}

int GeniusGame::getButtonPressed() {
  for (int i = 0; i < NUM_BOTOES; i++) {
    if (digitalRead(botoes[i]) == LOW) {
      delay(50);
      if (digitalRead(botoes[i]) == LOW) {
        while (digitalRead(botoes[i]) == LOW);
        return i;
      }
    }
  }
  return -1;
}

void GeniusGame::playSuccessTone() {
  for (int i = 0; i < 4; i++) {
    tone(buzzer, successTones[i], 150);
    delay(150);
  }
}

void GeniusGame::playFailureTone() {
  for (int i = 0; i < 4; i++) {
    tone(buzzer, failureTones[i], 150);
    delay(150);
  }
}