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
    val = myPort.readStringUntil('\n');
    if (val != null){
      if(intro){
        background(#ECF08A);
        textAlign(CENTER);
        text("Time Limit: 45 seconds", 80,60);
        text("Total number of rounds: 2", 80,80);
        text("Target Score: 30", 80,100);
        delay(3500);
        //This is not printing. Need to look into it.
        intro = false;
      }
      background(#ECF08A);
      textAlign(LEFT);
      val = val.trim();
      println(val);
      String[] input = split(val,":");
      if(input[0].equals("Score") == true){
        println(input[1]);
        score = input[1];
        text = false;
      }
      else if(input[0].equals("Time Elapsed") == true){
        timer = input[1];
        text = false;
      }
      else{
        text = true;
      }
      if(text == false){
        textAlign(RIGHT);
        text("Score:"+score, 280,150);
        text("Timer:"+timer, 150,150);
      }
      else{
        textAlign(LEFT);
        text(val, 80, 150);
      }
    }
  }
}
