void initializeOLED()  {
  Serial.print("starting 128x64 OLED... ");
  if (!display.begin(0x3C, true)) // Address 0x3C for 128x32
    Serial.println(F("SH110X  allocation failed"));
  else  {
    Serial.println("OLED ok");
    display.setRotation(1);
    //    Serial.println("Button test");
    pinMode(BUTTON_A, INPUT_PULLUP);
    pinMode(BUTTON_B, INPUT_PULLUP);
    pinMode(BUTTON_C, INPUT_PULLUP);
    // text display tests
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);
  }
   
}