#include <LiquidCrystal.h>

// Space is literal space between 2 words of message, for example the space between CAT DOG
// Recess is the pause between 2 characters of morse translation, for expmple the pause between ._
// Pause is the pause between 2 characters of message, for example pause between C and A in CAT

#define CLK_PIN 7
#define TX_PIN 2

#define CLOCK 2         // clock frequency
#define PAUSE 3         // clock cycles in a pause
#define SPACE 7         // clock cycles in a space. space must be greater than pause, else comm will break.
#define RECESS 1        // clock cycles in a recess
#define DAH 3           // clock cycles for which dah is high
#define DIT 1           // clock cycles for which dit is high

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char message[] = "IA T";

const char* letters[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..",
 "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};


// PROTOCOL: WRITE ON RISING
//           READ ON FALLING


void lcd_setup(){
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(message);
    lcd.setCursor(0, 1);
}

void dit(){
    lcd.print(".");
    // write data
    digitalWrite(TX_PIN, HIGH);
    // pulse clock 3 times
    for(int i = 0; i < DIT; i++){
        // one clock cycle
        digitalWrite(CLK_PIN, HIGH);
        delay(500/CLOCK);
        digitalWrite(CLK_PIN, LOW);
        delay(500/CLOCK);
    }
    digitalWrite(TX_PIN, LOW);
}

void dah(){
    lcd.print("_");
    // write data
    digitalWrite(TX_PIN, HIGH);
    // pulse clock 3 times
    for(int i = 0; i < DAH; i++){
        // one clock cycle
        digitalWrite(CLK_PIN, HIGH);
        delay(500/CLOCK);
        digitalWrite(CLK_PIN, LOW);
        delay(500/CLOCK);
    }
    digitalWrite(TX_PIN, LOW);
}

void space(){
    lcd.print(" ");
    digitalWrite(TX_PIN, LOW);
    for(int i = 0; i < (SPACE - PAUSE - RECESS); i++){
        // one clock cycle
        digitalWrite(CLK_PIN, HIGH);
        delay(500/CLOCK);
        digitalWrite(CLK_PIN, LOW);
        delay(500/CLOCK);
    }
}

void pause() {
    digitalWrite(TX_PIN, LOW);
    for(int i = 0; i < (PAUSE - RECESS); i++){
        // one clock cycle
        digitalWrite(CLK_PIN, HIGH);
        delay(500/CLOCK);
        digitalWrite(CLK_PIN, LOW);
        delay(500/CLOCK);
    }
}

void recess(){
    digitalWrite(TX_PIN, LOW);
    for(int i = 0; i < RECESS; i++){
        // one clock cycle
        digitalWrite(CLK_PIN, HIGH);
        delay(500/CLOCK);
        digitalWrite(CLK_PIN, LOW);
        delay(500/CLOCK);
    }
}

void setup() {
    pinMode(CLK_PIN, OUTPUT);
    pinMode(TX_PIN, OUTPUT);
    lcd_setup();

    for(int i = 0; i < strlen(message); i++){
        if(message[i] == ' '){
            space();
        }
        else{
            for(int j = 0; j < strlen(letters[message[i] - 65]); j++){
                if(letters[message[i] - 65][j] == '.'){
                    dit();
                }
                else{
                    dah();
                }
                recess();
            }
            pause();
        }
    }
}

void loop() {}
