#include <LiquidCrystal.h>

#define RX_PIN 7
#define CLOCK_PIN 2

volatile int rx_int = 0;
volatile bool update_rx_bits = false;
volatile int zeroes = 0;

struct hash{
    char character;
    const char* morse_bits;
};

static hash hash_table[27] = {
    {'A', "10111000"}, 
    {'B', "111010101000"}, 
    {'C', "11101011101000"}, 
    {'D', "1110101000"}, 
    {'E', "1000"}, 
    {'F', "101011101000"}, 
    {'G', "111011101000"}, 
    {'H', "1010101000"}, 
    {'I', "101000"}, 
    {'J', "1011101110111000"}, 
    {'K', "111010111000"}, 
    {'L', "101110101000"}, 
    {'M', "1110111000"}, 
    {'N', "11101000"}, 
    {'O', "11101110111000"}, 
    {'P', "10111011101000"}, 
    {'Q', "1110111010111000"}, 
    {'R', "1011101000"}, 
    {'S', "10101000"}, 
    {'T', "111000"}, 
    {'U', "1010111000"}, 
    {'V', "101010111000"}, 
    {'W', "101110111000"}, 
    {'X', "11101010111000"}, 
    {'Y', "1110101110111000"}, 
    {'Z', "11101110101000"},
    {' ', "000"}
};

char rx_bit_string[16] = "";
char rx_message[16] = "";

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void lcd_setup(){
    lcd.begin(16, 2);
    lcd.setCursor(0, 1);
    lcd.clear();
}

void read_bit(){
    rx_int = digitalRead(RX_PIN);
    if (rx_int){
        zeroes = 0;
    }
    else{
        zeroes++;
    }
    Serial.println(zeroes);
    update_rx_bits = true;
}

void compile_string(){
    for (int j = 0; j < 27; ++j){
        if(!strcmp(rx_bit_string, hash_table[j].morse_bits)){
            lcd.clear();
            lcd.setCursor(0, 0);
            strncat(rx_message, (const char*)&hash_table[j].character, 1);
            lcd.print(rx_message);
            lcd.setCursor(0, 1);
            j = 27;
        }
        else if (j == 26){
            lcd.clear();
            lcd.setCursor(0, 0);
            strncat(rx_message, (const char*)&hash_table[j].character, 1);
            lcd.print(rx_message);
            lcd.setCursor(0, 1);            
        }
    }
    strncpy(rx_bit_string, "", 1);
}

void insert_space(){
    strncat(rx_message, " ", 1);
    strncpy(rx_bit_string, "", 1);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(rx_message);
    lcd.setCursor(0, 1);
}

void setup(){
    pinMode(CLOCK_PIN, INPUT);
    pinMode(RX_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(CLOCK_PIN), read_bit, FALLING);
    Serial.begin(9600);
    lcd_setup();
}

void loop(){
    if (update_rx_bits){
        if (rx_int){
            strncat(rx_bit_string, "1", 1);
            lcd.print("1");
        }else{
            strncat(rx_bit_string, "0", 1);
            lcd.print("0");
        }

        if (zeroes == 3){
            compile_string();
        }
        if (zeroes == 7){
            insert_space();
        }
        update_rx_bits = false;
    }
}
