import processing.serial.*;

Serial myPort;
String val;
String score = "0";
String timer = "0";
boolean text = true;
boolean intro = true;
void setup(){
  size(400, 300);
  print(Serial.list());
  String portName = Serial.list()[2];
  myPort = new Serial(this, portName, 9600);
  background(#ECF08A);
  strokeWeight(2);
  textSize(18);
  fill(0);
}

void draw(){
    if (myPort.available() > 0){  
//  Capture input from the serial port      
    val = myPort.readStringUntil('\n');
    if (val != null){
      background(#ECF08A);
      textAlign(LEFT);
      val = val.trim();
      println(val);
      String[] input = split(val,":");
      if(input[0].equals("Score") == true){
//  Update the score value 
        println(input[1]);
        score = input[1];
        text = false;
      }
      else if(input[0].equals("Time Elapsed") == true){
//  Update the time elapsed value 
        timer = input[1];
        text = false;
      }
      else{
//  If score and timer values are not there, it means game is not started yet and 
//  instruction text should be displayed        
        text = true;
      }
      if(text == false){
//  Display the score and time elapsed values on the screen
        textAlign(RIGHT);
        text("Score:"+score, 280,150);
        text("Timer:"+timer, 150,150);
      }
      else{
//  Display instruction message in the beginning        
        textAlign(LEFT);
        if(intro){
        text("Time Limit: 50 seconds", 80,60);
        text("Total number of rounds: 2", 80,80);
        text("Target Score: 30", 80,100);
        intro = false;
        }
        text(val, 80, 150);
      }
    }
  }
}
