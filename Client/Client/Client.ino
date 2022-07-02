#include <LiquidCrystal.h>
#include<string.h>

// setup LCD1
const int rs = 35, en1 = 36, d4 = 40, d5 = 41, d6 = 42, d7 =43;
// setup LCD1
const int  en2 = 37;
// setup LCD1
const int  en3 = 38;

//lcds initialization
LiquidCrystal lcd1(rs, en1, d4, d5, d6, d7);
LiquidCrystal lcd2(rs, en2, d4, d5, d6, d7);
LiquidCrystal lcd3(rs, en3, d4, d5, d6, d7);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd1.begin(20, 4);
  lcd1.clear();
  lcd1.setCursor(0, 0);
  lcd2.begin(20, 4);
  lcd2.clear();
  lcd2.setCursor(0, 0);
  lcd3.begin(20, 4);
  lcd3.clear();
  lcd3.setCursor(0, 0);
}

void loop() {
  // put your main code here, to run repeatedly:

}
