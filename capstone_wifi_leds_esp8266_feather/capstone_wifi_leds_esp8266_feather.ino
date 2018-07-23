#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const char* ssid = "ada-seattle";
const char* password = "AdaLovelaceCodesIt";

#define PIN 2

#define NUM_LEDS 58

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
      

      const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 370;
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(http.getString());
 
      String color = root["color"];
      const char* id = root["id"];

      Serial.print("Color:");
      Serial.println(color);
      Serial.print("id:");
      Serial.println(id);

      int num = color.toInt();

      if (color == false)
      {
        colorWipe(strip.Color(255, 0, 0, 0), 50); // Red
      }

      switch (num) {
        case 1:
          colorWipe(strip.Color(255, 0, 0, 0), 50); // '#ff0000'
          break;
        case 2:
          colorWipe(strip.Color(255, 165, 0, 0), 50); // '#ffa500'
          break;
        case 3:
          colorWipe(strip.Color(255, 255, 0, 0), 50); // '#ffff00'
          break;
        case 4:
          colorWipe(strip.Color(0, 255, 0, 0), 50); // '#00ff00'
          break;
        case 5:
          colorWipe(strip.Color(0, 0, 255, 0), 50); // '#0000ff'
          break;
        case 6:
          colorWipe(strip.Color(85, 26, 139, 0), 50); // '#551a8b'
          break;
        case 7:
          colorWipe(strip.Color(3, 169, 244, 0), 50); // '#03a9f4'
          break;
        case 8:
          colorWipe(strip.Color(233, 30, 99, 0), 50); // '#e91e63'
          break;
        case 9:
          colorWipe(strip.Color(0, 150, 136, 0), 50); // '#009688'
          break;
        case 10:
          colorWipe(strip.Color(128, 0, 0, 0), 50); // '#800000'
          break;
        case 11:
          colorWipe(strip.Color(255, 0, 255, 0), 50); // '#ff00ff'
          break;
        case 12:
          colorWipe(strip.Color(0, 102, 0, 0), 50); // '#006600'
          break;
        case 13:
          rainbowFade2White(50, 1, 0); // RAINBOW
        default:
          colorWipe(strip.Color(0, 0, 0, 255), 50); // '#ffffff'
          break;
      }
      
    } else { 
      Serial.println("Server Error"); // check thumbprint as possible solution since SSL certs change see README
    }
    http.end(); //Close connection
  }
  delay(100); // half a second

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

      //Last loop, fade out!
      else if(k == rainbowLoops - 1 && j > 255 - fadeMax ){
          fadeVal--;
      }

        strip.show();
        delay(wait);
    }
  
  }



  delay(500);


  for(int k = 0 ; k < whiteLoops ; k ++){

    for(int j = 0; j < 256 ; j++){

        for(uint16_t i=0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, strip.Color(0,0,0, neopix_gamma[j] ) );
          }
          strip.show();
        }

        delay(2000);
    for(int j = 255; j >= 0 ; j--){

        for(uint16_t i=0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, strip.Color(0,0,0, neopix_gamma[j] ) );
          }
          strip.show();
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
