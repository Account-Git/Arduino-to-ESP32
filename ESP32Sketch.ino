//ESP32 (NodeMCU-32S clone) with 74HC165N shift register and a WS2812B 5050 LED strip with 8 LEDs
#include <FastLED.h>
#include <SPI.h>
  //GPIO Pin 23 = MOSI - Not connected for this application
  //GPIO Pin 19 = MISO - Connects to Pin 9 (QH) of the shift register
  //GPIO Pin 18 = SCK - Connects to Pin 2 (CLOCK) of the shift register
  //GPIO Pin 5 = SS - Connects to Pin 1 (SHIFT/LOAD) of the shift regoster
  //GPIO Pin 17 - LED data line

#define SftLoadPin 5
#define LEDDataPin 17

CRGB led[8];

byte SftRegister;

void setup() {
  FastLED.addLeds<NEOPIXEL, LEDDataPin>(led, 8);
  FastLED.setBrightness(75);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV128);
  SPI.begin();
  pinMode(SftLoadPin, OUTPUT);
  digitalWrite(SftLoadPin, HIGH);
  Serial.begin(115200);
} //End Setup

void loop() {
  digitalWrite(SftLoadPin, LOW);
  delay(5);
  digitalWrite(SftLoadPin, HIGH);
  SftRegister = SPI.transfer(0x00);
  Serial.println(SftRegister, BIN);
  for (int x = 0; x < 8; x++) {
    if (bitRead(SftRegister, x) == 0) {
      led[x] = CRGB(255, 0, 0);
    }
    else {
      led[x] = CRGB(0, 0, 255);
    }
  }
  FastLED.delay(100);
} //End Loop
