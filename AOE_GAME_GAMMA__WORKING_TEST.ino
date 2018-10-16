// IMPORTANT: ELEGOO_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Elegoo_TFTLCD.h FOR SETUP.
//Technical support:goodtft@163.com

#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0xffE0
#define CYAN    0xffFF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define TFT_WIDTH   320
#define TFT_HEIGHT  240
const int16_t BACKGROUND_COLOR = BLACK;

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
//Elegoo_GFX gfx(TFT_WIDTH, TFT_HEIGHT);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Elegoo_TFTLCD tft;

void setup(void) {
  Serial.begin(9600);
  //Serial.println(F("TFT LCD test"));

#ifdef USE_Elegoo_SHIELD_PINOUT
  Serial.println(F("Using Elegoo 2.8\" TFT Arduino Shield Pinout"));
#else
  Serial.println(F("Using Elegoo 2.8\" TFT Breakout Board Pinout"));
#endif

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

  uint16_t identifier = tft.readID(); //MODIFIED
// uint16_t identifier = 0x9341;
  if (identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if (identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if (identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  } else if (identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if (identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if (identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if (identifier == 0x0101)
  {
    identifier = 0x9341;
    Serial.println(F("Found 0x9341 LCD driver"));
  } else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier = 0x9341;

  }

  tft.begin(identifier);

  tft.setRotation(1);

  gameFillScreen(BACKGROUND_COLOR);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);

  gameStart();
}

#ifdef __AVR__
#include <avr/pgmspace.h>
#elif defined(ESP8266)
#include <pgmspace.h>
#else
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#endif


//////////////////////////// OUR CODE STARTS HERE ////////////////////////////////////////////



const int16_t STUDENT_WIDTH = 32;
const int16_t STUDENT_HEIGHT = 24;
const uint8_t student[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xf0, 0x00, 0x06, 0x00, 0x18, 0x00, 0x0c, 0x00, 0x0c, 0x00,
  0x18, 0x00, 0x06, 0x00, 0x17, 0x73, 0x3a, 0x00, 0x34, 0x44, 0xa3, 0x00, 0x27, 0x67, 0xb9, 0x00,
  0x21, 0x44, 0x89, 0x80, 0x27, 0x74, 0xb9, 0x60, 0x20, 0x00, 0x01, 0x10, 0x10, 0x00, 0x06, 0x08,
  0x18, 0x00, 0x0c, 0x30, 0x1c, 0x00, 0xff, 0xc0, 0x1f, 0xff, 0xff, 0x00, 0x19, 0xd7, 0xd7, 0x00,
  0x09, 0xee, 0xef, 0x00, 0x0c, 0x7e, 0xff, 0x00, 0x0e, 0x3c, 0x36, 0x00, 0x0f, 0x83, 0x8e, 0x00,
  0x01, 0xe3, 0xbc, 0x00, 0x00, 0x7f, 0xf8, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const int16_t TEST_WIDTH = 40;
const int16_t TEST_HEIGHT = 40;
const uint8_t test[] PROGMEM = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8,
  0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00,
  0x00, 0x00, 0x1f, 0xf8, 0x28, 0x00, 0x7c, 0x1f, 0xf8, 0x28, 0x00, 0x82, 0x1f, 0xf8, 0x6c, 0x01,
  0x01, 0x1f, 0xf9, 0xc7, 0x02, 0x7c, 0x9f, 0xf8, 0x00, 0x02, 0x40, 0x9f, 0xf9, 0xc7, 0x02, 0x40,
  0x9f, 0xf8, 0x6c, 0x02, 0x78, 0x9f, 0xf8, 0x28, 0x02, 0x40, 0x9f, 0xf8, 0x28, 0x01, 0x41, 0x1f,
  0xf8, 0x00, 0x00, 0x82, 0x1f, 0xf8, 0x00, 0x00, 0x7c, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x1f, 0xf8,
  0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x1f, 0xc3, 0xf8, 0x1f, 0xf8, 0x05,
  0x00, 0xa0, 0x1f, 0xf8, 0x05, 0x00, 0xa0, 0x1f, 0xf8, 0x05, 0x00, 0xa0, 0x1f, 0xf8, 0x05, 0x18,
  0xa0, 0x1f, 0xf8, 0x05, 0x24, 0xa0, 0x1f, 0xf8, 0x05, 0x24, 0xa0, 0x1f, 0xf8, 0x05, 0x00, 0xa0,
  0x1f, 0xf8, 0x05, 0x00, 0xa0, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x1f,
  0xf8, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x1f, 0xf8,
  0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

//SOUND VARIABLES
const int16_t SOUND_SENSITIVITY = 40;
const int16_t SAMPLE_WINDOW = 5; // Sample window width in mS (50 mS = 20Hz)
bool soundDetected = true;
unsigned int sample;
double soundValue;

//STUDENT VARIABLES
const int16_t STUDENT_COLOR = BLUE;
double fallingRate = 0; //Student falling rate
const int16_t SPEED = 3;
int16_t xStudent = 50; //Starting x position
int16_t yStudent = TFT_HEIGHT - STUDENT_HEIGHT;
const int16_t MAX_HEIGHT = 100;

//PILLARS VARIABLES
int16_t movingRate = 3; //Obstacle moving rate
int16_t xPillar = TFT_WIDTH;
int16_t yPillar = TFT_HEIGHT - random(50, 60);
const int16_t PILLAR_WIDTH = 30;
const int16_t PILLAR_COLOR = GREEN;

//TEST VARIABLES
//PILLARS VARIABLES
int16_t movingRateTest = 5; //Obstacle moving rate
int16_t xTest = TFT_WIDTH;
int16_t yTest = TFT_HEIGHT - random(50, 60);
const int16_t TEST_COLOR = CYAN;

bool gameOver = false;
int16_t tally = 0;

//Array of Strings
String words[7] = {"1007", "MULTI", "UWRITING", "AOE", "CHEM", "PHYSICS", "JAVA"};
String className = "";

void loop(void)
{
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(200, 0);
  tft.println("Score: ");

  tft.setTextColor(WHITE);
  tft.setTextSize(1);

  if (!gameOver)
  {

    if (yStudent <= TFT_HEIGHT - MAX_HEIGHT - STUDENT_HEIGHT)
      fallingRate = SPEED;
    else if (yStudent >= TFT_HEIGHT - STUDENT_HEIGHT)
      fallingRate = 0;

    if (fallingRate == 0)
    {
      soundValue = readSoundLevel();
      if (soundValue > SOUND_SENSITIVITY)
        fallingRate = -SPEED;
    }

    if (xPillar <= 50 + STUDENT_WIDTH && xPillar >= 50 - PILLAR_WIDTH)
    {

      tally += 1;
      if (yStudent + STUDENT_HEIGHT > yPillar) {
        gameOver = true;
      }
    }

    scoreKeeper(tally);
    drawStudent();

    //drawPillar();
    drawTest();//added

    //Serial.println(soundValue);

    xPillar -= movingRate;
    //if the pillar is out of the screen,
    if (xPillar < -PILLAR_WIDTH - 4)
      xPillar = TFT_WIDTH;

    xTest -= movingRateTest;
    if (xTest < -TEST_WIDTH - 2 * SPEED)
      xTest = TFT_WIDTH;//

    yStudent += (int)fallingRate;
    fallingRate += 0.4;
    
  }
  else {
    delay(1000);
    gameEnd(tally);
    tally = 0;
    gameOver = false;
    gameStart();
  }

}

void drawStudent()
{

  //draws white rectangle to clear previous state
  tft.fillRect(xStudent, yStudent - fallingRate - 2, STUDENT_WIDTH, STUDENT_HEIGHT + 2 * SPEED + 2, BACKGROUND_COLOR);
  //Draws the student
  tft.Elegoo_GFX::drawBitmap(xStudent, yStudent, student, STUDENT_WIDTH, STUDENT_HEIGHT, STUDENT_COLOR);
}

void drawPillar()
{
  tft.fillRect(xPillar, yPillar, PILLAR_WIDTH, TFT_HEIGHT - yPillar, PILLAR_COLOR);
  tft.setCursor(xPillar, yPillar + 30);
  if (xPillar < TFT_WIDTH - 25) tft.println(1007);
  tft.fillRect(xPillar + movingRate + PILLAR_WIDTH, yPillar, movingRate, TFT_HEIGHT - yPillar, BACKGROUND_COLOR);
}

void drawTest()
{
  tft.fillRect(xTest, yTest, TEST_WIDTH, TFT_HEIGHT - yTest, BACKGROUND_COLOR);
  tft.Elegoo_GFX::drawBitmap(xTest, yTest, test, TEST_WIDTH, TEST_HEIGHT, TEST_COLOR);
  tft.setCursor(xTest, yTest + 40);
  //tft.fillRect(xTest, yTest, TEST_WIDTH, TFT_HEIGHT - yTest, TEST_COLOR);
  tft.fillRect(xTest + movingRateTest + TEST_WIDTH, yTest, movingRateTest, TFT_HEIGHT - yTest, BACKGROUND_COLOR);
}
double readSoundLevel()
{
  ///MIC variables
  unsigned long startMillis = millis(); // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;


  while (millis() - startMillis < SAMPLE_WINDOW)
  {
    sample = analogRead(5);
    if (sample < 1024)  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  double volts = (peakToPeak * 3.0) / 1024;  // convert to volts
  double percentage = volts / 3;
  return percentage * 255;
}

void gameFillScreen(int16_t color)
{
  tft.fillScreen(color);
}

void gameDrawObsatcle(int x, int y)
{
  tft.fillRect(x, y, 40, 40, RED);
}

void scoreKeeper(int score) {
  int16_t actual_score = score / 20;

  tft.setTextSize(2);
  tft.setCursor(275, 0);

  tft.setTextColor(BLACK);
  if (actual_score == 1)
    tft.print("0");
  else
    tft.print(String(actual_score - 1));

  tft.setCursor(275, 0);
  tft.setTextColor(WHITE);
  tft.print(String(actual_score));
  tft.setTextSize(1);
}

void gameStart() {

  gameFillScreen(BACKGROUND_COLOR);
  tft.setTextColor(BLUE);
  tft.setTextSize(3);
  tft.setCursor(20, 100);
  tft.println("Game starts in..");
  delay(2000);


  gameFillScreen(BACKGROUND_COLOR);
  tft.setTextSize(5);
  tft.setCursor(135, 100);
  tft.println("3!");
  delay(1000);

  gameFillScreen(BACKGROUND_COLOR);
  tft.setCursor(135, 100);
  tft.println("2!");
  delay(1000);

  gameFillScreen(BACKGROUND_COLOR);
  tft.setCursor(135, 100);
  tft.println("1!");
  delay(1000);

  xPillar = TFT_WIDTH;
  gameFillScreen(BACKGROUND_COLOR);

}

void displayGrade(int score) {
  int16_t a_score = score / 20;

  gameFillScreen(BACKGROUND_COLOR);
  tft.setTextSize(3);
  tft.setCursor(20, 100);
  tft.print("Your score is " + String(a_score));
  delay(1000);

  gameFillScreen(BACKGROUND_COLOR);
  tft.setCursor(90, 80);
  tft.setTextColor(RED);
  tft.setTextSize(15);
  if (a_score < 12)
    tft.print("F!");
  else if (a_score < 14)
    tft.print("D!");
  else if (a_score < 16)
    tft.print("C!");
  else if (a_score < 18)
    tft.print("B!");
  else if (a_score < 21)
    tft.print("A!");
  else {
    tft.setCursor(20, 100);
    tft.setTextSize(3);
    tft.print("WOW!! IMPOSSIBLE");
  }

  delay(2000);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
}

void gameEnd(int score) {
  gameFillScreen(BACKGROUND_COLOR);
  tft.setTextColor(BLUE);
  tft.setTextSize(4);
  tft.setCursor(20, 100);
  tft.println("Game Over...");
  delay(1000);

  displayGrade(score);

  xPillar = TFT_WIDTH;
  gameFillScreen(BACKGROUND_COLOR);
}


