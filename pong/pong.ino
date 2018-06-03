/*
   Jogo Pong com LCD

   
   Baseado no projeto de Ryan Brazeal:
   
   Created by: Ryan Brazeal of Junior Pi School  

   http://jrpi.ca/projects/lcd-pong-project
*/


// =============================================================================================================
// --- Declaração dos Caracteres Customizados ---


// =============================================================================================================
// -- Caracteres para a Parede --
byte wallA[8] = {
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011
};

byte wallB[8] = {
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011
};

// =============================================================================================================
// -- Caracteres para o Jogador --
byte paddle1[8] = {
  0b10000,
  0b10000,
  0b10000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

byte paddle2[8] = {
  0b00000,
  0b10000,
  0b10000,
  0b10000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

byte paddle3[8] = {
  0b00000,
  0b00000,
  0b10000,
  0b10000,
  0b10000,
  0b00000,
  0b00000,
  0b00000
};

byte paddle4[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b10000,
  0b10000,
  0b10000,
  0b00000,
  0b00000
};

byte paddle5[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10000,
  0b10000,
  0b10000,
  0b00000
};

byte paddle6[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10000,
  0b10000,
  0b10000
};

byte paddle7a[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10000,
  0b10000
};

byte paddle7b[8] = {
  0b10000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

byte paddle8a[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10000
};

byte paddle8b[8] = {
  0b10000,
  0b10000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

// =============================================================================================================
// -- Caracteres para a Bola --

// Row 1, Each Column
byte ball00[8] = {
  0b10000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000  
};

byte ball01[8] = {
  0b01000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000  
};

byte ball02[8] = {
  0b00100,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000  
};

byte ball03[8] = {
  0b00010,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000  
};

byte ball04[8] = {
  0b00001,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000  
};

// Row 2, Each Column
byte ball10[8] = {
  0b00000,
  0b10000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000  
};

byte ball11[8] = {
  0b00000,
  0b01000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000  
};

byte ball12[8] = {
  0b00000,
  0b00100,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000  
};

byte ball13[8] = {
  0b00000,
  0b00010,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000  
};

byte ball14[8] = {
  0b00000,
  0b00001,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000  
};

// Row 3, Each Column
byte ball20[8] = {
  0b00000,
  0b00000,
  0b10000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000  
};

byte ball21[8] = {
  0b00000,
  0b00000,
  0b01000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000  
};

byte ball22[8] = {
  0b00000,
  0b00000,
  0b00100,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000  
};

byte ball23[8] = {
  0b00000,
  0b00000,
  0b00010,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000  
};

byte ball24[8] = {
  0b00000,
  0b00000,
  0b00001,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000  
};

// Row 4, Each Column
byte ball30[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b10000,
  0b00000,
  0b00000,
  0b00000,
  0b00000  
};

byte ball31[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b01000,
  0b00000,
  0b00000,
  0b00000,
  0b00000  
};

byte ball32[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b00000,
  0b00000,
  0b00000,
  0b00000  
};

byte ball33[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00010,
  0b00000,
  0b00000,
  0b00000,
  0b00000  
};

byte ball34[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00001,
  0b00000,
  0b00000,
  0b00000,
  0b00000  
};

// Row 5, Each Column
byte ball40[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10000,
  0b00000,
  0b00000,
  0b00000  
};

byte ball41[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b01000,
  0b00000,
  0b00000,
  0b00000  
};

byte ball42[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b00000,
  0b00000,
  0b00000  
};

byte ball43[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00010,
  0b00000,
  0b00000,
  0b00000  
};

byte ball44[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00001,
  0b00000,
  0b00000,
  0b00000  
};

// Row 6, Each Column
byte ball50[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10000,
  0b00000,
  0b00000  
};

byte ball51[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b01000,
  0b00000,
  0b00000  
};

byte ball52[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b00000,
  0b00000  
};

byte ball53[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00010,
  0b00000,
  0b00000  
};

byte ball54[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00001,
  0b00000,
  0b00000  
};

// Row 7, Each Column
byte ball60[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10000,
  0b00000  
};

byte ball61[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b01000,
  0b00000  
};

byte ball62[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b00000  
};

byte ball63[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00010,
  0b00000  
};

byte ball64[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00001,
  0b00000  
};

// Row 8, Each Column
byte ball70[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b10000  
};

byte ball71[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b01000  
};

byte ball72[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00100  
};

byte ball73[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00010  
};

byte ball74[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00001  
};

/**********************************************************************************************************************************************************/

// =============================================================================================================
// --- Bibliotecas Auxiliares ---
#include <LiquidCrystal.h>   // LCD library

// =============================================================================================================
// --- Hardware do LCD ---
LiquidCrystal lcd (12,  //RS no digital 8
                   11,  //EN no digital 7
                   6,  //D4 no digital 5
                   5,  //D5 no digital 4
                   4,  //D6 no digital 3
                   3); //D7 no digital 2

// Arduino Pins
const int button = 2;                 // Push button (pulled low)
const int buzzer = 13;                // Piezo Buzzer

// Globals
int upDownDir;                        // Up/Down State of the Ball
int leftRightDir;                     // Left/Right State of the Ball 
int angle;                            // Angle with respect to the horizontal (X) axis the ball is travelling
int pontuacao = 0x00;
float azimuth;                        // Clockwise angle from the Vertical (Y) axis the ball is travelling
boolean gameStarted;                  // Game State
int paddlePos;                        // Position of the player's paddle (14 possible positions)
int ballPos[2];                       // X, Y coordinates of the bal
int points;                           // Keeps track of how many balls have passed the players boundary (game is to 3)
float distance;                       // Distance between successive positions of the ball
float totalDistance;                  // Total distance from the ball's last boundary deflection (control) point, this is used to properly calculate the ball's trajectory

// Game Control Variables (CHANGE TO SUIT YOUR DESIRE)
float speedIncreasePercent = 10;      // Speed increase percentage when the player successfully bounces the ball off their paddle
int gameAngleMin = 10;                // Min trajectory angle for the ball
int gameAngleMax = 50;                // Max trajectory angle for the ball
float initialDist = 1.0;              // Initial Distance value that is used at the start of a game (pick a bigger number for the ball to travel faster at the start)

void setup() {
  gameStarted = false;
  // set up the lcd's number of columns and rows: 
  lcd.begin(16, 2);
  
  // set button pin as input
  pinMode(button, INPUT);

  // set the Buzzer as output
  pinMode(buzzer, OUTPUT);

  // calculate an initial trajectory angle for the ball
  calcInitialDir();
  
  // set the ball's initial position to centre screen
  ballPos[0] = 39;
  ballPos[1] = 7;
  
  // initialize control variables to default values
  distance = initialDist;
  totalDistance = distance;
  points = 0;
  
  // display message for player to press the button to start the game
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Aperte o botao  ");
  lcd.setCursor(0,1);
  lcd.print("para iniciar");
}

void loop() {
  
  // check the game state
  if (gameStarted == true)    // Game is started
  {
    ballUpdate();                // Update the ball's position
    
    // Check if game to 3 has ended
    if (gameStarted == true) {
      playerPaddleUpdate();        // Update the player's paddle position
      
      // Check for button press to reset the game
      if (digitalRead(button) == HIGH) {
        delay(250);
        setup();
      }
    }
    delay(100);
  }
  else                        // Game has not started
  { 
    // Check for button press
    if (digitalRead(button) == HIGH)
    {
      // Start a game (toggle game state) and initialize the game board
      gameStarted = true;
      drawInitial();
    }
  }

  
}

// Function for drawing the initial state of the game board
void drawInitial() {
  lcd.clear();
      
  // Draw the pong Wall chars
  lcd.createChar(0, wallA); 
  lcd.setCursor(0,0);
  lcd.write((byte)0);
  lcd.createChar(1, wallB);
  lcd.setCursor(0,1);
  lcd.write(1);

  // Draw the ball in it's default starting position
  lcd.createChar(2, ball04);
  lcd.setCursor(7,1);
  lcd.write(2); 
  delay(250);
}

// Function for determining the ball's trajectory angle
void calcInitialDir() {
 // randomly get a 1 or -1 for the up/down and left/right directions and the ball's angle of travel from the X axis  
  upDownDir = 0;
  leftRightDir = 0;
  while (upDownDir == 0) {
    upDownDir = random(-1,2);
  }
  while (leftRightDir == 0) {
    leftRightDir = random(-1,2);
  }
  // Randomly grab a game angle between Min and Max values
  randomSeed(analogRead(1));
  angle = random(gameAngleMin,gameAngleMax + 1);

}

// Function for updating the player's paddle position based on the potentiometer's value
void playerPaddleUpdate() {
    // read the pot on A15 for paddle position
    int potReading = analogRead(15);
    // map and constrain the pot's value to represent one of the 14 possible paddle positions
    paddlePos = constrain(map(potReading, 0, 950, 1, 14), 1, 14);
    
    //clear the paddle
    lcd.setCursor(15,0);
    lcd.print(" ");
    lcd.setCursor(15,1);
    lcd.print(" ");
   
    //draw new paddle position using the correct custom LCD character(s)
    if (paddlePos == 1)
    {
      lcd.createChar(6, paddle6);
      lcd.setCursor(15,1);
      lcd.write(6);
    }
    else if (paddlePos == 2)
    {
      lcd.createChar(7, paddle5);
      lcd.setCursor(15,1);
      lcd.write(7);
    }
    else if (paddlePos == 3)
    {
      lcd.createChar(6, paddle4);
      lcd.setCursor(15,1);
      lcd.write(6);
    }
    else if (paddlePos == 4)
    {
      lcd.createChar(7, paddle3);
      lcd.setCursor(15,1);
      lcd.write(7);
    }
    else if (paddlePos == 5)
    {
      lcd.createChar(6, paddle2);
      lcd.setCursor(15,1);
      lcd.write(6);
    }
    else if (paddlePos == 6)
    {
      lcd.createChar(7, paddle1);
      lcd.setCursor(15,1);
      lcd.write(7);
    }
    else if (paddlePos == 7)
    {
      lcd.createChar(6, paddle8a);
      lcd.setCursor(15,0);
      lcd.write(6);
      lcd.createChar(7, paddle8b);
      lcd.setCursor(15,1);
      lcd.write(7);
    }
    else if (paddlePos == 8)
    {
      lcd.createChar(6, paddle7a);
      lcd.setCursor(15,0);
      lcd.write(6);
      lcd.createChar(7, paddle7b);
      lcd.setCursor(15,1);
      lcd.write(7);
    }
    else if (paddlePos == 9)
    {
      lcd.createChar(6, paddle6);
      lcd.setCursor(15,0);
      lcd.write(6);
    }
    else if (paddlePos == 10)
    {
      lcd.createChar(7, paddle5);
      lcd.setCursor(15,0);
      lcd.write(7);
    }
    else if (paddlePos == 11)
    {
      lcd.createChar(6, paddle4);
      lcd.setCursor(15,0);
      lcd.write(6);
    }
    else if (paddlePos == 12)
    {
      lcd.createChar(7, paddle3);
      lcd.setCursor(15,0);
      lcd.write(7);
    }
    else if (paddlePos == 13)
    {
      lcd.createChar(6, paddle2);
      lcd.setCursor(15,0);
      lcd.write(6);
    }
    else if (paddlePos == 14)
    {
      lcd.createChar(7, paddle1);
      lcd.setCursor(15,0);
      lcd.write(7);
    }
}

// Function for updating the ball's position on the LCD screen using one of 40 possible custom characters
void ballUpdate() {

  // Calculate the azimuth of the ball's game angle (trajectory angle)
  if (upDownDir == 1 && leftRightDir == -1)
  {
    azimuth = 90 - angle;
  }
  else if (upDownDir == -1 && leftRightDir == -1)
  {
    azimuth = 90 + angle;
  }
  else if (upDownDir == -1 && leftRightDir == 1)
  {
    azimuth = 270 - angle;
  }
  else
  {
    azimuth = 270 + angle;
  }
  // Convert degrees to radians
  azimuth = azimuth * PI / 180.0;
  
  // Solve for the ball's new position (uses the ball's last deflection point along with total distance to better display the true game angle)
  int newX = sin(azimuth) * totalDistance + (float)ballPos[0];
  int newY = cos(azimuth) * totalDistance + (float)ballPos[1]; 

  // Constrain the ball's position to be on the game board
  newX = constrain(newX, 5, 75);
  newY = constrain(newY, 0, 15);
  
  // Update the total distance between the ball and it's last deflection (bounce) point within the game 
  totalDistance = totalDistance + distance;  
  
  // Check if the ball has hit a top/bottom boundary and if so update it's Up/Down state value 
  if (newY == 0)      // Hit the Bottom
  {
    tone(buzzer, 3000, 10);
    upDownDir = 1;
    totalDistance = distance;
    ballPos[0] = newX;
    ballPos[1] = newY + 1;
  }
  else if (newY == 15)  // Hit the Top
  {
    tone(buzzer, 3000, 10);
    upDownDir = -1;
    totalDistance = distance;
    ballPos[0] = newX;
    ballPos[1] = newY - 1;
  } 
  
  // Check if the ball has hit a left/right boundary and if so update it's Left/Right state value
  if (newX == 5)      // Hit the Wall
  {
    tone(buzzer, 2000, 10);   

    
    pontuacao++;
    
    leftRightDir = -1;
    totalDistance = distance;
    ballPos[0] = newX + 1;
    ballPos[1] = newY;
  }
  else if (newX == 75)  // Hit the player's boundary
  {
    // Speed up the ball each time it hit's the player's paddle
    distance = (1.0 + speedIncreasePercent / 100.0) * distance;
    
    // Check to see if the player's paddle was in the correct paddle position to bounce the ball
    if (newY == 0 && (paddlePos == 1 || paddlePos == 2)) {
      hitPaddleUpdate(newX, newY);
    }
    else if (newY == 1 && (paddlePos == 1 || paddlePos == 2 || paddlePos == 3)) {
      hitPaddleUpdate(newX, newY);
    }
    else if (newY == 2 && (paddlePos == 1 || paddlePos == 2 || paddlePos == 3 || paddlePos == 4)) {
      hitPaddleUpdate(newX, newY);
    }
    else if (newY == 3 && (paddlePos == 1 || paddlePos == 2 || paddlePos == 3 || paddlePos == 4 || paddlePos == 5)) {
      hitPaddleUpdate(newX, newY);
    }
    else if (newY == 4 && (paddlePos == 2 || paddlePos == 3 || paddlePos == 4 || paddlePos == 5 || paddlePos == 6)) {
      hitPaddleUpdate(newX, newY);
    }
    else if (newY == 5 && (paddlePos == 3 || paddlePos == 4 || paddlePos == 5 || paddlePos == 6 || paddlePos == 7)) {
      hitPaddleUpdate(newX, newY);
    }
    else if (newY == 6 && (paddlePos == 4 || paddlePos == 5 || paddlePos == 6 || paddlePos == 7 || paddlePos == 8)) {
      hitPaddleUpdate(newX, newY);
    }
    else if (newY == 7 && (paddlePos == 5 || paddlePos == 6 || paddlePos == 7 || paddlePos == 8 || paddlePos == 9)) {
      hitPaddleUpdate(newX, newY);
    }
    else if (newY == 8 && (paddlePos == 6 || paddlePos == 7 || paddlePos == 8 || paddlePos == 9 || paddlePos == 10)) {
      hitPaddleUpdate(newX, newY);
    }
    else if (newY == 9 && (paddlePos == 7 || paddlePos == 8 || paddlePos == 9 || paddlePos == 10 || paddlePos == 11)) {
      hitPaddleUpdate(newX, newY);
    }
    else if (newY == 10 && (paddlePos == 8 || paddlePos == 9 || paddlePos == 10 || paddlePos == 11 || paddlePos == 12)) {
      hitPaddleUpdate(newX, newY);
    }
    else if (newY == 11 && (paddlePos == 9 || paddlePos == 10 || paddlePos == 11 || paddlePos == 12 || paddlePos == 13)) {
      hitPaddleUpdate(newX, newY);
    }
    else if (newY == 12 && (paddlePos == 10 || paddlePos == 11 || paddlePos == 12 || paddlePos == 13 || paddlePos == 14)) {
      hitPaddleUpdate(newX, newY);
    }
    else if (newY == 13 && (paddlePos == 11 || paddlePos == 12 || paddlePos == 13 || paddlePos == 14)) {
      hitPaddleUpdate(newX, newY);
    }
    else if (newY == 14 && (paddlePos == 12 || paddlePos == 13 || paddlePos == 14)) {
      hitPaddleUpdate(newX, newY);
    }
    else if (newY == 15 && (paddlePos == 13 || paddlePos == 14)) {
      hitPaddleUpdate(newX, newY);
    }
    // The ball has crossed the player's boundary
    else {
      // Play Uh-Oh tone
      tone(buzzer, 100);
      delay(500);
      noTone(buzzer);
      tone(buzzer, 55  );
      delay(500);
      noTone(buzzer);
      
      //Reset the ball's position and control variables for the next point
      ballPos[0] = 39;
      ballPos[1] = 7;
      totalDistance = distance;
      drawInitial();
      // Determine a new game angle for this point
      calcInitialDir();
      points++;
      
      // A point has been scored (by the computer), flash the LED(s)
      if (points == 1) {
        /*for (int i = 0; i < 5; i++) {
          digitalWrite(compPoint1, HIGH);
          delay(250);
          digitalWrite(compPoint1, LOW);
          delay(250);
        }
        digitalWrite(compPoint1, HIGH);*/
      }
      else if (points == 2) {
        /*for (int i = 0; i < 5; i++) {
          digitalWrite(compPoint2, HIGH);
          delay(250);
          digitalWrite(compPoint2, LOW);
          delay(250);
        }
        digitalWrite(compPoint2, HIGH);*/
      }
      // Game is over, 3 points have been scored by the computer, reset the LCD to display the Start Game message
      else if (points == 3) {
        /*gameStarted = false;
        
        // Display Game Over Message
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("      GAME      ");
        lcd.setCursor(0,1);
        lcd.print("      OVER      ");

        delay(2000);
        lcd.clear();
        delay(50);
        
        lcd.setCursor(0,0);
        lcd.print("Numero de pontos");

        lcd.setCursor(4,1);
        lcd.print(pontuacao);
        
        for (int i = 0; i < 5; i++) {
          digitalWrite(compPoint1, HIGH);
          digitalWrite(compPoint2, HIGH);
          digitalWrite(compPoint3, HIGH);
          delay(250);
          digitalWrite(compPoint1, LOW);
          digitalWrite(compPoint2, LOW);
          digitalWrite(compPoint3, LOW);
          delay(250);
        }
        digitalWrite(compPoint1, HIGH);
        digitalWrite(compPoint2, HIGH);
        digitalWrite(compPoint3, HIGH);
        pontuacao = 0x00;
        delay(250);*/
        
        // Call setup to start the game over
        setup();
      }
    }
  }
  
  // Check to make sure the Game is NOT over and then update the ball's LCD character
  if (gameStarted == true) {
  drawChars(newX, newY);
  }
}

// Function to perform necessary updates/events when the ball hits the player's paddle
void hitPaddleUpdate(int X, int Y) {
  tone(buzzer, 2500, 10);
  leftRightDir = 1;
  totalDistance = distance;
  ballPos[0] = X - 1;
  ballPos[1] = Y;
}

// Function to determine which one of the 40 possible custom LCD characters should be drawn (and where) on the LCD
void drawChars(int X, int Y) {
  int LCDrow;
  int LCDcol;
  
  // Determine which row of the LCD the ball's character is on
  if (Y <= 7) {
    LCDrow = 1;
  }
  else {
    LCDrow = 0;
  }
  
  //Determine which column of the LCD the ball's character is on
  if (X <= 4) {
    LCDcol = 0;
  }
  else if (X <= 9) {
    LCDcol = 1;
  }
  else if (X <= 14) {
    LCDcol = 2;
  }
  else if (X <= 19) {
    LCDcol = 3;
  }
  else if (X <= 24) {
    LCDcol = 4;
  }
  else if (X <= 29) {
    LCDcol = 5;
  }
  else if (X <= 34) {
    LCDcol = 6;
  }
  else if (X <= 39) {
    LCDcol = 7;
  }
  else if (X <= 44) {
    LCDcol = 8;
  }
  else if (X <= 49) {
    LCDcol = 9;
  }
  else if (X <= 54) {
    LCDcol = 10;
  }
  else if (X <= 59) {
    LCDcol = 11;
  }
  else if (X <= 64) {
    LCDcol = 12;
  }
  else if (X <= 69) {
    LCDcol = 13;
  }
  else if (X <= 74) {
    LCDcol = 14;
  }
  else {
    LCDcol = 15;
  }
  
  // Clear the LCD of the previous ball (but not the Wall and the player's paddle)
  lcd.setCursor(1,0);
  // 14 empty characters printed inbetween the Wall and the player's paddle
  lcd.print("              ");
  lcd.setCursor(1,1);
  lcd.print("              ");
  
  // Determine the ball's position (single pixel) within a single LCD character (i.e. within the 8x5 pixels that make up a single LCD character)
  int dx = X - 5 * LCDcol;    // Column position within the LCD character
  int dy;
  
  // Row position within the LCD character
  if (Y == 0 || Y == 8) {
    dy = 0;
  }
  else if (Y == 1 || Y == 9) {
    dy = 1;
  }
  else if (Y == 2 || Y == 10) {
    dy = 2;
  }
  else if (Y == 3 || Y == 11) {
    dy = 3;
  }
  else if (Y == 4 || Y == 12) {
    dy = 4;
  }
  else if (Y == 5 || Y == 13) {
    dy = 5;
  }
  else if (Y == 6 || Y == 14) {
    dy = 6;
  }
  else if (Y == 7 || Y == 15) {
    dy = 7;
  }

  // Select the correct custom character, of the 40 possible, and display it (in it's correct LCD column, row position)
  // Alternate assigning the custom characters to LCD custom character bytes 1,2,3,4,5
  if (dx == 0 && dy == 0) {
   lcd.createChar(2, ball70);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(2);
  }
  else if (dx == 1 && dy == 0) {
   lcd.createChar(2, ball71);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(2);
  }
  else if (dx == 2 && dy == 0) {
   lcd.createChar(2, ball72);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(2);
  }
  else if (dx == 3 && dy == 0) {
   lcd.createChar(2, ball73);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(2);
  }
  else if (dx == 4 && dy == 0) {
   lcd.createChar(2, ball74);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(2);
  }
  
  else if (dx == 0 && dy == 1) {
   lcd.createChar(3, ball60);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(3);
  }
  else if (dx == 1 && dy == 1) {
   lcd.createChar(3, ball61);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(3);
  }
  else if (dx == 2 && dy == 1) {
   lcd.createChar(3, ball62);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(3);
  }
  else if (dx == 3 && dy == 1) {
   lcd.createChar(3, ball63);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(3);
  }
  else if (dx == 4 && dy == 1) {
   lcd.createChar(3, ball64);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(3);
  }
  
  else if (dx == 0 && dy == 2) {
   lcd.createChar(4, ball50);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(4);
  }
  else if (dx == 1 && dy == 2) {
   lcd.createChar(4, ball51);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(4);
  }
  else if (dx == 2 && dy == 2) {
   lcd.createChar(4, ball52);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(4);
  }
  else if (dx == 3 && dy == 2) {
   lcd.createChar(4, ball53);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(4);
  }
  else if (dx == 4 && dy == 2) {
   lcd.createChar(4, ball54);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(4);
  }
  
  else if (dx == 0 && dy == 3) {
   lcd.createChar(5, ball40);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(5);
  }
  else if (dx == 1 && dy == 3) {
   lcd.createChar(5, ball41);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(5);
  }
  else if (dx == 2 && dy == 3) {
   lcd.createChar(5, ball42);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(5);
  }
  else if (dx == 3 && dy == 3) {
   lcd.createChar(5, ball43);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(5);
  }
  else if (dx == 4 && dy == 3) {
   lcd.createChar(5, ball44);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(5);
  }
  
  else if (dx == 0 && dy == 4) {
   lcd.createChar(2, ball30);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(2);
  }
  else if (dx == 1 && dy == 4) {
   lcd.createChar(2, ball31);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(2);
  }
  else if (dx == 2 && dy == 4) {
   lcd.createChar(2, ball32);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(2);
  }
  else if (dx == 3 && dy == 4) {
   lcd.createChar(2, ball33);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(2);
  }
  else if (dx == 4 && dy == 4) {
   lcd.createChar(2, ball34);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(2);
  }
  
  else if (dx == 0 && dy == 5) {
   lcd.createChar(3, ball20);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(3);
  }
  else if (dx == 1 && dy == 5) {
   lcd.createChar(3, ball21);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(3);
  }
  else if (dx == 2 && dy == 5) {
   lcd.createChar(3, ball22);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(3);
  }
  else if (dx == 3 && dy == 5) {
   lcd.createChar(3, ball23);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(3);
  }
  else if (dx == 4 && dy == 5) {
   lcd.createChar(3, ball24);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(3);
  }
  
  else if (dx == 0 && dy == 6) {
   lcd.createChar(4, ball10);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(4);
  }
  else if (dx == 1 && dy == 6) {
   lcd.createChar(4, ball11);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(4);
  }
  else if (dx == 2 && dy == 6) {
   lcd.createChar(4, ball12);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(4);
  }
  else if (dx == 3 && dy == 6) {
   lcd.createChar(4, ball13);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(4);
  }
  else if (dx == 4 && dy == 6) {
   lcd.createChar(4, ball14);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(4);
  }
  
  else if (dx == 0 && dy == 7) {
   lcd.createChar(5, ball00);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(5);
  }
  else if (dx == 1 && dy == 7) {
   lcd.createChar(5, ball01);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(5);
  }
  else if (dx == 2 && dy == 7) {
   lcd.createChar(5, ball02);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(5);
  }
  else if (dx == 3 && dy == 7) {
   lcd.createChar(5, ball03);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(5);
  }
  else if (dx == 4 && dy == 7) {
   lcd.createChar(5, ball04);
   lcd.setCursor(LCDcol, LCDrow);
   lcd.write(5);
  }
}
