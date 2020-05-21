//Arduino Pro Mini (ATmega328P 5V, 16MHz) with 74HC165N shift register and a WS2812B 5050 LED strip with 8 LEDs
#include <FastLED.h>
#include <SPI.h>
  //Arduino Pin 11 = MOSI - Not connected for this application
  //Arduino Pin 12 = MISO - Connects to Pin 9 (QH) of the shift register
  //Arduino Pin 13 = SCK - Connects to Pin 2 (CLOCK) of the shift register
  //Arduino Pin 7 = SS - Connects to Pin 1 (SHIFT/LOAD) of the shift register
  //Arduino Pim 6 = LED data line

#define SftLoadPin 7
#define LEDDataPin 6

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
  Serial.begin(9600);
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
