#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_SH110X.h>  // oled library
#include <WiFi101.h>


#define VBATPIN A7 
#define BUTTON_A  9 // Oled button also A7 enable pullup to read button
#define BUTTON_B  6 // oled button
#define BUTTON_C  5 // oled button
#define SD_CS 10    // Chip select for SD card default for Adalogger

#define MAXBUF_REQUIREMENT 48

#if (defined(I2C_BUFFER_LENGTH) &&                 \
     (I2C_BUFFER_LENGTH >= MAXBUF_REQUIREMENT)) || \
    (defined(BUFFER_LENGTH) && BUFFER_LENGTH >= MAXBUF_REQUIREMENT)
#define USE_PRODUCT_INFO
#endif

String ssidg, passcodeg ;
WiFiSSLClient client;
Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);
File logfile;
int status = WL_IDLE_STATUS;

void setup() {
  pinMode(VBATPIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);

  initializeOLED();
  WiFi.setPins(8,7,4,2);
  AP_getInfo(ssidg, passcodeg); 
  display.display();
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Wifi info:");
  display.print("ssid");
  display.println(ssidg);
  display.print("passcodeg");
  display.println(passcodeg);
  display.display();
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
