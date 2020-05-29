#include <FastLED.h>
#include <SPI.h>

const int LEDDataPin = 17;
const int SftLoadPin = 5;
static const int spiCLK = 1000000; //Set the clock speed to 1MHz

CRGB led[8];

byte SftRegister;
SPIClass * vspi = NULL;

void setup() {
  FastLED.addLeds<NEOPIXEL, LEDDataPin>(led, 8);
  FastLED.setBrightness(50);
  vspi = new SPIClass(VSPI);
  vspi->begin(18, 19, -1, 5); //SCK, MISO, MOSI, SS
  pinMode(SftLoadPin, OUTPUT);
  digitalWrite(SftLoadPin, 1);
  
  Serial.begin(115200);
  
} //End Setup

void loop() {
  vspi->beginTransaction(SPISettings(spiCLK, MSBFIRST, SPI_MODE2));
  digitalWrite(SftLoadPin, 0);
  delayMicroseconds(25);
  digitalWrite(SftLoadPin, 1);
  vspi->endTransaction();
  SftRegister = vspi->transfer(0x00);
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

//vspi->beginTransaction(SPISettings(spiCLK, LSBFIRST, SPI_MODE0));
//digitalWrite(latch_pin, 0);

//vspi->transfer(chipcontrol);
//vspi->transfer(adcswrre);
//vspi->transfer(dataspi);

//vspi->endTransaction();
//digitalWrite(latch_pin, 1);
