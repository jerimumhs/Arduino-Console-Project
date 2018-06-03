#include <LiquidCrystal.h>
volatile int level;
volatile int auxLevel;
volatile int podmenu;
#define PIN_BUTTON 2
#define PIN_AUTOPLAY 8
#define PIN_READWRITE 10
#define PIN_CONTRAST 12

#define SPRITE_RUN1 1
#define SPRITE_RUN2 2
#define SPRITE_JUMP 3
#define SPRITE_JUMP_UPPER '.'         // Use o '.' para a cabeca do personagem
#define SPRITE_JUMP_LOWER 4
#define SPRITE_TERRAIN_EMPTY ' '      // Use ' ' para corpo do personagem
#define SPRITE_TERRAIN_SOLID 5
#define SPRITE_TERRAIN_SOLID_RIGHT 6
#define SPRITE_TERRAIN_SOLID_LEFT 7

#define HERO_HORIZONTAL_POSITION 1    // Posição horizontal do personagem na tela

#define TERRAIN_WIDTH 16
#define TERRAIN_EMPTY 0
#define TERRAIN_LOWER_BLOCK 1
#define TERRAIN_UPPER_BLOCK 2

#define HERO_POSITION_OFF 0          // Personanagem Visivel
#define HERO_POSITION_RUN_LOWER_1 1  // Personagem correndo nos leds da fila inferior (pose 1)
#define HERO_POSITION_RUN_LOWER_2 2  //                                                (pose 2)

#define HERO_POSITION_JUMP_1 3       // Començando um salto
#define HERO_POSITION_JUMP_2 4       // Meio do caminho
#define HERO_POSITION_JUMP_3 5       // Salto nos Leds da fila superior
#define HERO_POSITION_JUMP_4 6       // Salto nos Leds da fila superior
#define HERO_POSITION_JUMP_5 7       // Salto nos Leds da fila superior
#define HERO_POSITION_JUMP_6 8       // Salto nos Leds da fila superior
#define HERO_POSITION_JUMP_7 9       // Meio do caminho
#define HERO_POSITION_JUMP_8 10      // Prestes a ir ao chao

#define HERO_POSITION_RUN_UPPER_1 11 // Personagem correndo nos leds da fila superior (pose 1)
#define HERO_POSITION_RUN_UPPER_2 12 //                                               (pose 2)

LiquidCrystal lcd(12, 11, 6, 5, 4, 3);
static char terrainUpper[TERRAIN_WIDTH + 1];
static char terrainLower[TERRAIN_WIDTH + 1];
static bool buttonPushed = false;
char wybor;
char wyborpoz;

void initializeGraphics(){
  static byte graphics[] = {
    // Posicao de corrida 1
    B01100,
    B01100,
    B00000,
    B01110,
    B11100,
    B01100,
    B11010,
    B10011,
    // Posicao de corrida 1 2
    B01100,
    B01100,
    B00000,
    B01100,
    B01100,
    B01100,
    B01100,
    B01110,
    // Salto
    B01100,
    B01100,
    B00000,
    B11110,
    B01101,
    B11111,
    B10000,
    B00000,
    // Salto baixo
    B11110,
    B01101,
    B11111,
    B10000,
    B00000,
    B00000,
    B00000,
    B00000,
    // Chao
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    // Chao a direita
    B00011,
    B00011,
    B00011,
    B00011,
    B00011,
    B00011,
    B00011,
    B00011,
    // Chao a esquerda
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
    B11000,
  };
  int i;
  // Permite que o lcd.print () seja usado para
  // desenhar rapidamente vários caracteres
  for (i = 0; i < 7; ++i) {
    lcd.createChar(i + 1, &graphics[i * 8]);
  }
  for (i = 0; i < TERRAIN_WIDTH; ++i) {
    terrainUpper[i] = SPRITE_TERRAIN_EMPTY;
    terrainLower[i] = SPRITE_TERRAIN_EMPTY;
  }
}

// Desliza o terreno para a esquerda em incrementos de meio-caractere

void advanceTerrain(char* terrain, byte newTerrain){
  for (int i = 0; i < TERRAIN_WIDTH; ++i) {
    char current = terrain[i];
    char next = (i == TERRAIN_WIDTH-1) ? newTerrain : terrain[i+1];
    switch (current){
      case SPRITE_TERRAIN_EMPTY:
        terrain[i] = (next == SPRITE_TERRAIN_SOLID) ? SPRITE_TERRAIN_SOLID_RIGHT : SPRITE_TERRAIN_EMPTY;
        break;
      case SPRITE_TERRAIN_SOLID:
        terrain[i] = (next == SPRITE_TERRAIN_EMPTY) ? SPRITE_TERRAIN_SOLID_LEFT : SPRITE_TERRAIN_SOLID;
        break;
      case SPRITE_TERRAIN_SOLID_RIGHT:
        terrain[i] = SPRITE_TERRAIN_SOLID;
        break;
      case SPRITE_TERRAIN_SOLID_LEFT:
        terrain[i] = SPRITE_TERRAIN_EMPTY;
        break;
    }
  }
}
void gl (int czas, int glos){

tone(3, glos);
delay(czas);
noTone(3);
}


bool drawHero(byte position, char* terrainUpper, char* terrainLower, unsigned int score) {
  bool collide = false;
  char upperSave = terrainUpper[HERO_HORIZONTAL_POSITION];
  char lowerSave = terrainLower[HERO_HORIZONTAL_POSITION];
  byte upper, lower;
  switch (position) {
    case HERO_POSITION_OFF:
      upper = lower = SPRITE_TERRAIN_EMPTY;
      break;
    case HERO_POSITION_RUN_LOWER_1:
      upper = SPRITE_TERRAIN_EMPTY;
      lower = SPRITE_RUN1;
      break;
    case HERO_POSITION_RUN_LOWER_2:
      upper = SPRITE_TERRAIN_EMPTY;
      lower = SPRITE_RUN2;
      break;
    case HERO_POSITION_JUMP_1:
    case HERO_POSITION_JUMP_8:
      upper = SPRITE_TERRAIN_EMPTY;
      lower = SPRITE_JUMP;
      break;
    case HERO_POSITION_JUMP_2:
    case HERO_POSITION_JUMP_7:
      upper = SPRITE_JUMP_UPPER;
      lower = SPRITE_JUMP_LOWER;
      break;
    case HERO_POSITION_JUMP_3:
    case HERO_POSITION_JUMP_4:
    case HERO_POSITION_JUMP_5:
    case HERO_POSITION_JUMP_6:
      upper = SPRITE_JUMP;
      lower = SPRITE_TERRAIN_EMPTY;
      break;
    case HERO_POSITION_RUN_UPPER_1:
      upper = SPRITE_RUN1;
      lower = SPRITE_TERRAIN_EMPTY;
      break;
    case HERO_POSITION_RUN_UPPER_2:
      upper = SPRITE_RUN2;
      lower = SPRITE_TERRAIN_EMPTY;
      break;
  }
  if (upper != ' ') {
    terrainUpper[HERO_HORIZONTAL_POSITION] = upper;
    collide = (upperSave == SPRITE_TERRAIN_EMPTY) ? false : true;
  }
  if (lower != ' ') {
    terrainLower[HERO_HORIZONTAL_POSITION] = lower;
    collide |= (lowerSave == SPRITE_TERRAIN_EMPTY) ? false : true;
  }
  
  byte digits = (score > 9999) ? 5 : (score > 999) ? 4 : (score > 99) ? 3 : (score > 9) ? 2 : 1;
  
  // desenha o cenario
  terrainUpper[TERRAIN_WIDTH] = '\0';
  terrainLower[TERRAIN_WIDTH] = '\0';
  char temp = terrainUpper[16-digits];
  terrainUpper[16-digits] = '\0';
  lcd.setCursor(0,0);
  lcd.print(terrainUpper);
  terrainUpper[16-digits] = temp;  
  lcd.setCursor(0,1);
  lcd.print(terrainLower);
  
  lcd.setCursor(16 - digits,0);
  lcd.print(score);

  terrainUpper[HERO_HORIZONTAL_POSITION] = upperSave;
  terrainLower[HERO_HORIZONTAL_POSITION] = lowerSave;
  return collide;
}

void buttonPush() {
  buttonPushed = true;
}

//Menu do jogo
void presentation(){
  lcd.setCursor(0,0);
  lcd.print("  JUMPMAN O ");
  lcd.setCursor(2,4);
  lcd.print("  GAME (|)");
  gl(100,400);
  gl(100,300);
  gl(100,200);
  gl(100,300);
  gl(100,400);
  gl(100,600);
  delay(5000);
  lcd.clear();
  
}  

void gameRules(int poziomgry){
  static byte heroPos = HERO_POSITION_RUN_LOWER_1;
  static byte newTerrainType = TERRAIN_EMPTY;
  static byte newTerrainDuration = 1;
  static bool playing = false;
  static bool blink = false;
  static unsigned int distance = 0;
  if (!playing) {
    drawHero((blink) ? HERO_POSITION_OFF : heroPos, terrainUpper, terrainLower, distance >> 3);
    if (blink) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Press  JUMP");
    }
    delay(250);
    blink = !blink;
    if (buttonPushed) {
      gl(100,400);
      gl(100,600);
      gl(100,400);
      initializeGraphics();
      heroPos = HERO_POSITION_RUN_LOWER_1;
      playing = true;
      buttonPushed = false;
      distance = 0;
      
    }
    return;
  }

  // Muda o terreno para a esquerda
  advanceTerrain(terrainLower, newTerrainType == TERRAIN_LOWER_BLOCK ? SPRITE_TERRAIN_SOLID : SPRITE_TERRAIN_EMPTY);
  advanceTerrain(terrainUpper, newTerrainType == TERRAIN_UPPER_BLOCK ? SPRITE_TERRAIN_SOLID : SPRITE_TERRAIN_EMPTY);
  
  // Faça um novo terreno para entrar à direita
  if (--newTerrainDuration == 0) {
    if (newTerrainType == TERRAIN_EMPTY) {
      newTerrainType = (random(3) == 0) ? TERRAIN_UPPER_BLOCK : TERRAIN_LOWER_BLOCK;
      newTerrainDuration = 2 + random(10);
    } else {
      newTerrainType = TERRAIN_EMPTY;
      newTerrainDuration = 10 + random(10);
    }
  }
    
  if (buttonPushed) {
    
    if (heroPos <= HERO_POSITION_RUN_LOWER_2)
    gl(100,300);
    heroPos = HERO_POSITION_JUMP_1;
    buttonPushed = false;
    
  }  
 // O personagem colidiu com alguma coisa. Game Over
  if (drawHero(heroPos, terrainUpper, terrainLower, distance >> 3)) {
    playing = false;
    gl(100,500);
    gl(100,400);
    gl(120,300);
    gl(160,400);
    lcd.clear();
  } else {
    if (heroPos == HERO_POSITION_RUN_LOWER_2 || heroPos == HERO_POSITION_JUMP_8) {
      heroPos = HERO_POSITION_RUN_LOWER_1;
    } else if ((heroPos >= HERO_POSITION_JUMP_3 && heroPos <= HERO_POSITION_JUMP_5) && terrainLower[HERO_HORIZONTAL_POSITION] != SPRITE_TERRAIN_EMPTY) {
      heroPos = HERO_POSITION_RUN_UPPER_1;
    } else if (heroPos >= HERO_POSITION_RUN_UPPER_1 && terrainLower[HERO_HORIZONTAL_POSITION] == SPRITE_TERRAIN_EMPTY) {
      heroPos = HERO_POSITION_JUMP_5;
    } else if (heroPos == HERO_POSITION_RUN_UPPER_2) {
      heroPos = HERO_POSITION_RUN_UPPER_1;
    } else {
      ++heroPos;
    }
    ++distance;
    
    digitalWrite(PIN_AUTOPLAY, terrainLower[HERO_HORIZONTAL_POSITION + 2] == SPRITE_TERRAIN_EMPTY ? HIGH : LOW);
  }
  delay(poziomgry);
  }

void setup(){
  pinMode(7, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  
  pinMode(PIN_READWRITE, OUTPUT);
  digitalWrite(PIN_READWRITE, LOW);
  pinMode(PIN_CONTRAST, OUTPUT);
  digitalWrite(PIN_CONTRAST, LOW);
  
  pinMode(PIN_BUTTON, INPUT);
  digitalWrite(PIN_BUTTON, HIGH);
  pinMode(PIN_AUTOPLAY, OUTPUT);
  digitalWrite(PIN_AUTOPLAY, HIGH);

  level = 1;
  attachInterrupt(0/*PIN_BUTTON*/, buttonPush, FALLING);
  
  initializeGraphics();
  
  lcd.begin(16, 2);
  presentation();
   do{menu();}while(digitalRead(2) == LOW);
}
//Executa infinitamente atpe que alguma regra seja quebrada
void loop() { 
switch (auxLevel) {
case 1:
gameRules(70);
break;
case 2:
gameRules(50);
break;
case 3:
gameRules(15);
break;
case 4:
gameRules(1);
break;
    }
  }
//Seleção de níveis
void menu() {
if (level > 4 || level < 0) {level == 0;}
if (digitalRead(7) == HIGH) { level++;}
  switch (level) {

    case 1:
    lcd.setCursor(0,0);
  lcd.print("Select mode:");
  lcd.setCursor(0,1);
  lcd.print("<     Easy     >");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Select mode:");
  lcd.setCursor(0,1);
  lcd.print("<              >");
  delay(500);
  if(digitalRead(2) == HIGH) {
    auxLevel = 1;
    auxLevel;}
  
  break;
    case 2:
lcd.setCursor(0,0);
  lcd.print("Select mode:");
  lcd.setCursor(0,1);
  lcd.print("<    Medium    >");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Select mode:");
  lcd.setCursor(0,1);
  lcd.print("<              >");
  delay(500);
if(digitalRead(2) == HIGH) {
    auxLevel = 2;
    auxLevel;}
    break;

    case 3:
lcd.setCursor(0,0);
  lcd.print("Select mode:");
  lcd.setCursor(0,1);
  lcd.print("<     Hard     >");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Select mode:");
  lcd.setCursor(0,1);
  lcd.print("<              >");
  delay(500);
  if(digitalRead(2) == HIGH) {
    auxLevel = 3;
    auxLevel;}

    break;
    case 4:
lcd.setCursor(0,0);
  lcd.print("Select mode:");
  lcd.setCursor(0,1);
  lcd.print("<    Ninja     >");
  delay(500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Select mode:");
  lcd.setCursor(0,1);
  lcd.print("<              >");
  delay(500);
  if(digitalRead(2) == HIGH) {
    auxLevel = 4;
    auxLevel;}
    break;
    
  default:
level = 0;
  break;
    }
  }
