#include <Wire.h>
#include <U8g2lib.h>

#include "startScreen.h"

// Initialize U8g2 for SH1106 display with I2C communication
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Define pin numbers for buttons
#define BUTTON_LEFT_UP 25
#define BUTTON_LEFT_DOWN 27
#define JOYSTICK_RIGHT 15
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
const int buzzerPin = 13;



// Game variables
int paddleLeftY = 24;         // Initial paddle position (tuned for 64px height)
int paddleRightY = 24;         // Initial paddle position (tuned for 64px height)
int paddleHeight = 16;    // Paddle height
int ballX = 64, ballY = 32;     // Ball starting position
int ballSpeedX = 2, ballSpeedY = 2; // Ball speed
int joyStickY = 500; // Joystick direction

int score = 0;
bool startScreen = true;

void setup() {
  Serial.begin(9600);
  
  // Initialize buttons
  pinMode(BUTTON_LEFT_UP, INPUT_PULLUP);
  pinMode(BUTTON_LEFT_DOWN, INPUT_PULLUP);

  // Initialize the display
  u8g2.begin();
}

void loop() {
  song(buzzerPin);

  if(startScreen) {
    // Show startscreen
    showStartScreen();
  } else {
    // Play game iteration
    gameIteration();
  }

  
}

void showStartScreen() {

  // Check to see if game should be started in next iteration
  if(!digitalRead(BUTTON_LEFT_UP)){
    startScreen = false;
  }

  if(!digitalRead(BUTTON_LEFT_DOWN)){
    startScreen = false;
  }

  // Clear the display buffer
  u8g2.clearBuffer();

  // Draw startScreenSprite
  u8g2.drawXBMP(0, 0, img_pong_logo_width, img_pong_logo_height, img_pong_logo);

  // Send buffer to display
  u8g2.sendBuffer();

  // Delay for frame rate control
  delay(20);

}

void gameIteration() {
  // Read button states
  if (digitalRead(BUTTON_LEFT_UP) == LOW && paddleLeftY > 0) {
    paddleLeftY -= 3;
  }
  if (digitalRead(BUTTON_LEFT_DOWN) == LOW && paddleLeftY < (64 - paddleHeight)) {
    paddleLeftY += 3;
  }
  joyStickY = analogRead(JOYSTICK_RIGHT);
  Serial.println(joyStickY);
  if (joyStickY <= 2000 && paddleRightY > 0) {
    paddleRightY -= 3;
  }
  if (joyStickY >= 2500 && paddleRightY < (64 - paddleHeight)) {
    paddleRightY += 3;
  }

  // Update ball position
  ballX += ballSpeedX;
  ballY += ballSpeedY;

  // Ball collision with top and bottom edges
  if (ballY <= 0 || ballY >= 63) {
    ballSpeedY = -ballSpeedY;
    playBleep();
  }

  // Ball collision with paddle
  if (ballX <= 4 && ballY >= paddleLeftY && ballY <= paddleLeftY + paddleHeight) {
    ballSpeedX = -ballSpeedX;
    playBleep();
    score++;
  } else if (ballX >= 119 && ballY >= paddleRightY && ballY <= paddleRightY + paddleHeight) {       
    ballSpeedX = -ballSpeedX;
    playBleep();
    score++;
  }

  // Reset ball position if it goes out of bounds
  if (ballX < 0 || ballX > 127) {
    ballX = 64;
    ballY = 32;
    ballSpeedX = -ballSpeedX;
    score = 0;
    startScreen = true;
    playGameOver();
  }

  // Clear the display buffer
  u8g2.clearBuffer();

  // Draw paddle
  u8g2.drawBox(0, paddleLeftY, 4, paddleHeight);
  u8g2.drawBox(119, paddleRightY, 4, paddleHeight);
  
  
  // Draw ball
  u8g2.drawBox(ballX, ballY, 3, 3);

  // Display the score
  u8g2.setFont(u8g2_font_ncenB08_tr);             // Set font
  u8g2.setCursor(40, 10);                         // Position the score
  u8g2.print("Score: ");
  u8g2.print(score);


  // Send buffer to display
  u8g2.sendBuffer();

  // Delay for frame rate control
  delay(20);
}

// Function to play a bleep sound
void playBleep() {
  tone(buzzerPin, 1000, 100); // Play a 1000 Hz tone for 100 ms
}

// Function to play a bleep sound
void playGameOver() {
  tone(buzzerPin, 1000, 100); // Play a 1000 Hz tone for 100 ms
  tone(buzzerPin, 800, 100); // Play a 1000 Hz tone for 100 ms
  tone(buzzerPin, 600, 300); // Play a 1000 Hz tone for 100 ms

}


void song(int buzzerPin){
  
  tone(buzzerPin, 330);
  delay(529);
  noTone(buzzerPin);

  tone(buzzerPin, 392);
  delay(794);
  noTone(buzzerPin);

  tone(buzzerPin, 330);
  delay(353);
  noTone(buzzerPin);

  tone(buzzerPin, 370);
  delay(353);
  noTone(buzzerPin);

  tone(buzzerPin, 392);
  delay(618);
  noTone(buzzerPin);

  tone(buzzerPin, 494);
  delay(706);
  noTone(buzzerPin);

  tone(buzzerPin, 440);
  delay(353);
  noTone(buzzerPin);

  tone(buzzerPin, 494);
  delay(706);
  noTone(buzzerPin);

  tone(buzzerPin, 587);
  delay(706);
  noTone(buzzerPin);

  tone(buzzerPin, 494);
  delay(606);
  noTone(buzzerPin);

  tone(buzzerPin, 370);
  delay(641);
  noTone(buzzerPin);

  tone(buzzerPin, 554);
  delay(353);
  noTone(buzzerPin);

  tone(buzzerPin, 587);
  delay(706);
  noTone(buzzerPin);

  tone(buzzerPin, 294);
  delay(265);
  noTone(buzzerPin);

  tone(buzzerPin, 330);
  delay(265);
  noTone(buzzerPin);

  tone(buzzerPin, 370);
  delay(265);
  noTone(buzzerPin);

  tone(buzzerPin, 330);
  delay(647);
  noTone(buzzerPin);

  tone(buzzerPin, 294);
  delay(235);
  noTone(buzzerPin);

  tone(buzzerPin, 330);
  delay(253);
  noTone(buzzerPin);

  tone(buzzerPin, 349);
  delay(265);
  noTone(buzzerPin);

  tone(buzzerPin, 392);
  delay(229);
  noTone(buzzerPin);

  tone(buzzerPin, 440);
  delay(706);
  noTone(buzzerPin);

  tone(buzzerPin, 294);
  delay(235);
  noTone(buzzerPin);

  tone(buzzerPin, 330);
  delay(229);
  noTone(buzzerPin);

  tone(buzzerPin, 349);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 330);
  delay(235);
  noTone(buzzerPin);

  tone(buzzerPin, 349);
  delay(224);
  noTone(buzzerPin);

  tone(buzzerPin, 392);
  delay(229);
  noTone(buzzerPin);

  tone(buzzerPin, 440);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 392);
  delay(218);
  noTone(buzzerPin);

  tone(buzzerPin, 349);
  delay(224);
  noTone(buzzerPin);

  tone(buzzerPin, 330);
  delay(265);
  noTone(buzzerPin);

  tone(buzzerPin, 349);
  delay(647);
  noTone(buzzerPin);

  tone(buzzerPin, 349);
  delay(353);
  noTone(buzzerPin);

  tone(buzzerPin, 440);
  delay(353);
  noTone(buzzerPin);

  tone(buzzerPin, 392);
  delay(706);
  noTone(buzzerPin);

  tone(buzzerPin, 392);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 440);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 494);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 440);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 392);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 440);
  delay(353);
  noTone(buzzerPin);

  tone(buzzerPin, 440);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 523);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 494);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 440);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 392);
  delay(235);
  noTone(buzzerPin);

  tone(buzzerPin, 440);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 262);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 262);
  delay(235);
  noTone(buzzerPin);

  tone(buzzerPin, 294);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 330);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 349);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 392);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 440);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 494);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 330);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 349);
  delay(212);
  noTone(buzzerPin);

  tone(buzzerPin, 294);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 330);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 349);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 330);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 294);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 262);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 294);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 233);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 262);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 294);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 262);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 233);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 220);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 233);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 196);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 220);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 233);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 220);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 196);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 175);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 196);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 165);
  delay(353);
  noTone(buzzerPin);

  tone(buzzerPin, 175);
  delay(353);
  noTone(buzzerPin);

  tone(buzzerPin, 349);
  delay(353);
  noTone(buzzerPin);

  tone(buzzerPin, 330);
  delay(353);
  noTone(buzzerPin);

  tone(buzzerPin, 294);
  delay(782);
  noTone(buzzerPin);

  tone(buzzerPin, 262);
  delay(776);
  noTone(buzzerPin);

  tone(buzzerPin, 233);
  delay(706);
  noTone(buzzerPin);

  tone(buzzerPin, 220);
  delay(176);
  noTone(buzzerPin);

  tone(buzzerPin, 233);
  delay(353);
  noTone(buzzerPin);

  tone(buzzerPin, 196);
  delay(1235);
  noTone(buzzerPin);

  tone(buzzerPin, 175);
  delay(353);
  noTone(buzzerPin);

  tone(buzzerPin, 196);
  delay(706);
  noTone(buzzerPin);

  tone(buzzerPin, 233);
  delay(706);
  noTone(buzzerPin);

  tone(buzzerPin, 220);
  delay(3121);
  noTone(buzzerPin);
}

