#ifndef LCD_UTILS_H
#define LCD_UTILS_H

#include <LiquidCrystal_I2C.h>

void initLCD(LiquidCrystal_I2C& lcd);
void printLCD(LiquidCrystal_I2C& lcd, const char* text);

#endif