#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

const char* ssid = "ada-seattle";
const char* password = "Pass";

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

// Color constants
const char* rainbow = "rainbow";

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
      
      if (id == 0) // if color not rainbow, parse string by r, g, b
      {
//        const char* r = root["r"];
//        const char* g = root["g"];
//        const char* b = root["b"];
//        
//        colorWipe(strip.Color(r, g, b), 50);
          colorWipe(strip.Color(0, 0, 255, 0), 50); // Blue
      }
      
    } else { 
      Serial.println("Server Error"); // check thumbprint as possible solution since SSL certs change see README
    }
    http.end(); //Close connection
  }
  delay(30000); // 30 seconds

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
