#define RX_PIN 7
#define CLOCK_PIN 2

#include <LiquidCrystal.h>

char message[16];

volatile int i = 0;
volatile byte rx = 0x00;
volatile bool update = false;
volatile int rx_reading;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void readBit(){
  update = true;
  rx_reading = digitalRead(RX_PIN);
  if(rx_reading == 1){
    rx |= (0x80 >> i);
  }
  i++;
}


void setup() {
  lcd.begin(16, 2);
  pinMode(RX_PIN, INPUT);
  pinMode(CLOCK_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(CLOCK_PIN), readBit, RISING);
  lcd.clear();
  lcd.setCursor(0, 1);
}

void loop() {
  if (update){
    update = false;
    lcd.print(rx_reading);
  }
  if (i == 8){
    i = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    char c = static_cast<char>(rx);
    strncat(message, &c, 1);
    lcd.print(message);
    rx = 0x00;
    lcd.setCursor(0,1);
  }
}
