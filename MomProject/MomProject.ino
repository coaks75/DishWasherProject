#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


// These 2 constants are for the pin number of the input from the button and the output for the buttons lights
const int button = 2;
const int buttonLight = 7;

// These 2 variables are for the state of the button
boolean lastButton = LOW;
boolean currentButton = LOW;

// The index here is used to know what to print
int index = -1;

// Number of prints is to know when to reset our indexx
const int numOfPrints = 3;

// These 3 variables all are for timing, whether its timing the washer or if its timing our blink.
unsigned long previousMillis = 0;
unsigned long previousBlink = 0;
unsigned long currentMillis = 0;

// These variables are for how long the dish washing cycle is and if it is currently running
long washMinutes = 1;
boolean washing = false;

// This variable is just for how long of an interval to blink when the dishes are clean
int blinkTime = 200;

// Might delete these. Stay tuned folks
boolean blinking = false;
boolean hasBlinked = false;
boolean changed = false;



void setup() {
  // put your setup code here, to run once:

  lcd.begin(16, 2);
  lcd.clear();
  pinMode(button, INPUT);
  pinMode(buttonLight, OUTPUT);
  washMinutes = washMinutes * 60000;
  
}

/*
 * Debouncing method.
 * Checks whether or not the button state has changed and takes 
 *    button bouncing into account.
 */
boolean debounce(boolean last) {
  boolean current = digitalRead(button);
  if (last != current) {
    delay(5);
    current = digitalRead(button);
  }
  return current;
}

void loop() {
  // put your main code here, to run repeatedly:

  currentMillis = millis();
  currentButton = debounce(lastButton);

  if ((lastButton == LOW && currentButton == HIGH) || (washing == true && currentMillis - previousMillis >= washMinutes)) {
    index++;
    washing = false;
    if (index >= numOfPrints) {
      index = 0;
    }
    switch (index) {
      case 0:
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("Dishwasher is");
        lcd.setCursor(4,1);
        lcd.print("dirty");
        break;
      case 1:
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("Dishwasher is");
        lcd.setCursor(4,1);
        lcd.print("running");
        washing = true;
        previousMillis = currentMillis;
        break;
      case 2:
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("Dishwasher is");
        lcd.setCursor(0,1);
        lcd.print("clean, empty it");
        break;
    }
  }
  
  if (currentButton == HIGH) {
    digitalWrite(buttonLight, HIGH);
  }
  else {
    digitalWrite(buttonLight, LOW);
  }
  lastButton = currentButton;
    
}
  
