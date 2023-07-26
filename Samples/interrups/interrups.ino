// Ref:
//  https://www.tutorialspoint.com/arduino/arduino_interrupts.htm
// https://deepbluembedded.com/arduino-interrupts-tutorial-examples


#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
//OLED buttons
// Assigning pins
#define BUTTON_A 9
#define BUTTON_B 6
#define BUTTON_C 5

/*
///const byte ledPin = 13;
const byte BUTTON_A = 9;
const byte BUTTON_B = 6;
const byte BUTTON_C = 5;
*/

int options[2];
//volatile byte state = LOW;

// 'X' = no option selected
char sentinel = 'X';

// Screen Dimension 64 X 128
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire); // large OLED display

void setup() {
  //pinMode(ledPin, OUTPUT);
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_A), A, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_B), B, CHANGE);
  attachInterrupt(digitalPinToInterrupt(BUTTON_C), C, CHANGE);

  display.print("Select using the buttons A, B or C");

  question_1();

}


void question_1(){
  // Select Option 
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Create s new connection");
  display.println("Use an existing connection");
  display.println("Continue offline");
  display.display(); // actually display all of the above

  switch(sentinel){
    case 'A':  question_2();
    case 'B':  question_3();
    case 'C': Serial.println("Continuing Offline...");
      break;
    default:
      break;
  }
}

void question_2(){
   // Select Option 
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Continue");
  display.println("Return");
  display.display(); // actually display all of the above

  switch(sentinel){
    case('A'): Serial.println("Start provisioning");
      break;
    case('B'): question_1();
      break;
    default:
      break;
  }
}

void question_3(){
  // use existing connection
  // display connections available - max2
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Connection1");
  display.println("Connection2");
  display.println("Return");
  display.display(); // actually display all of the above

  switch(sentinel){
    case 'A': Serial.println("Connecting to connection 1");
      //SSID = connection_1_SSID;
      //PSWD = connection_1_pswd;
      //initialize_wifi();
      break;
    case 'B': Serial.println("Connecting to connection 2");
     // SSID = connection_2_SSID;
     // PSWD = connection_3_pswd;
     // initialize_wifi();
      break;
    case 'C': question_1();
      break;
    default:
      break;
  }
}

void loop() {
  // not use
}

void reset(){
  sentinel = 'X';
}

void A(){
  sentinel =  'A';
}

void B(){
  sentinel = 'B';
}

void C(){
  sentinel = 'C';
}