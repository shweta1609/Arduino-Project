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

#include <LiquidCrystal.h>          

//Initializing the corresponding circuit connection pins for arduino to understand
int buzzerPin = 5;
int redButton = 6;
int blueButton = 7;
int RedPin = 2;
int GreenPin = 3;
int BluePin = 4;

//Intializing variables for the game 
int currCol = -1;
int newCol = 0;
bool randomGen = false;
bool start = false;
bool lose = false;
int sliderLen = 1;
int prev = 16;
int stage = 1;
long timeLimit = 25000;
long timeElapsed = 0;
long prevMillis = 0;
long dispTime = 3000;
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); 
// tell the RedBoard what pins are connected to the display
int tones[] = {262, 330, 392, 494}; 

//Initializing the bytes to illuminate one full block
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
//  Displaying message on screen to start the game
  lcd.setCursor(0,0);               //set the cursor to the 0,1 position (top left corner)
  lcd.print("Press any button");
  lcd.setCursor(3,1);
  lcd.print("to start");
  Serial.println("Press any button to start");
  initBlock();
}

void loop() {
//If the game is not started then display Green color in RGB LED
  if(!start){ 
    analogWrite(RedPin, 0);
    analogWrite(BluePin, 0);
    analogWrite(GreenPin, 200); 
    if((digitalRead(redButton) == LOW) or (digitalRead(blueButton) == LOW)){
//    Play small sound when game is starting
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
//    Check if game is over (i.e when 2 stages completed and stage variable has value 3)
    if(stage !=3){
      if(!lose){
//        If game is not lost, print time elapsed on serial to be sent to Processing
        Serial.print("Time Elapsed:");
        Serial.println(timeElapsed/1000);
      }
//      Capture the time elapsed
    timeElapsed = millis();
//    Check if stage 1 is completed
    if(sliderLen ==16 and stage==1){
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
//    Check if stage 2 is complete 
    else if(sliderLen == 16 and stage == 2){
//      Display that player won
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Congratulations! ");
      lcd.setCursor(3,1);
      lcd.print("You Won");
      delay(200);
      lose = false;
      Serial.println("Congratulations! You Won");
      stage += 1;
//      Play the win sequence melody
      winSequence();
    }
    else{
//      When game is in progress
    if(digitalRead(redButton) == LOW){ 
      //move right
      lcd.clear();
      if(currCol < 15)
        currCol += 1;
//        Change the position of the whole slider blocks
      for(int i=0; i<sliderLen; i++){
        lcd.setCursor(currCol+i,1);               //set the cursor to the 0,0 position (top left corner)
        lcd.write(byte(0));
        }
//        illuminate blue light when game is in progress
      analogWrite(RedPin, 0);
      analogWrite(BluePin, 200);
      analogWrite(GreenPin, 0);
      delay(150);
    }
    else if(digitalRead(blueButton) == LOW){ 
      //move left
      lcd.clear();
      if(currCol > 0)
        currCol -= 1;
      for(int i=0; i<sliderLen; i++){
        lcd.setCursor(currCol+i,1);               //set the cursor to the 0,0 position (top left corner)
        lcd.write(byte(0));
        }
      delay(150);
      //        illuminate blue light when game is in progress
      analogWrite(RedPin, 0);
      analogWrite(BluePin, 200);
      analogWrite(GreenPin, 0);
      }
      if(!randomGen and sliderLen<15){
        newCol = random(0,16);
        while((newCol == prev) or (newCol == prev+1)or (newCol == prev-1))
        newCol = random(0,16);
        prev = newCol;
        randomGen = true;
        prevMillis = timeElapsed;
       }
       if(stage == 2){
//          Hide the block after 3 seconds
         if((timeElapsed-prevMillis)< dispTime){
//          If time elapsed since block was displayed is less than 3 sec display the block
           lcd.setCursor(newCol,0);               
           lcd.write(byte(0));
         }
         else{
//          Otherwise, generate a new block
          prevMillis = timeElapsed;
          newCol = -1;
          randomGen = false;
         }
       }
       else{
//        Display the new block at a new position
          lcd.setCursor(newCol,0);               
          lcd.write(byte(0));
        }
//        Check if either end of slider reached the block
       if((newCol == currCol) or (newCol == (currCol+sliderLen-1))){
//        Increase the length of slider
        sliderLen += 1;
//        Update the score in Serial to be sent to processing
        Serial.print("Score:");
        if(stage == 1)
          Serial.println(sliderLen-1);
        else
          Serial.println(sliderLen+14);
//          Hide the block after adding it to slider
        lcd.setCursor(newCol,0);
        lcd.write("                ");
        randomGen = false;
        }
    }
//    Check if time is over
      if(timeElapsed >= 50000){
//        Display that game is over
        lcd.clear();
        lcd.setCursor(3,0);
        lcd.print("Times Up!");
        lcd.setCursor(3,1);
        lcd.print("You lose!");
        analogWrite(RedPin, 200);
        analogWrite(BluePin, 0);
        analogWrite(GreenPin, 0);
        sliderLen = 1; 
        Serial.println("Times Up! You lose!");  
        lose = true; 
//        Play the sequence for losing the game
        loseSequence();
    }
  }
  }

}

//Sequence for losing game sound
void loseSequence() {
  
  //play the 1Up noise
  tone(buzzerPin, 130, 250);   //E6
  delay(275);
  tone(buzzerPin, 73, 250);   //G6
  delay(275);
  tone(buzzerPin, 65, 150);   //E7
  delay(175);
  tone(buzzerPin, 98, 500);   //C7
  delay(500);
}

//Sequence for winning game sound
void winSequence() {
  //play the 1Up noise
  tone(buzzerPin, 1318, 150);   //E6
  delay(175);
  tone(buzzerPin, 1567, 150);   //G6
  delay(175);
  tone(buzzerPin, 2637, 150);   //E7
  delay(175);
  tone(buzzerPin, 2093, 150);   //C7
  delay(175);
  tone(buzzerPin, 2349, 150);   //D7
  delay(175);
  tone(buzzerPin, 3135, 500);   //G7
  delay(500);
}
