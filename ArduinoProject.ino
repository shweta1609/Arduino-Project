/*
SparkFun Inventor’s Kit
Circuit 4A-HelloWorld

The LCD will display the words "Hello World" and show how many seconds have passed since
the RedBoard was last reset.

This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
This code is completely free for any use.

View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v40
Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

#include <LiquidCrystal.h>          //the liquid crystal library contains commands for printing to the display

int buzzerPin = 5;
int redButton = 6;
int blueButton = 7;
int RedPin = 2;
int GreenPin = 3;
int BluePin = 4;
int col = 0;
char slider = '_';
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); 
// tell the RedBoard what pins are connected to the display
int tones[] = {262, 330, 392, 494};
void setup() {                     

  lcd.begin(16, 2);                 //tell the lcd library that we are using a display that is 16 characters wide and 2 characters high
  lcd.clear();  
  //clear the display
  Serial.begin(9600);
  pinMode(redButton,INPUT_PULLUP);
  pinMode(blueButton,INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(RedPin,OUTPUT);
  pinMode(BluePin,OUTPUT);
  lcd.setCursor(0,1);               //set the cursor to the 0,1 position (top left corner)
  lcd.print(slider);
}

void loop() {

//  lcd.setCursor(0,1);               //move the cursor to the first space of the bottom row
  if(digitalRead(redButton) == LOW){ //move right
    lcd.clear();
    if(col < 15)
      col += 1;
    lcd.setCursor(col,1);               //set the cursor to the 0,0 position (top left corner)
    lcd.print(slider);
    delay(150);
    analogWrite(RedPin, 200);
    analogWrite(BluePin, 0);
  }
  else if(digitalRead(blueButton) == LOW){ //move left
    lcd.clear();
    if(col > 0)
      col -= 1;
    lcd.setCursor(col,1);               //set the cursor to the 0,0 position (top left corner)
    lcd.print(slider);
    delay(150);
    analogWrite(RedPin, 100);
    analogWrite(BluePin, 200);
//    tone(buzzerPin, 130, 250);   //E6
//    delay(275);
//    tone(buzzerPin, 98, 500);   //C7
//    delay(500);
    }
}  
