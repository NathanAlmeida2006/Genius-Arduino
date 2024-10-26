#include "lcd_utils.h"

void initLCD(LiquidCrystal_I2C& lcd) {
  lcd.begin(16, 2);
  lcd.backlight();
}

void printLCD(LiquidCrystal_I2C& lcd, const char* text) {
  lcd.setCursor(0, 0);
  lcd.print(text);
}