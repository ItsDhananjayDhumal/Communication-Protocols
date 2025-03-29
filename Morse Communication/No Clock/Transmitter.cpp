#define DIT 100
int tx_pin = 2;

char message[] = "CAT DOG";

const char* letters[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..",
 "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

void dit(){
  digitalWrite(tx_pin, HIGH);
  delay(DIT);
  digitalWrite(tx_pin, LOW);
  delay(DIT);
}

void dah(){
  digitalWrite(tx_pin, HIGH);
  delay(3 * DIT);
  digitalWrite(tx_pin, LOW);
  delay(DIT);
}

void space(){
  delay(4 * DIT);
}

void pause(){
  delay(2 * DIT);
}

void setup() {
  pinMode(tx_pin, OUTPUT);
  Serial.begin(9600);

  for(int i = 0; i < strlen(message); i++){
    if(message[i] == ' '){
      space();
      Serial.print("   ");
    }
    else{
      for(int j = 0; j < strlen(letters[message[i] - 65]); j++){
        if(letters[message[i] - 65][j] == '.'){
          dit();
          Serial.print(".");
        }
        else{
          dah();
          Serial.print("_");
        }
      }
      pause();
      Serial.print(" ");
    }
  }
}

void loop() {
}
