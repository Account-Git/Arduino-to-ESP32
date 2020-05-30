#include <FastLED.h>
#include <SPI.h>

const int LEDDataPin = 17;
const int SftLoadPin = 5;

CRGB led[8];

byte SftRegister;

void setup() {
  FastLED.addLeds<NEOPIXEL, LEDDataPin>(led, 8);
  FastLED.setBrightness(50);
  SPI.begin();
  pinMode(SftLoadPin, OUTPUT);
  digitalWrite(SftLoadPin, 1);
  
  Serial.begin(115200);
  
} //End Setup

void loop() {
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE2));
  digitalWrite(SftLoadPin, 0);
  delayMicroseconds(5);
  digitalWrite(SftLoadPin, 1);
  SPI.endTransaction();
  SftRegister = SPI.transfer(0x00);
  for (int x = 0; x < 8; x++) {
    Serial.print(bitRead(SftRegister, x));
    if (x == 7) { Serial.println(); }
    if (bitRead(SftRegister, x) == 0) {
      led[x] = CRGB(255, 0, 0);
    }
    else {
      led[x] = CRGB(0, 0, 255);
    }
  }
  FastLED.delay(500);
} //End Loop
