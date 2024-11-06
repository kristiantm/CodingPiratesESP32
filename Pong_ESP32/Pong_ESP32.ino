#include <Wire.h>
#include <U8g2lib.h>

// Initialize U8g2 for SH1106 display with I2C communication
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Define pin numbers for buttons
#define BUTTON_LEFT_UP 25
#define BUTTON_LEFT_DOWN 27
#define JOYSTICK_RIGHT 15

// Game variables
int paddleLeftY = 24;         // Initial paddle position (tuned for 64px height)
int paddleRightY = 24;         // Initial paddle position (tuned for 64px height)
int paddleHeight = 16;    // Paddle height
int ballX = 64, ballY = 32;     // Ball starting position
int ballSpeedX = 2, ballSpeedY = 2; // Ball speed
int joyStickY = 500; // Joystick direction

void setup() {
  Serial.begin(9600);
  
  // Initialize buttons
  pinMode(BUTTON_LEFT_UP, INPUT_PULLUP);
  pinMode(BUTTON_LEFT_DOWN, INPUT_PULLUP);

  // Initialize the display
  u8g2.begin();
}

void loop() {
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
  }

  // Ball collision with paddle
  if (ballX <= 4 && ballY >= paddleLeftY && ballY <= paddleLeftY + paddleHeight) {
    ballSpeedX = -ballSpeedX;
  } else if (ballX >= 119 && ballY >= paddleRightY && ballY <= paddleRightY + paddleHeight) {       
    ballSpeedX = -ballSpeedX;
  }

  // Reset ball position if it goes out of bounds
  if (ballX < 0 || ballX > 127) {
    ballX = 64;
    ballY = 32;
    ballSpeedX = -ballSpeedX;
  }

  // Clear the display buffer
  u8g2.clearBuffer();

  // Draw paddle
  u8g2.drawBox(0, paddleLeftY, 4, paddleHeight);
  u8g2.drawBox(119, paddleRightY, 4, paddleHeight);
  
  // Draw ball
  u8g2.drawBox(ballX, ballY, 3, 3);

  // Send buffer to display
  u8g2.sendBuffer();

  // Delay for frame rate control
  delay(20);
}