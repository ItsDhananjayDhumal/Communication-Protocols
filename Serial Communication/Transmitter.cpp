#define CLOCK 500 //baud; bits sent per second

char message[] = "electronics";
#define TX_PIN 7
#define CLOCK_PIN 2
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  pinMode(TX_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);

  for(int byte_no = 0; byte_no < strlen(message); byte_no++){
    char byte = message[byte_no];
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(byte);
    lcd.setCursor(0,1);

    for(int bit_no = 0; bit_no < 8; bit_no++){
      bool bit = byte & (0x80 >> bit_no);
      digitalWrite(TX_PIN, bit);
      lcd.print(bit);
      digitalWrite(CLOCK_PIN, HIGH);
      delay(500/CLOCK);
      digitalWrite(CLOCK_PIN, LOW);
      delay(500/CLOCK);
    }
  }
}

void loop() {
}
