#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED FeatherWing buttons map to different pins depending on board.
// The I2C (Wire) bus may also be different.

// 32u4, M0, M4, nrf52840 and 328p
  #define BUTTON_A  9
  #define BUTTON_B  6
  #define BUTTON_C  5
  #define WIRE Wire

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &WIRE);

void setup() {
  Serial.begin(9600);

  Serial.println("OLED FeatherWing test");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  Serial.println("OLED begun");

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  Serial.println("IO test");

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);


  // text display tests
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("OptionA");
  display.println("OptionB");
  display.println("OptionC");
  display.setCursor(0,24);
  display.print("Select using the buttons A, B or C");
  display.display(); // actually display all of the above

}

int choice = 68;
void loop() {

  // Select your option
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
    if(choice != 68){ // if a choice as made quit while loop.
      break;
    }
  }
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("You choose :");
  display.print(" Option");
  display.println(char(choice));
  display.display();

}