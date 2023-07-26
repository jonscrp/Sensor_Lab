// Ref:
//  https://www.tutorialspoint.com/arduino/arduino_interrupts.htm
// https://deepbluembedded.com/arduino-interrupts-tutorial-examples

#include <Wire.h>
#include <Adafruit_SH110X.h>  // oled library
//OLED buttons
// Assigning pins
#define BUTTON_A 9
#define BUTTON_B 6
#define BUTTON_C 5

// 'X' = no option selected
char sentinel = 'X';

// Screen Dimension 64 X 128
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire); // large OLED display
void setup() {
  Serial.print("starting 128x64 OLED... ");
  if (!display.begin(0x3C, true)) // Address 0x3C for 128x32
    Serial.println(F("SH110X  allocation failed")); 
  else{

  Serial.begin(9600);
  display.display();
  delay(700);
  display.setRotation(1); // Up
  // Clear the buffer.
  display.clearDisplay();
  display.display();
  // text display tests
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  //pinMode(ledPin, OUTPUT);
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_A), A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_B), B, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_C), C, CHANGE);

  display.print("Select using the buttons A, B or C");
  delay(2500);
  display.display();
  sel_connection(); 
  }
}


void sel_connection(){
  delay(1000);
  display.clearDisplay();
  display.setCursor(0,0);
  // Options
  display.println("[A]New Connection");
  display.println("[B]Use Existing");
  display.println("[C]Offline");
  display.display(); // actually display all of the above
  Serial.println("Wait for user choice:");
  reset();
  while(sentinel == 'X'){
    Serial.println(sentinel);
    switch(sentinel){
    case 'A':  
      Serial.print("Connection method: ");
      Serial.println(sentinel);
      create_new_connection();  
      break;
    case 'B':
      Serial.print("Connection method: ");
      Serial.println(sentinel);
      use_existing_connection();
      break;
    case 'C':
      // move on with out connecting to internet
      Serial.println("Continuing Offline...");
      break;
    }
  }
  Serial.println("Kill while");
}


void create_new_connection(){
  delay(1000);
   // Select Option 
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Continue");
  display.println("Return");
  display.display(); // actually display all of the above
  reset();
  while(sentinel == 'X'){
    Serial.println(sentinel);
    switch(sentinel){
      case 'A':
        Serial.print("Creating new connection: ");
        Serial.println(sentinel);
        Serial.println("Start provisioning");
        break;
      case 'B': 
        Serial.print("Connection method: ");
        Serial.println(sentinel);
        sel_connection(); // return to previous step
        break;
    }
  }
   Serial.println("Kill while");
}

void use_existing_connection(){
  delay(1000);
  // use existing connection
  // display connections available - max2
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("[A]Connection1");  // secrets.
  display.println("[B]Connection2");
  display.println("[C]Return");
  display.display(); // actually display all of the above
  reset();
  while(sentinel == 'X'){
    Serial.println(sentinel);
    switch(sentinel){
      case 'A':
        Serial.println("Connecting to connection 1");
        Serial.print("Connecting SSID: ");
        Serial.println(sentinel);
        //SSID = connection_1_SSID;
        //PSWD = connection_1_pswd;
        //initialize_wifi();
        break;
      case 'B': 
        Serial.println("Connecting to connection 2");
        Serial.print("Connecting SSID: ");
        Serial.println(sentinel);
        // SSID = connection_2_SSID;
        // PSWD = connection_3_pswd;
        // initialize_wifi();
        break;
      case 'C':
        sel_connection();
        //Serial.print("Continue offline");
        break;
    }
  }
  Serial.println("Kill while");
}

void loop() {
  // not use
}

void reset(){
  sentinel = 'X';
}

void A(){
  sentinel = 'A';
}

void B(){
  sentinel = 'B';
}

void C(){
  sentinel = 'C';
}