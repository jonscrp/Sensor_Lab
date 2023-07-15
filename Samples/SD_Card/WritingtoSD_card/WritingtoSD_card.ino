/*
Start the Oled 
and then store a message to the SD card
*/

#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
// oled buttons
#define BUTTON_A 9
#define BUTTON_B 6
#define BUTTON_C 5

#define SD_CS 10
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire); // large OLED display
File logFile;
uint8_t stat = 0; // status byte

void setup() {
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
    // check if an SD card is plugged and can be initialized
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0,0);
    display.println("Starting SD Card");
    display.display();
    Serial.println("33");
    if(!SD.begin(SD_CS)){ 
      Serial.println("Card failed, or is not plugged.");
      stat = stat | 0x01; // set bit 1 if SD error
      Serial.println("LINE 36");
    } else{
    // Creating file
    Serial.println("LINE 39");
    char filename[] = "Jack1.txt";
    // Check if file already exists
    logFile = SD.open(filename, FILE_WRITE); // open will create a new file if file doesn't already exist
    Serial.print("Writing to SD");
    logFile.println("Messessage 3");
    logFile.flush();
    }
    display.println("Finished");
    display.display();
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
