#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <LiquidCrystal.h>

// Pin connections
SoftwareSerial mySerial(10, 11); // RX, TX for DFPlayer Mini
DFRobotDFPlayerMini myDFPlayer;
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // RS, E, D4, D5, D6, D7

// Button pins
const int playPauseBtn = 8;
const int nextBtn = 9;
const int prevBtn = 12;

bool isPlaying = false;

void setup() {
  // LCD setup
  lcd.begin(16, 2);
  lcd.print("Media Player");

  // Buttons setup
  pinMode(playPauseBtn, INPUT_PULLUP);
  pinMode(nextBtn, INPUT_PULLUP);
  pinMode(prevBtn, INPUT_PULLUP);

  // DFPlayer setup
  mySerial.begin(9600);
  Serial.begin(115200);
  if (!myDFPlayer.begin(mySerial)) {
    lcd.setCursor(0, 1);
    lcd.print("DFPlayer Error!");
    while (true);
  }
  myDFPlayer.volume(25);  // Set volume (0-30)
  lcd.setCursor(0, 1);
  lcd.print("Ready to Play");
}

void loop() {
  if (digitalRead(playPauseBtn) == LOW) {
    delay(200); // debounce
    if (isPlaying) {
      myDFPlayer.pause();
      lcd.setCursor(0, 1);
      lcd.print("Paused        ");
      isPlaying = false;
    } else {
      myDFPlayer.start();
      lcd.setCursor(0, 1);
      lcd.print("Playing...    ");
      isPlaying = true;
    }
  }

  if (digitalRead(nextBtn) == LOW) {
    delay(200);
    myDFPlayer.next();
    lcd.setCursor(0, 1);
    lcd.print("Next Song     ");
    isPlaying = true;
  }

  if (digitalRead(prevBtn) == LOW) {
    delay(200);
    myDFPlayer.previous();
    lcd.setCursor(0, 1);
    lcd.print("Prev Song     ");
    isPlaying = true;
  }
}
