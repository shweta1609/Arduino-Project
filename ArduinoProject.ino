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
}

void loop() {

  lcd.setCursor(0,0);               //set the cursor to the 0,0 position (top left corner)
  lcd.print("Hello, world!");       //print hello, world! starting at that position

  lcd.setCursor(0,1);               //move the cursor to the first space of the bottom row
  if(digitalRead(redButton) == LOW){
    analogWrite(RedPin, 100);
    analogWrite(BluePin, 0);
    analogWrite(GreenPin,0);
    lcd.print(millis()/1000);         //print the number of seconds that have passed since the last reset
  }
  else if(digitalRead(blueButton) == LOW){
    lcd.print("blueeee");
    analogWrite(RedPin, 0);
    analogWrite(BluePin, 100);
    analogWrite(GreenPin,0);
    tone(buzzerPin, 130, 250);   //E6
    delay(275);
    tone(buzzerPin, 98, 500);   //C7
    delay(500);
    }
}  
