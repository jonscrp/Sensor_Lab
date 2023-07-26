 // Page to fill SSID and PASS
const char webpage_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Community Sensor Lab provisioning page</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    ssid: <input type="text" name="SSID"><br>
    <!-- <input type="submit" value="Submit">
  </form><br>
  <form action="/get"> -->
    passcode: <input type="password" name="passcode"><br>
    <input type="submit" value="Submit">
   </form>
</body></html>)rawliteral";;

/**
* print wifi relevant info to Serial
*
*/
void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print(F("SSID: "));
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print(F("IP Address: "));
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print(F("signal strength (RSSI):"));
  Serial.print(rssi);
  Serial.println(F(" dBm"));
}

/**
* print formatted MAC address to Serial
*
*/
void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16)
      Serial.print("0");
    Serial.print(mac[i], HEX);
    if (i > 0)
      Serial.print(":");
  }
  Serial.println();
}


void AP_getInfo(String &ssid, String &passcode) {
  WiFiServer server(80);
  WiFiClient client;
  Serial.println(F("Access Point Web Server"));

  status = WiFi.status();
  if (status == WL_NO_SHIELD) {
    Serial.println(F("WiFi shield not present"));
    while (true);
  }

  // make AP with string+MAC address
  makeMACssidAP("csl");

  // wait 10 seconds for connection:
  delay(1000);
  printWiFiStatus();

  while (true) {  // loop to poll connections etc.
    // compare the previous status to the current status
    if (status != WiFi.status()) {  // someone joined AP or left
      // it has changed update the variable
      status = WiFi.status();
      if (status == WL_AP_CONNECTED) {
        byte remoteMac[6];
        Serial.print(F("Device connected to AP, MAC address: "));
        WiFi.APClientMacAddress(remoteMac);
        printMacAddress(remoteMac);

        Serial.println(F("Starting server"));
        server.begin();
        // print where to go in a browser:
        IPAddress ip = WiFi.localIP();
        Serial.print(F("To provide provisioning info, open a browser at http://"));
        Serial.println(ip);

      } else {
        // a device has disconnected from the AP, and we are back in listening mode
        Serial.println(F("Device disconnected from AP"));
        client.stop();
      }
    }

    client = server.available();  // listen for incoming clients

    if (client) {                    // if you get a client,
      Serial.println(F("new client"));  // print a message out the serial port
      String currentLine = "";       // make a String to hold incoming data from the client
      while (client.connected()) {   // loop while the client's connected

        if (client.available()) {  // if there's bytes to read from the client,
          char c = client.read();  // read a byte, then
          Serial.write(c);         // print it out the serial monitor

          if (c == '\n') {  // if the byte is a newline character
            // if the current line is blank, you got two newline characters in a row.
            // that's the end of the client HTTP request, so send a response:
            if (currentLine.length() == 0) {
              // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
              // and a content-type so the client knows what's coming, then a blank line:
              client.println(F("HTTP/1.1 200 OK"));
              client.println(F("Content-type:text/html"));
              client.println();
              client.print(webpage_html);  // The HTTP response ends with another blank line:
              client.println();
              // break out of the while loop:
              break;                   
            } else {
              // if you got a newline, then check and parse currentLine and clear
              // if current line starts with 'GET' it has the info so parse                                      
              if (currentLine.startsWith("GET /get?")) {  

                int ssidIndx = currentLine.indexOf("SSID=");
                int passcodeIndx = currentLine.indexOf("passcode=");
                int httpIndx = currentLine.indexOf(" HTTP");
                ssid = currentLine.substring(ssidIndx + 5, passcodeIndx - 1);
                passcode = currentLine.substring(passcodeIndx + 9,  httpIndx);
                // close the connection:
                client.stop();
                Serial.println("client disconnected\n");
                WiFi.end();
                delay(5000);
                status = WiFi.status();
                return;  // info will be in global vars ssidg, passcodeg, gsidg. TODO Move to local vars
              }
              currentLine = "";  // if not 'GET' just start new line
            }
          } else if (c != '\r') {  // if you got anything else but a carriage return character,
            currentLine += c;      // add it to the end of the currentLine
          }
        }  // if(client.available())
      }    // while(client.connected())
      client.stop();
      Serial.println(F("Client disconnected"));

    }  // if(client)
  }    // while(true)
}

/**
*   Create an AP with a unique ssid formed with a string
*   and the last 2 hex digits of the board MAC address.
*   By default the local IP address of will be 192.168.1.1
*   you can override it with the following:
*   WiFi.config(IPAddress(10, 0, 0, 1));
*
*   @param startString a string to preface the ssid
*/
void makeMACssidAP(String startString) {

  byte localMac[6];

  Serial.print(F("Device MAC address: "));
  WiFi.macAddress(localMac);
  printMacAddress(localMac);

  char myHexString[3];
  sprintf(myHexString, "%02X%02X", localMac[1], localMac[0]);
  String ssid = startString + String((char *)myHexString);

  Serial.print(F("Creating access point: "));
  Serial.println(ssid);

  status = WiFi.beginAP(ssid.c_str());

  if (status != WL_AP_LISTENING) {
    Serial.println(F("Creating access point failed"));
    while (true)
      ;
  }
}