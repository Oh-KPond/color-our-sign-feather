All hardware code was written using the Arduino IDE

## Hardware
- [Adafruit Feather HUZZAH with ESP8266 WiFi](https://www.adafruit.com/product/3404)
- [Adafruit NeoPixel Digital RGB LED Strip - White 60 LED - WHITE](https://www.adafruit.com/product/1138?length=1)
- [Custom LED Back Lit Sign](https://www.etsy.com/listing/564193854/custom-led-back-lit-sign-light-up-sign?ref=shop_home_feat_3)
- 5V DC power supply (obtained from Amazon bought lights included with the sign)
- Capacitor (1000 µF, 6.3V)
- Diode
- Variety of male to female wires, to connect wires to pins

## Assembly
- Adafruit Feather HUZZAH with ESP8266 WiFi
  - Power connects to Ground PIN and USB PIN (with diode in between power & pin)
  - Data PIN 2 connects to LED data-in pad
- Adafruit NeoPixel Digital RGB LED Strip
  - Power connects to 5V and Ground pads
  - LED data-in pad connects to Data PIN 2 on the Feather
- Power source includes the capacitor between the wall plug and other hardware

- LED strip with silicon sleeve removed is held in place with paperclips that have been hot-glued into the box by one end
