#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
// oled buttons
// Assigning pins
#define BUTTON_A 9
#define BUTTON_B 6
#define BUTTON_C 5

// Board information  https://learn.adafruit.com/adafruit-128x64-oled-featherwing/pinouts
// Note: The board uses the I2C protocol

// Screen Dimension 64 X 128
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire); // large OLED display

int x_coor = 0;
int y_coor = 0;
int x_offset = 10;
int y_offset = 10;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(96000);
  Serial.print("Starting program");

// Note: 0x3C is the board address and can be changed to 0x3D
  if (!display.begin(0x3C, true)){ // Address 0x3C for 128x32
    Serial.println(F("SH110X  allocation failed"));
  }
  else{
    Serial.println("LED is working");
    // Clear buffer.
    display.clearDisplay();
    display.display();
    // display orientation
    display.setRotation(1);
    // buttons 
    pinMode(BUTTON_A, INPUT_PULLUP); // default is 1 when press it go's to 0
    pinMode(BUTTON_B, INPUT_PULLUP); // used to prevent oscillation
    pinMode(BUTTON_C, INPUT_PULLUP);

    // display 
    display.setTextSize(1); // text orientation
    display.setTextColor(SH110X_WHITE);
    display.setCursor(30,20);
    display.println("Legends");
    display.display();
    delay(1000);
  }
}

void loop() {
  display.clearDisplay();
  display.setCursor(x_coor,y_coor);
  display.print("W");
  display.display();
  delay(200);
  // Logic to prevent the character from leaving the screen.
  if( (x_coor + x_offset) > 128 ||  (x_coor + x_offset) < 0){
      x_offset = -x_offset;
  } 
  if( (y_coor + y_offset) > 64||  (y_coor + y_offset) < 0 ){
      y_offset =  -y_offset;
  } 
  // Calculating new position
  x_coor += x_offset;
  y_coor += y_offset;
}