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
int currCol = -1;
int newCol = 0;
bool randomGen = false;
bool start = false;
int sliderLen = 1;
int prev = 16;
int stage = 1;
int timeLimit = 25000;
int timeElapsed = 0;
int prevMillis = 0;
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); 
// tell the RedBoard what pins are connected to the display
int tones[] = {262, 330, 392, 494};

void initBlock(){
  byte Block[8] =
  {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
  };
  lcd.createChar(0,Block);
}

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
  lcd.setCursor(0,0);               //set the cursor to the 0,1 position (top left corner)
  lcd.print("Press any button");
  lcd.setCursor(3,1);
  lcd.print("to start");
  initBlock();
}

void loop() {
//  lcd.clear();
  if(!start){  
    if((digitalRead(redButton) == LOW) or (digitalRead(blueButton) == LOW)){
      start = true;
      tone(buzzerPin, 130, 250);   //E6
      delay(275);
      tone(buzzerPin, 98, 500);   //C7
      delay(500);
      lcd.clear();
      timeElapsed = millis();
    }
  }
 
  else{
    timeElapsed = millis();
    prevMillis = timeElapsed;
    Serial.print("Timer: ");
    Serial.println(timeElapsed);
    if(sliderLen ==16){
      lcd.clear();
      sliderLen = 1;
      lcd.setCursor(0,0);
      lcd.print("Stage Complete");
      lcd.setCursor(3,1);
      lcd.print("Continue?");
      delay(200);
      start = false;
      stage += 1;
    }
    else{
    if(digitalRead(redButton) == LOW){ //move right
      lcd.clear();
      if(currCol < 15)
        currCol += 1;
      for(int i=0; i<sliderLen; i++){
        lcd.setCursor(currCol+i,1);               //set the cursor to the 0,0 position (top left corner)
        lcd.write(byte(0));
        }
      
      delay(150);
      analogWrite(RedPin, 200);
      analogWrite(BluePin, 0);
    }
    else if(digitalRead(blueButton) == LOW){ //move left
      lcd.clear();
      if(currCol > 0)
        currCol -= 1;
      for(int i=0; i<sliderLen; i++){
        lcd.setCursor(currCol+i,1);               //set the cursor to the 0,0 position (top left corner)
        lcd.write(byte(0));
        }
      delay(150);
      analogWrite(RedPin, 100);
      analogWrite(BluePin, 200);
      }
      if(!randomGen and sliderLen<15){
        newCol = random(0,16);
        while((newCol == prev) or (newCol == prev+1)or (newCol == prev-1))
        newCol = random(0,16);
        prev = newCol;
        Serial.print("Random Number:");
        Serial.println(newCol);
        randomGen = true;
       }
       
       lcd.setCursor(newCol,0);               
       lcd.write(byte(0));

       if((newCol == currCol) or (newCol == (currCol+sliderLen-1))){
        sliderLen += 1;
        Serial.print("Score:");
        Serial.println(sliderLen);
        lcd.setCursor(newCol,0);
        lcd.write("                ");
        randomGen = false;
        }
    }
      if(timeElapsed >= timeLimit){
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("Times Up!");
        lcd.setCursor(3,1);
        lcd.print("You lose!");
        timeElapsed = 0;
        sliderLen = 0;
        start = false;
        sliderLen = 1;
    }
  }

}  
