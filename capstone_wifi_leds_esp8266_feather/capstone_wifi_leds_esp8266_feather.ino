#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const char* ssid = "CenturyLink0874";
const char* password = "pass";

#define PIN 2

#define NUM_LEDS 60

#define BRIGHTNESS 100

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

byte neopix_gamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

void setup() 
{
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  colorWipe(strip.Color(0, 0, 0, 255), 50); // White
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Connecting...");
  }
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) 
  {
    Serial.println("Connected!");
    HTTPClient http; //Object of class HTTPClient
    String thumbprint =   "08 3B 71 72 02 43 6E CA ED 42 86 93 BA 7E DF 81 C4 BC 62 30"; // to find thumbprint see view certificate in security tab of dev tools SHA-1
    String path = "https://color-our-sign-api.herokuapp.com/color";
    http.begin(path, thumbprint);
    int httpCode = http.GET();

    if (httpCode > 0) 
    {
      // Color constants
      const char* rainbow = "rainbow";
      const char* color1 = "{\"r\":244,\"g\":67,\"b\":54,\"a\":1}";
      const char* color2 = "{\"r\":233,\"g\":30,\"b\":99,\"a\":1}";
      const char* color3 = "{\"r\":156,\"g\":39,\"b\":176,\"a\":1}";
      const char* color4 = "{\"r\":103,\"g\":58,\"b\":183,\"a\":1}";
      const char* color5 = "{\"r\":63,\"g\":81,\"b\":181,\"a\":1}";
      const char* color6 = "{\"r\":33,\"g\":150,\"b\":243,\"a\":1}";
      const char* color7 = "{\"r\":3,\"g\":169,\"b\":244,\"a\":1}";
      const char* color8 = "{\"r\":0,\"g\":188,\"b\":212,\"a\":1}";
      const char* color9 = "{\"r\":0,\"g\":150,\"b\":136,\"a\":1}";
      const char* color10 = "{\"r\":76,\"g\":175,\"b\":80,\"a\":1}";
      const char* color11 = "{\"r\":139,\"g\":195,\"b\":74,\"a\":1}";
      const char* color12 = "{\"r\":205,\"g\":220,\"b\":57,\"a\":1}";
      const char* color13 = "{\"r\":255,\"g\":235,\"b\":59,\"a\":1}";
      const char* color14 = "{\"r\":255,\"g\":193,\"b\":7,\"a\":1}";
      const char* color15 = "{\"r\":255,\"g\":152,\"b\":0,\"a\":1}";
      const char* color16 = "{\"r\":255,\"g\":87,\"b\":34,\"a\":1}";
      

      const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 370;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(http.getString());
 
      int id = root["id"]; 
      const char* color = root["color"];

      Serial.print("Color:");
      Serial.println(color);
      Serial.print("id:");
      Serial.println(id);

      if (color == false)
      {
        colorWipe(strip.Color(255, 0, 0, 0), 50); // Red
      }

      
      if (strcmp (color, color1) == 0) 
      {    
          colorWipe(strip.Color(244, 67, 54, 0), 50); // "#f44336"
      }

      if (strcmp (color, color2) == 0) 
      {    
          colorWipe(strip.Color(233, 30, 99, 0), 50); // "#e91e63"
      }

      if (strcmp (color, color3) == 0) 
      {    
          colorWipe(strip.Color(156, 39, 176, 0), 50); // "#9c27b0"
      }

      if (strcmp (color, color4) == 0) 
      {    
          colorWipe(strip.Color(103, 58, 183, 0), 50); // "#673ab7"
      }

      if (strcmp (color, color5) == 0) 
      {    
          colorWipe(strip.Color(63, 81, 181, 0), 50); // "#3f51b5"
      }

      if (strcmp (color, color6) == 0) 
      {    
          colorWipe(strip.Color(33, 150, 243, 0), 50); // "#2196f3"
      }

      if (strcmp (color, color7) == 0) 
      {    
          colorWipe(strip.Color(3, 169, 244, 0), 50); // "#03a9f4"
      }

      if (strcmp (color, color8) == 0) 
      {    
          colorWipe(strip.Color(0, 188, 212, 0), 50); // "#00bcd4"
      }

      if (strcmp (color, color9) == 0) 
      {    
          colorWipe(strip.Color(0, 150, 136, 0), 50); // "#009688"
      }

      if (strcmp (color, color10) == 0) 
      {    
          colorWipe(strip.Color(76, 175, 76, 0), 50); // "#4caf50"
      }

      if (strcmp (color, color11) == 0) 
      {    
          colorWipe(strip.Color(139, 195, 74, 0), 50); // "#8bc34a"
      }

      if (strcmp (color, color12) == 0) 
      {    
          colorWipe(strip.Color(205, 220, 57, 0), 50); // "#cddc39"
      }

      if (strcmp (color, color13) == 0) 
      {    
          colorWipe(strip.Color(255, 235, 59, 0), 50); // "#ffeb3b"
      }

      if (strcmp (color, color14) == 0) 
      {    
          colorWipe(strip.Color(255, 193, 7, 0), 50); // "#ffc107"
      }

      if (strcmp (color, color15) == 0) 
      {    
          colorWipe(strip.Color(255, 152, 0, 0), 50); // "#ff9800"
      }

      if (strcmp (color, color16) == 0) 
      {    
          colorWipe(strip.Color(255, 87, 34, 0), 50); // "#ff5722"
      }
      
      if (strcmp (color, rainbow) == 0) // if color rainbow, fade in rainbow
      {
        rainbowFade2White(3,3,1);
      }
      
    } else { 
      Serial.println("Server Error"); // check thumbprint as possible solution since SSL certs change see README
    }
    http.end(); //Close connection
  }
  delay(500); // half a second

}

// COLOR COMMANDS
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
   strip.setPixelColor(i, c);
   strip.show();
   delay(wait);
  }
 }

 void rainbowFade2White(uint8_t wait, int rainbowLoops, int whiteLoops) {
  float fadeMax = 100.0;
  int fadeVal = 0;
  uint32_t wheelVal;
  int redVal, greenVal, blueVal;

  for(int k = 0 ; k < rainbowLoops ; k ++){
    
    for(int j=0; j<256; j++) { // 5 cycles of all colors on wheel

      for(int i=0; i< strip.numPixels(); i++) {

        wheelVal = Wheel(((i * 256 / strip.numPixels()) + j) & 255);

        redVal = red(wheelVal) * float(fadeVal/fadeMax);
        greenVal = green(wheelVal) * float(fadeVal/fadeMax);
        blueVal = blue(wheelVal) * float(fadeVal/fadeMax);

        strip.setPixelColor( i, strip.Color( redVal, greenVal, blueVal ) );

      }

      //First loop, fade in!
      if(k == 0 && fadeVal < fadeMax-1) {
          fadeVal++;
      }

//      //Last loop, fade out!
//      else if(k == rainbowLoops - 1 && j > 255 - fadeMax ){
//          fadeVal--;
//      }

        strip.show();
        delay(wait);
    }
  
  }
  delay(500);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}

uint8_t red(uint32_t c) {
  return (c >> 16);
}
uint8_t green(uint32_t c) {
  return (c >> 8);
}
uint8_t blue(uint32_t c) {
  return (c);
}
