#include <LiquidCrystal.h>

// Initialize the pins
LiquidCrystal lcd(8, 9, 5, 4, 3, 2);
const int switchPin = 6;
const int setPlayerPin = 7;
const int redLEDPin = 10;    // LED connected to digital pin 10
const int greenLEDPin = 11;     // LED connected to digital pin 11
const int blueLEDPin = 12;    // LED connected to digital pin 12

// Initialize the States
int switchState = 0;
int setPlayerState = 0;
int prevSetPlayerState = 0;
int prevSwitchState = 0;
int prevDoubleState = 0;
int doubleState = 0;

// Initialize the variables
int num1,num2;
int playerLed = 0;
int numOfPlayer = 3;
int redValue = 0; // value to write to the red LED
int greenValue = 0; // value to write to the green LED
int blueValue = 0; // value to write to the blue LED
unsigned long previousTime = 0;

// Helper methods
void scrollScreen();
void playerColor(int choice);

void setup() {
  // set the digital pins as inputs
  pinMode(switchPin, INPUT);
  pinMode(setPlayerPin, INPUT);
  // set the digital pins as outputs
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  // Screen Size
  lcd.begin(16, 2); 
  //-------- Write characters on the display ------------------
  // NOTE: Cursor Position: (CHAR, LINE) start at 0  
  lcd.print("Hello, world!");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(numOfPlayer);
  lcd.print(" players");
  delay(2000);
  lcd.clear();
  lcd.print("Let's ");
  lcd.print("begin!");
  delay(2000);
  scrollScreen();
}

void loop() {
    switchState = digitalRead(switchPin);
    setPlayerState = digitalRead(setPlayerPin);
    
    if(setPlayerState != prevSetPlayerState) {
      if(setPlayerState == LOW){
        numOfPlayer += 1;
          if(numOfPlayer == 6){
            numOfPlayer = 2;
        }
        lcd.clear();
        lcd.print(numOfPlayer);
        lcd.print(" Players");
      }
    }

    playerColor(playerLed);
    if(switchState != prevSwitchState) {
      if(switchState == LOW){
      previousTime = millis();
      analogWrite(redLEDPin, redValue);
      analogWrite(greenLEDPin, greenValue);
      analogWrite(blueLEDPin, blueValue);
      num1 = random(7)+ 1;
      num2 = random(2) + 1;
      lcd.clear();
      
      if(num1 != num2) {
        lcd.setCursor(0, 0);
        lcd.print("dice says:");
        lcd.setCursor(11, 0);
        lcd.print(num1);
        lcd.print("+");
        lcd.print(num2);
        lcd.setCursor(0, 1);
        lcd.print("move ");
        lcd.print(num1 + num2);
        doubleState = 0;
        prevDoubleState = 0;
        delay(500);
      } else {
        if(doubleState == prevDoubleState)
          doubleState += 1;
        
        if(doubleState == 2){ // Doubles three times
          lcd.setCursor(0, 0);
          lcd.print("Double x2");
          lcd.setCursor(0, 1);
          lcd.print("Jail Time! ");
          delay(2000);
          scrollScreen();
          doubleState = 0;
          prevDoubleState = 0;
        } else {
          lcd.setCursor(0, 0);
          lcd.print("Double!");
          lcd.setCursor(0, 1);
          lcd.print("Roll Again!");
          playerLed -= 1;
        }
      }
      delay(2000);
      playerLed += 1;
      if(playerLed == numOfPlayer){
        playerLed = 0;
      }
      playerColor(playerLed);
      analogWrite(redLEDPin, redValue);
      analogWrite(greenLEDPin, greenValue);
      analogWrite(blueLEDPin, blueValue);
      lcd.clear();
      lcd.print("dice says: ");
      lcd.print(num1 + num2);
      lcd.setCursor(0, 1);
      lcd.print("Ask again");
      }
    }
    // Record Previous State
    prevSetPlayerState = setPlayerState;
    prevSwitchState = switchState;
    prevDoubleState = doubleState;
}

void scrollScreen(){
  // scroll 13 positions (string length) to the left
  // to move it offscreen left:
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(125);
  }

  // scroll 29 positions (string length + display length) to the right
  // to move it offscreen right:
  for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    // scroll one position right:
    lcd.scrollDisplayRight();
    // wait a bit:
    delay(100);
  }

  // scroll 16 positions (display length + string length) to the left
  // to move it back to center:
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(125);
  }

  // delay at the end of the full loop:
  delay(500);
}

// Support 2 - 5 players
void playerColor(int choice){
      if(choice == 0){
          redValue = 0;
          greenValue = 222;
          blueValue = 222;
      }
      else if(choice == 1){
          redValue = 0;
          greenValue = 255;
          blueValue = 0;
      }
      else if(choice == 2){
          redValue = 255;
          greenValue = 0;
          blueValue = 0;
      }
      else if(choice == 3){
          redValue = 222;
          greenValue = 0;
          blueValue = 222;
      }
      else if(choice == 4){
          redValue = 150;
          greenValue = 150;
          blueValue = 80;
      }
}
