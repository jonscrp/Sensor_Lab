#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
// reference:
// go to - https://en.cppreference.com/w/cpp/language/goto

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);


// 32u4, M0, M4, nrf52840, esp32-s2 and 328p
#define BUTTON_A  9
#define BUTTON_B  6
#define BUTTON_C  5


void setup() {
  Serial.begin(115200);

  Serial.println("128x64 OLED FeatherWing test");
  delay(250); // wait for the OLED to power up
  display.begin(0x3C, true); // Address 0x3C default

  Serial.println("OLED begun");

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);
  display.setRotation(1);
  // Clear the buffer.
  display.clearDisplay();
  display.display();

  Serial.println("IO test");

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);

}

void loop() {
  Selecting:
  
  // Select Option 
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("OptionA");
  display.println("OptionB");
  display.println("OptionC");
  display.setCursor(0,24);
  display.print("Select using the buttons A, B or C");
  display.display(); // actually display all of the above
  
  delay(1000); 
  int choice = 68;
  // Check option selected
  while(1){
    if(!digitalRead(BUTTON_A)){
      choice = 65;
    }
    else if(!digitalRead(BUTTON_B)){
      choice = 66;
    }
    else if(!digitalRead(BUTTON_C)){
      choice = 67;
    } 
    if(choice != 68){ // if a choice was made quit while loop.
      break;
    }
  }
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("You choose :");
  display.print(" Option");
  display.println(char(choice));
  display.display();
  delay(400);
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Would you like to continue( A = Ok, B = Return , C = Cancel)");
  display.display();
  choice = 68;
  while(1){
    if(!digitalRead(BUTTON_A)){
      choice = 65;
    }
    else if(!digitalRead(BUTTON_B)){
      choice = 66;
    }
    else if(!digitalRead(BUTTON_C)){
      choice = 67;
    } 
    if(choice == 65){ // if a choice as made quit while loop.
      break;
    }
    else if(choice == 67){
      goto Selecting; // return to previous step
    }
  }

  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Second choice");
  display.display();
  while(1);
  
}