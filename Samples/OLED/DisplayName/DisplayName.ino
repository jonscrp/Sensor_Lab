#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
// oled buttons
#define BUTTON_A 9
#define BUTTON_B 6
#define BUTTON_C 5



Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire); // large OLED display

void setup() {
  // put your setup code here, to run once:
  Serial.begin(96000);
  Serial.print("Starting program");

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
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0,0);
    display.println("HelloWorld");
    display.display();
    delay(3000);
    display.setCursor(30,20);
    display.println("Jonathan");
    display.display();

    

  }
}

void loop() {
  // Check if the button was pressed
    Serial.println(digitalRead(BUTTON_B));
    delay(300);
}