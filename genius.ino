#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define NUM_LEDS 4
#define NUM_BOTOES 4

const int leds[NUM_LEDS] = {13, 12, 11, 10};
const int botoes[NUM_BOTOES] = {9, 8, 7, 6};
const int buzzer = A0;

// Frequências dos tons para cada botão/LED
const int tones[NUM_LEDS] = {261, 329, 392, 523};  // C4, E4, G4, C5

// Frequências dos tons para as sequências de sucesso e falha
const int successTones[4] = {261, 294, 329, 349};  // C4, D4, E4, F4
const int failureTones[4] = {349, 329, 294, 261};  // F4, E4, D4, C4

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Endereço I2C 0x27, 16 colunas e 2 linhas

class DynamicArray {
private:
  int* data;
  int capacity;
  int length;

  void resize() {
    capacity *= 2;
    int* newData = new int[capacity];
    memcpy(newData, data, length * sizeof(int));
    delete[] data;
    data = newData;
  }

public:
  DynamicArray() : capacity(1), length(0) {
    data = new int[capacity];
  }

  ~DynamicArray() {
    delete[] data;
  }

  void push_back(int value) {
    if (length == capacity) {
      resize();
    }
    data[length++] = value;
  }

  int size() const {
    return length;
  }

  int operator[](int index) const {
    if (index < 0 || index >= length) {
      // Retorna um valor inválido em caso de índice fora dos limites
      return -1;
    }
    return data[index];
  }

  void clear() {
    delete[] data;
    data = new int[1];
    capacity = 1;
    length = 0;
  }
};

DynamicArray sequence;  // Sequência do jogo usando DynamicArray
int inputIndex = 0;  // Índice da entrada do jogador

void setup() {
  // Configurar os LEDs como saída
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(leds[i], OUTPUT);
  }
  
  // Configurar os botões como entrada com pull-up
  for (int i = 0; i < NUM_BOTOES; i++) {
    pinMode(botoes[i], INPUT_PULLUP);
  }
  
  // Configurar o buzzer como saída
  pinMode(buzzer, OUTPUT);

  // Inicializar o display LCD
  lcd.begin(16, 2);
  lcd.backlight(); 
  lcd.setCursor(0, 0);
  lcd.print("Genius Game");
  delay(2000);
  lcd.clear();
  
  randomSeed(analogRead(0));  // Inicializar a semente do gerador de números aleatórios
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Nova rodada!");
  delay(1000);
  lcd.clear();
  
  // Gerar o próximo passo da sequência
  sequence.push_back(random(NUM_LEDS));
  
  // Mostrar a sequência para o jogador
  for (int i = 0; i < sequence.size(); i++) {
    acendeLed(sequence[i]);
    delay(500);
    apagaLed(sequence[i]);
    delay(250);
  }

  // Esperar a entrada do jogador
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
        lcd.setCursor(0, 0);
        lcd.print("Game Over!");
        playFailureTone();
        delay(1000);
        lcd.clear();
        sequence.clear();  // Limpar a sequência
        return;
      }
    }
  }
  
  lcd.setCursor(0, 0);
  lcd.print("Correto!");
  playSuccessTone();
  delay(1000);
  lcd.clear();
  delay(1000);
}

void acendeLed(int ledIndex) {
  if (ledIndex < 0 || ledIndex >= NUM_LEDS) return;  // Verificação de segurança
  digitalWrite(leds[ledIndex], HIGH);
  tone(buzzer, tones[ledIndex], 200);
}

void apagaLed(int ledIndex) {
  if (ledIndex < 0 || ledIndex >= NUM_LEDS) return;  // Verificação de segurança
  digitalWrite(leds[ledIndex], LOW);
}

int getButtonPressed() {
  for (int i = 0; i < NUM_BOTOES; i++) {
    if (digitalRead(botoes[i]) == LOW) {
      delay(50);  // Debounce
      if (digitalRead(botoes[i]) == LOW) {
        while (digitalRead(botoes[i]) == LOW);  // Esperar o botão ser solto
        return i;
      }
    }
  }
  return -1;
}

void playSuccessTone() {
  for (int i = 0; i < 4; i++) {
    tone(buzzer, successTones[i], 150);
    delay(150);
  }
}

void playFailureTone() {
  for (int i = 0; i < 4; i++) {
    tone(buzzer, failureTones[i], 150);
    delay(150);
  }
}
