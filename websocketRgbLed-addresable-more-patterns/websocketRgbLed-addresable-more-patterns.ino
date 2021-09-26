#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoOTA.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <WebSocketsServer.h>
#include  "FastLED.h"
#define NUM_LEDS 150
void rainbowWave(uint8_t, uint8_t);


CRGB leds[NUM_LEDS];

ESP8266WiFiMulti wifiMulti;       // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);       // Create a webserver object that listens for HTTP request on port 80
WebSocketsServer webSocket(81);    // create a websocket server on port 81

File fsUploadFile;                 // a File variable to temporarily store the received file

const char *ssid = "prrrrrrrrrrrr"; // The name of the Wi-Fi network that will be created
const char *password = "";   // The password required to connect to it, leave blank for an open network

const char *OTAName = "ESP8266";           // A name and a password for the OTA service
const char *OTAPassword = "esp8266";



const char* mdnsName = "esp8266"; // Domain name for the mDNS responder






void setup() {
  FastLED.addLeds<NEOPIXEL, 26>(leds, NUM_LEDS); 

  Serial.begin(115200);        // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println("\r\n");

  startWiFi();                 // Start a Wi-Fi access point, and try to connect to some given access points. Then wait for either an AP or STA connection
  
  startOTA();                  // Start the OTA service
  
  startSPIFFS();               // Start the SPIFFS and list all contents

  startWebSocket();            // Start a WebSocket server
  
  startMDNS();                 // Start the mDNS responder

  startServer();               // Start a HTTP server with a file read handler and an upload handler
  
}


// ##################### PATTERNS ########################



// void radiation(int ahue, int idelay) { //-SORT OF RADIATION SYMBOLISH- 
//   //int N2 = int(NUM_LEDS/2);
//   int N3 = int(NUM_LEDS/3);
//   int N6 = int(NUM_LEDS/6);  
//   int N12 = int(NUM_LEDS/12);  
//   int acolor[3];

//   for(int i = 0; i < N6; i++ ) { //-HACKY, I KNOW...
//     tcount = tcount + .02;
//     if (tcount > 3.14) {tcount = 0.0;}
//     ibright = int(sin(tcount)*255);
    
//     int j0 = (i + NUM_LEDS - N12) % NUM_LEDS;
//     int j1 = (j0+N3) % NUM_LEDS;
//     int j2 = (j1+N3) % NUM_LEDS;    
//     HSVtoRGB(ahue, 255, ibright, acolor);  
// //    leds[j0].r = acolor[0]; leds[j0].g = acolor[1]; leds[j0].b = acolor[2];
//     leds.setPixel(j0, acolor[0], acolor[1], acolor[2]);

// //    leds[j1].r = acolor[0]; leds[j1].g = acolor[1]; leds[j1].b = acolor[2];
//     leds.setPixel(j1, acolor[0], acolor[1], acolor[2]);
// //    leds[j2].r = acolor[0]; leds[j2].g = acolor[1]; leds[j2].b = acolor[2];    
//     leds.setPixel(j2, acolor[0], acolor[1], acolor[2]);

//   }    
//     leds.show();    
//     delay(idelay);    
// }


// void germany(int idelay) { //-german flag
//   //int N2 = int(NUM_LEDS/2);
//   // one_color_allNOSHOW(0,0,0);
//   int split = 12;
//   for(int i = 0; i < NUM_LEDS; i++) {
//     if ( i < (NUM_LEDS/split)) { 
//       leds[i].red = 255;
//       leds[i].green = 0;
//       leds[i].blue = 0;
//       // leds.setPixel(i, 255, 0, 0);
//       }
//     else if ( i < (NUM_LEDS/split*(split/2-1))) {
//       leds[i].red = 0;
//       leds[i].green = 0;
//       leds[i].blue = 0;
//       //  leds.setPixel(i, 0, 0, 0);
//        }
//     else if ( i < (NUM_LEDS/split*(split/2+1))) {
//       leds[i].red = 255;
//       leds[i].green = 0;
//       leds[i].blue = 0;
//       //  leds.setPixel(i, 255, 0, 0);
//        }
//     else if ( i < (NUM_LEDS/split*(split-1))) {
//       leds[i].red = 255;
//       leds[i].green = 204;
//       leds[i].blue = 0;
//       //  leds.setPixel(i, 255, 204, 0);
//        }
//     else {
//       leds[i].red = 255;
//       leds[i].green = 0;
//       leds[i].blue = 0;
//       // FastLED.setPixel(i, 255, 0, 0);
//       }
//           FastLED.show();    
//   }    

//     delay(idelay);    
// }


void setPixel(int Pixel, byte red, byte green, byte blue) {

   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;

}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}


void showStrip() {

   FastLED.show();

}

void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause){
  for(int j = 0; j < StrobeCount; j++) {
    setAll(red,green,blue);
    showStrip();
    delay(FlashDelay);
    setAll(0,0,0);
    showStrip();
    delay(FlashDelay);
  }
 
 delay(EndPause);
}


void Fire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[NUM_LEDS];
  int cooldown;
  
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);
    
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
  
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
    
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  showStrip();
  delay(SpeedDelay);
}

void setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    setPixel(Pixel, 255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    setPixel(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    setPixel(Pixel, heatramp, 0, 0);
  }
}
void theaterChaseRainbow(int SpeedDelay) {
  byte *c;
  
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < NUM_LEDS; i=i+3) {
          c = Wheel( (i+j) % 255);
          setPixel(i+q, *c, *(c+1), *(c+2));    //turn every third pixel on
        }
        showStrip();
       
        delay(SpeedDelay);
       
        for (int i=0; i < NUM_LEDS; i=i+3) {
          setPixel(i+q, 0,0,0);        //turn every third pixel off
        }
    }
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
  
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}
void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
  int Position=0;
  
  for(int i=0; i<NUM_LEDS*2; i++)
  {
      Position++; // = 0; //Position + Rate;
      for(int i=0; i<NUM_LEDS; i++) {
        // sine wave, 3 offset waves make a rainbow!
        //float level = sin(i+Position) * 127 + 128;
        //setPixel(i,level,0,0);
        //float level = sin(i+Position) * 127 + 128;
        setPixel(i,((sin(i+Position) * 127 + 128)/255)*red,
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);
      }
      
      showStrip();
      delay(WaveDelay);
  }
}


void colorWipe(byte red, byte green, byte blue, int SpeedDelay) {
  for(uint16_t i=0; i<NUM_LEDS; i++) {
      setPixel(i, red, green, blue);
      showStrip();
      delay(SpeedDelay);
  }
}



// void strips_loop() {
//   if(strip0_loop0() & 0x01)
//     strip_0.strip.show();
// }

// uint8_t strip0_loop0() {
//   uint8_t ret = 0x00;
//   switch(strip0loop0.currentChild) {
//     case 0: 
//            ret = strip0_loop0_eff0();break;
//   }
//   if(ret & 0x02) {
//     ret &= 0xfd;
//     if(strip0loop0.currentChild + 1 >= strip0loop0.childs) {
//       strip0loop0.currentChild = 0;
//       if(++strip0loop0.currentTime >= strip0loop0.cycles) {strip0loop0.currentTime = 0; ret |= 0x02;}
//     }
//     else {
//       strip0loop0.currentChild++;
//     }
//   };
//   return ret;
// }

// uint8_t strip0_loop0_eff0() {
//     // Strip ID: 0 - Effect: Rainbow - LEDS: 150
//     // Steps: 60 - Delay: 20
//     // Colors: 3 (91.206.255, 245.34.76, 255.255.255)
//     // Options: rainbowlen=60, toLeft=true, 
//   if(millis() - strip_0.effStart < 20 * (strip_0.effStep)) return 0x00;
//   float factor1, factor2;
//   uint16_t ind;
//   for(uint16_t j=0;j<150;j++) {
//     ind = strip_0.effStep + j * 1;
//     switch((int)((ind % 60) / 20)) {
//       case 0: factor1 = 1.0 - ((float)(ind % 60 - 0 * 20) / 20);
//               factor2 = (float)((int)(ind - 0) % 60) / 20;
//               strip_0.strip.setPixelColor(j, 91 * factor1 + 245 * factor2, 206 * factor1 + 34 * factor2, 255 * factor1 + 76 * factor2);
//               break;
//       case 1: factor1 = 1.0 - ((float)(ind % 60 - 1 * 20) / 20);
//               factor2 = (float)((int)(ind - 20) % 60) / 20;
//               strip_0.strip.setPixelColor(j, 245 * factor1 + 255 * factor2, 34 * factor1 + 255 * factor2, 76 * factor1 + 255 * factor2);
//               break;
//       case 2: factor1 = 1.0 - ((float)(ind % 60 - 2 * 20) / 20);
//               factor2 = (float)((int)(ind - 40) % 60) / 20;
//               strip_0.strip.setPixelColor(j, 255 * factor1 + 91 * factor2, 255 * factor1 + 206 * factor2, 255 * factor1 + 255 * factor2);
//               break;
//     }
//   }
//   if(strip_0.effStep >= 60) {strip_0.Reset(); return 0x03; }
//   else strip_0.effStep++;
//   return 0x01;
// }
// class Strip
// {
// public:
//   uint8_t   effect;
//   uint8_t   effects;
//   uint16_t  effStep;
//   unsigned long effStart;
//   Adafruit_NeoPixel strip;
//   Strip(uint16_t leds, uint8_t pin, uint8_t toteffects, uint16_t striptype) : strip(leds, pin, striptype) {
//     effect = -1;
//     effects = toteffects;
//     Reset();
//   }
//   void Reset(){
//     effStep = 0;
//     effect = (effect + 1) % effects;
//     effStart = millis();
//   }
// };

// struct Loop
// {
//   uint8_t currentChild;
//   uint8_t childs;
//   bool timeBased;
//   uint16_t cycles;
//   uint16_t currentTime;
//   Loop(uint8_t totchilds, bool timebased, uint16_t tottime) {currentTime=0;currentChild=0;childs=totchilds;timeBased=timebased;cycles=tottime;}
// };

// Strip strip_0(150, 8, 150, NEO_GRB + NEO_KHZ800);
// struct Loop strip0loop0(1, false, 1);

// //[GLOBAL_VARIABLES]

// void setup() {

//   //Your setup here:


// }

// void loop() {

//   //Your code here:

//   strips_loop();
// }

// void strips_loop() {
//   if(strip0_loop0() & 0x01)
//     strip_0.strip.show();
// }

// uint8_t strip0_loop0() {
//   uint8_t ret = 0x00;
//   switch(strip0loop0.currentChild) {
//     case 0: 
//            ret = strip0_loop0_eff0();break;
//   }
//   if(ret & 0x02) {
//     ret &= 0xfd;
//     if(strip0loop0.currentChild + 1 >= strip0loop0.childs) {
//       strip0loop0.currentChild = 0;
//       if(++strip0loop0.currentTime >= strip0loop0.cycles) {strip0loop0.currentTime = 0; ret |= 0x02;}
//     }
//     else {
//       strip0loop0.currentChild++;
//     }
//   };
//   return ret;
// }

// uint8_t strip0_loop0_eff0() {
//     // Strip ID: 0 - Effect: Rainbow - LEDS: 150
//     // Steps: 60 - Delay: 20
//     // Colors: 3 (91.206.255, 245.34.76, 255.255.255)
//     // Options: rainbowlen=60, toLeft=true, 
//   if(millis() - strip_0.effStart < 20 * (strip_0.effStep)) return 0x00;
//   float factor1, factor2;
//   uint16_t ind;
//   for(uint16_t j=0;j<150;j++) {
//     ind = strip_0.effStep + j * 1;
//     switch((int)((ind % 60) / 20)) {
//       case 0: factor1 = 1.0 - ((float)(ind % 60 - 0 * 20) / 20);
//               factor2 = (float)((int)(ind - 0) % 60) / 20;
//               strip_0.strip.setPixelColor(j, 91 * factor1 + 245 * factor2, 206 * factor1 + 34 * factor2, 255 * factor1 + 76 * factor2);
//               break;
//       case 1: factor1 = 1.0 - ((float)(ind % 60 - 1 * 20) / 20);
//               factor2 = (float)((int)(ind - 20) % 60) / 20;
//               strip_0.strip.setPixelColor(j, 245 * factor1 + 255 * factor2, 34 * factor1 + 255 * factor2, 76 * factor1 + 255 * factor2);
//               break;
//       case 2: factor1 = 1.0 - ((float)(ind % 60 - 2 * 20) / 20);
//               factor2 = (float)((int)(ind - 40) % 60) / 20;
//               strip_0.strip.setPixelColor(j, 255 * factor1 + 91 * factor2, 255 * factor1 + 206 * factor2, 255 * factor1 + 255 * factor2);
//               break;
//     }
//   }
//   if(strip_0.effStep >= 60) {strip_0.Reset(); return 0x03; }
//   else strip_0.effStep++;
//   return 0x01;
// }


// ##################### PATTERNS ########################

bool rainbow = false;             // The rainbow effect is turned off on startup
unsigned long start, end = 0;
unsigned long prevMillis = millis();
int hue = 0;

void loop() {
  webSocket.loop();                           // constantly check for websocket events
  server.handleClient();                      // run the server
  ArduinoOTA.handle();                        // listen for OTA events

  if(rainbow) {                               // if the rainbow effect is turned on
    // if(millis() > prevMillis + 32) {          
    //   if(++hue == 360)                        // Cycle through the color wheel (increment by one degree every 32 ms)
    //     hue = 0;
    //   setHue(hue);                            // Set the RGB LED to the right color
    //   prevMillis = millis();
    // }
      // rainbowWave(200, 10);

      // FastLED.show();
        // Strobe(0xff, 0xff, 0xff, 10, 50, 10);
          // Fire(55,120,15);
            // theaterChaseRainbow(50);
              // RunningLights(0xff,0xff,0x00, 50);
              // DO I NEED COLOR CORRECTION? WHY IS #ed6f88 not pink?
  //             int delay = 1;
  // colorWipe(0x5b,0xce,0xfa, delay); // 5bcefa
  // colorWipe(0xF5,0x22,0x4c, delay); // f5a9b8 or ed6f88 oooor f5224c
  // colorWipe(0xff,0xff,0xff, delay); // ffffff
  // colorWipe(0xF5,0x22,0x4c, delay); // f5a9b8 or ed6f88 oooor f5224c
  // strips_loop();



  // colorWipe(0x5b,0xce,0xfa, delay); // 5bcefa

  
  
  }

  }




void startWiFi() { // Start a Wi-Fi access point, and try to connect to some given access points. Then wait for either an AP or STA connection
  WiFi.softAP(ssid, password);             // Start the access point
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started\r\n");

  wifiMulti.addAP("Modem LTE Orange", "mlekogrzybowe");

  wifiMulti.addAP("linksys_SES_6206", "Neo16pbsOsloPixu");
  wifiMulti.addAP("Orange-07BE", "mlekogrzybowe");   // add Wi-Fi networks you want to connect to

  Serial.println("Connecting");
  while (wifiMulti.run() != WL_CONNECTED && WiFi.softAPgetStationNum() < 1) {  // Wait for the Wi-Fi to connect
    delay(250);
    Serial.print('.');
  }
  Serial.println("\r\n");
  if(WiFi.softAPgetStationNum() == 0) {      // If the ESP is connected to an AP
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());             // Tell us what network we're connected to
    Serial.print("IP address:\t");
    Serial.print(WiFi.localIP());            // Send the IP address of the ESP8266 to the computer
  } else {                                   // If a station is connected to the ESP SoftAP
    Serial.print("Station connected to ESP8266 AP");
  }
  Serial.println("\r\n");
}

void startOTA() { // Start the OTA service
  ArduinoOTA.setHostname(OTAName);
  ArduinoOTA.setPassword(OTAPassword);

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
    // digitalWrite(LED_RED, 0);    // turn off the LEDs
    // digitalWrite(LED_GREEN, 0);
    // digitalWrite(LED_BLUE, 0);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\r\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("OTA ready\r\n");
}

void startSPIFFS() { // Start the SPIFFS and list all contents
  SPIFFS.begin();                             // Start the SPI Flash File System (SPIFFS)
  Serial.println("SPIFFS started. Contents:");
  {
    Dir dir = SPIFFS.openDir("/");
    while (dir.next()) {                      // List the file system contents
      String fileName = dir.fileName();
      size_t fileSize = dir.fileSize();
      Serial.printf("\tFS File: %s, size: %s\r\n", fileName.c_str(), formatBytes(fileSize).c_str());
    }
    Serial.printf("\n");
  }
}

void startWebSocket() { // Start a WebSocket server
  webSocket.begin();                          // start the websocket server
  webSocket.onEvent(webSocketEvent);          // if there's an incomming websocket message, go to function 'webSocketEvent'
  Serial.println("WebSocket server started.");
}

void startMDNS() { // Start the mDNS responder
  MDNS.begin(mdnsName);                        // start the multicast domain name server
  Serial.print("mDNS responder started: http://");
  Serial.print(mdnsName);
  Serial.println(".local");
}

void startServer() { // Start a HTTP server with a file read handler and an upload handler
  server.on("/edit.html",  HTTP_POST, []() {  // If a POST request is sent to the /edit.html address,
    server.send(200, "text/plain", ""); 
  }, handleFileUpload);                       // go to 'handleFileUpload'

  server.onNotFound(handleNotFound);          // if someone requests any other file or page, go to function 'handleNotFound'
                                              // and check if the file exists

  server.begin();                             // start the HTTP server
  Serial.println("HTTP server started.");
}

void handleNotFound(){ // if the requested file or page doesn't exist, return a 404 not found error
  if(!handleFileRead(server.uri())){          // check if the file exists in the flash memory (SPIFFS), if so, send it
    server.send(404, "text/plain", "404: File Not Found");
  }
}

bool handleFileRead(String path) { // send the right file to the client (if it exists)
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) path += "index.html";          // If a folder is requested, send the index file
  String contentType = getContentType(path);             // Get the MIME type
  String pathWithGz = path + ".gz";
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) { // If the file exists, either as a compressed archive, or normal
    if (SPIFFS.exists(pathWithGz))                         // If there's a compressed version available
      path += ".gz";                                         // Use the compressed verion
    File file = SPIFFS.open(path, "r");                    // Open the file
    size_t sent = server.streamFile(file, contentType);    // Send it to the client
    file.close();                                          // Close the file again
    Serial.println(String("\tSent file: ") + path);
    return true;
  }
  Serial.println(String("\tFile Not Found: ") + path);   // If the file doesn't exist, return false
  return false;
}

void handleFileUpload(){ // upload a new file to the SPIFFS
  HTTPUpload& upload = server.upload();
  String path;
  if(upload.status == UPLOAD_FILE_START){
    path = upload.filename;
    if(!path.startsWith("/")) path = "/"+path;
    if(!path.endsWith(".gz")) {                          // The file server always prefers a compressed version of a file 
      String pathWithGz = path+".gz";                    // So if an uploaded file is not compressed, the existing compressed
      if(SPIFFS.exists(pathWithGz))                      // version of that file must be deleted (if it exists)
         SPIFFS.remove(pathWithGz);
    }
    Serial.print("handleFileUpload Name: "); Serial.println(path);
    fsUploadFile = SPIFFS.open(path, "w");            // Open the file for writing in SPIFFS (create if it doesn't exist)
    path = String();
  } else if(upload.status == UPLOAD_FILE_WRITE){
    if(fsUploadFile)
      fsUploadFile.write(upload.buf, upload.currentSize); // Write the received bytes to the file
  } else if(upload.status == UPLOAD_FILE_END){
    if(fsUploadFile) {                                    // If the file was successfully created
      fsUploadFile.close();                               // Close the file again
      Serial.print("handleFileUpload Size: "); Serial.println(upload.totalSize);
      server.sendHeader("Location","/success.html");      // Redirect the client to the success page
      server.send(303);
    } else {
      server.send(500, "text/plain", "500: couldn't create file");
    }
  }
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) { // When a WebSocket message is received
  switch (type) {
    case WStype_DISCONNECTED:             // if the websocket is disconnected
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED: {              // if a new websocket connection is established
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        rainbow = false;                  // Turn rainbow off when a new connection is established
      }
      break;
    case WStype_TEXT:                     // if new text data is received
      // Serial.printf("[%u] get Text: %s\n", num, payload);
      if (payload[0] == '#') {            // we get RGB data
        uint32_t rgb = (uint32_t) strtol((const char *) &payload[1], NULL, 16);   // decode rgb data
        int r = ((rgb >> 20) & 0x3FF);                     // 10 bits per color, so R: bits 20-29
        int g = ((rgb >> 10) & 0x3FF);                     // G: bits 10-19
        int b =          rgb & 0x3FF;                      // B: bits  0-9

        r = r/4;
        g = g/4;
        b = b/4;

        for(int i = 0; i<NUM_LEDS; i++){
        leds[i].red = (uint8_t)r;                          // write it to the LED output pins
        leds[i].green = (uint8_t)g;
        leds[i].blue = (uint8_t)b;
        }
        Serial.print("R:");
        Serial.print(r);
        Serial.print(" G:");
        Serial.print(g);
        Serial.print(" B:");
        Serial.print(b);
        Serial.print("\n");
      } else if (payload[0] == 'R') {                      // the browser sends an R when the rainbow effect is enabled
        rainbow = true;
      } else if (payload[0] == 'N') {                      // the browser sends an N when the rainbow effect is disabled
        rainbow = false;
      }
      FastLED.show();
      break;
  }
}



String formatBytes(size_t bytes) { // convert sizes in bytes to KB and MB
  if (bytes < 1024) {
    return String(bytes) + "B";
  } else if (bytes < (1024 * 1024)) {
    return String(bytes / 1024.0) + "KB";
  } else if (bytes < (1024 * 1024 * 1024)) {
    return String(bytes / 1024.0 / 1024.0) + "MB";
  }
}

String getContentType(String filename) { // determine the filetype of a given filename, based on the extension
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

void setHue(int hue) { // Set the RGB LED to a given hue (color) (0° = Red, 120° = Green, 240° = Blue)
  hue %= 360;                   // hue is an angle between 0 and 359°
  float radH = hue*3.142/180;   // Convert degrees to radians
  float rf, gf, bf;
  
  if(hue>=0 && hue<120){        // Convert from HSI color space to RGB              
    rf = cos(radH*3/4);
    gf = sin(radH*3/4);
    bf = 0;
  } else if(hue>=120 && hue<240){
    radH -= 2.09439;
    gf = cos(radH*3/4);
    bf = sin(radH*3/4);
    rf = 0;
  } else if(hue>=240 && hue<360){
    radH -= 4.188787;
    bf = cos(radH*3/4);
    rf = sin(radH*3/4);
    gf = 0;
  }
  int r = rf*rf*1023;
  int g = gf*gf*1023;
  int b = bf*bf*1023;

          r = r/4;
        g = g/4;
        b = b/4;
  
        for(int i = 0; i<NUM_LEDS; i++){
        leds[i].red = (uint8_t)r;                          // write it to the LED output pins
        leds[i].green = (uint8_t)g;
        leds[i].blue = (uint8_t)b;
        }
      FastLED.show();

}
void rainbowWave(uint8_t thisSpeed, uint8_t deltaHue) {     // The fill_rainbow call doesn't support brightness levels.
 
// uint8_t thisHue = beatsin8(thisSpeed,0,255);                // A simple rainbow wave.
 uint8_t thisHue = beat8(thisSpeed,255);                     // A simple rainbow march.
  
 fill_rainbow(leds, NUM_LEDS, thisHue, deltaHue);            // Use FastLED's fill_rainbow routine.
 
} 
