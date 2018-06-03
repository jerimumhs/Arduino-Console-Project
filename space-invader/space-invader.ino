/*
Space Invader type of game.  16X2 LCD set up into pins 2-7, 
buzzer on pin 9 and wiiNunchuk attached to A4 (data) and A5 (clock).

Difficulty select on start to set the rate at which the enemy moves.
WiiNunchuk analog used to move left and right, z button to shoot.
Game is to 10 points after which your time will be displayed.
Misses reduce ammo, if you run out of ammo it costs 1 point to reload,
if your score falls below zero you lose.

Much credit to Gabriel Bianconi for creating the ArduinoNunchuk 
library, I could have never made this project with out that.
http://www.gabrielbianconi.com/projects/arduinonunchuk/
*/

#include <LiquidCrystal.h>
#include <Wire.h>
#include <ArduinoNunchuk.h>

ArduinoNunchuk nunchuk = ArduinoNunchuk();
LiquidCrystal lcd(11, 9, 6, 5, 4, 3);

int posX = 90;
int x = 0;
int x2 = 7;
int prevx = 0;
int prevx2 = 0;
int prevPosX = 0;
int zState = 0;
int zLast = 0;
unsigned long previousMillis = 0;
unsigned long startMillis = 0;
unsigned long currentMillis = 0;
unsigned long time = 0;
unsigned long shotTime = 0;
long moveDelay;
long moveSpeed;
long shotDelay = 100;
int shot = 9;
int i = 0;
int j = 6;
int score = 0;
const int buzzer = 13;

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define  R1     0

int winMelody[] = {NOTE_C4,NOTE_B3,NOTE_G3,NOTE_C4,NOTE_B3,NOTE_E3,R1,NOTE_C3,NOTE_C3,NOTE_G3,NOTE_A6,NOTE_C7};
int winBeats[] = {16,16,16,8,8,16,32,16,16,16,8,8};
int winMaxCount = sizeof(winMelody) / 2;
int lossMelody[] = {NOTE_C8,R1,NOTE_G7,NOTE_C7,NOTE_B7,NOTE_E7,R1,NOTE_C8,R1,NOTE_G7,NOTE_A7,NOTE_C8};
int lossBeats[] = {16,16,16,8,8,16,32,16,16,16,8,8};
int lossMaxCount = sizeof(lossMelody) / 2;
long tempo = 10000;
int pause = 1000;
int restCount = 100;
int tone_ = 0;
int beat = 0;
long duration = 0;

byte enemy1[8] = {
  B00100,
  B01010,
  B10001,
  B10101,
  B10101,
  B01010,
  B10101,
  B10001,
};

byte enemy2[8] = {
  B00000,
  B00100,
  B01010,
  B10001,
  B01110,
  B10101,
  B00000,
  B00000,
};

byte enemy3[8] = {
  B00000,
  B00100,
  B01110,
  B01010,
  B01110,
  B10101,
  B00000,
  B00000,
};

byte gun[8] = {
  B00000,
  B00000,
  B00000,
  B00100,
  B01110,
  B01010,
  B01010,
  B11111,
};

byte gunShoot[8] = {
  B00100,
  B00100,
  B01010,
  B00100,
  B01110,
  B01010,
  B01010,
  B11111,
};

byte hitShot[8] = {
  B01010,
  B00000,
  B10001,
  B01010,
  B01010,
  B10001,
  B00000,
  B01010,
};

byte missShot[8] = {
  B01110,
  B10101,
  B10101,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
};

byte blank[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};

void setup(){
  lcd.begin(16,2);
  nunchuk.init();
  lcd.createChar(1, gun);
  lcd.createChar(2, gunShoot);
  lcd.createChar(3, hitShot);
  lcd.createChar(4, missShot);
  lcd.createChar(5, blank);
  lcd.createChar(6, enemy1);
  lcd.createChar(7, enemy2);
  lcd.createChar(8, enemy3);
  nunchuk.update();
  zState = nunchuk.zButton;
  while(zState == LOW){
      difficulty();
  }
  lcd.setCursor(x2,1);
  lcd.write(2);
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(x2,0);
  lcd.write(3);
  delay(250);
  lcd.clear();
  startMillis = millis();
}  

void loop(){
  if(score <= 4){
    moveSpeed = moveDelay;
    j = 6;
  }
  else if( score <= 7){
    moveSpeed = moveDelay / 2;
    j = 7;
  }
  else{
    moveSpeed = moveDelay / 4;
    j = 8;
  }
  nunchuk.update();
  currentMillis = millis();

  posX = nunchuk.analogX;
  if(posX < 60 && prevPosX > 60){
    x2--;
  }
  if(posX > 200 && prevPosX < 200){
    x2++;
  }
  x2 = constrain(x2, 0, 14);
  
  if(currentMillis - previousMillis > moveSpeed){
    i = random(0,2);
    if(i == 0){
      x--;
    }
    if(i == 1){
      x++;
    }
    previousMillis = currentMillis;
  }
  x = constrain(x, 0, 14);

  lcd.setCursor(prevx,0);
  lcd.write(5);
  lcd.setCursor(x,0);
  lcd.write(j);
  lcd.setCursor(prevx2, 1);
  lcd.write(5);
  lcd.setCursor(x2,1);
  lcd.write(1);
  lcd.setCursor(15, 0);
  lcd.print(score);
  lcd.setCursor(15, 1);
  lcd.print(shot);

  zState = nunchuk.zButton;
  if(zState != zLast && zState == HIGH){
    shotTime = currentMillis;
    lcd.setCursor(x2,1);
    lcd.write(2);
    if(x == x2 && currentMillis < shotTime + shotDelay){
      hit();
    }
    else{
      miss();
    }
  }
  zLast = zState;
  
  if(shot == 0){
    shot = 9;
    score--;
  }

  prevx = x;
  prevPosX = posX;
  prevx2 = x2;
  
  if(score > 9){
    time = currentMillis - startMillis;
    lcd.setCursor(0,0);
    lcd.print("    YOU WIN     ");
    lcd.setCursor(0,1);
    lcd.print("  ");
    lcd.print(time / 1000);
    lcd.print("  Seconds    ");
    playWin();
    delay(4000);
    score = 0;
    shot = 9;
    startMillis = millis();
    lcd.clear();
  }

  if(score < 0){
    lcd.setCursor(0,0);
    lcd.print("   GAME OVER    ");
    lcd.setCursor(0,1);
    lcd.print("   YOU LOSE!    ");
    playLoss();
    delay(4000);
    score = 0;
    shot = 9;
    startMillis = millis();
    lcd.clear();
  }    
}

void hit(){
  lcd.setCursor(x,0);
  lcd.write(3);
  tone(buzzer, 100, 90);
  delay(10);
  tone(buzzer, 250, 150);
  delay(333);
  score++;
  lcd.setCursor(x,0);
  lcd.write(5);
  x = random(0,15);
}
  
void miss(){
  tone(buzzer, 1000, 90);
  delay(10);
  tone(buzzer, 1250, 150);
  shot--;
  lcd.setCursor(x2,0);
  lcd.write(4);
  delay(50);
  lcd.setCursor(x2,0);
  lcd.write(5);
}  

void difficulty(){
  nunchuk.update();
  x2 = constrain(x2, 0, 15);
  lcd.setCursor(0,0);
  lcd.print("SLOW        FAST");

  posX = nunchuk.analogX;
  if(posX < 60 && prevPosX > 60){
    x2--;
  }
  if(posX > 200 && prevPosX < 200){
    x2++;
  }
  prevPosX = posX;
  lcd.setCursor(prevx2,1);
  lcd.write(5);
  lcd.setCursor(x2,1);
  lcd.write(1);
  
  prevx2 = x2;
  moveDelay = map(x2, 0, 15, 1600, 400);
  zState = nunchuk.zButton;
}

void playWin(){
  for(int i = 0; i < winMaxCount; i++){
    tone_ = winMelody[i];
    beat = winBeats[i];
    duration = beat * tempo;
    playTone();
    delayMicroseconds(pause);
  }
}

void playLoss(){
  for(int i = 0; i < lossMaxCount; i++){
    tone_ = lossMelody[i];
    beat = lossBeats[i];
    duration = beat * tempo;
    playTone();
    delayMicroseconds(pause);
  }
}

void playTone(){
  long elapsedTime = 0;
  if(tone_ > 0){
    while (elapsedTime < duration){
      digitalWrite(buzzer, HIGH);
      delayMicroseconds(tone_ / 2);
      digitalWrite(buzzer, LOW);
      delayMicroseconds(tone_ / 2);
      elapsedTime += (tone_);
    }
  }
  else{
    for(int j = 0; j < restCount; j++){
      delayMicroseconds(duration);
    }
  }
}
