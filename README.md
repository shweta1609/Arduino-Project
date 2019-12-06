# Arduino-Project

This is a basic arduino game which has 2 stages with goal to achieve 30 points in a total of 50 seconds.

____

## Hardware components:

1. 16x2 LCD (Pins 14a-30a)
2. RGB LED (Pins 22f-25f)
3. 330 ohm resistors (for each color pin in LED)
4. Two Buttons (Pins {7d-9d-7g-9g}, {12d-14d-12g-14g})
5. Buzzer (1f-3f)
6. Potentiometer
7. Jumper wires


## Software Work:

All the game logic was written in Arduino and the scores and timer display were coded and displayed in Processing.

### Arduino

1. Displaying message on screen to start the game
2. Start the timer
3. Display a new block to catch
4. Use buttons to move the slider-block to reach the new block
5. When the score reaches 15, stage 1 is completed
6. Stage two has additional difficulty, the new block generated gets disappeared in 3 seconds.
7. Reach the new block as fast as possible
8. If total score reaches 30 before 50 seconds, player wins otherwise game over.


### Processing

1. Display the instructions for game in the beginning
2. As the game starts, read the score and timer value from the serial and display on the screen
3. If the game is over, display the appropriate win or lose message.

_____

## Usage
1. Connect the circuit as displayed in the circuit diagram
2. Connect the USB cable to the system
3. Upload the arduino code the the circuit board
4. Run the processing code
5. Play the game.

