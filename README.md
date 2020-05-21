# Arduino-to-ESP32
Porting Arduino shift register sketch to ESP32

Included are two sketches created in the Arduino IDE.
The ArduinoSketch.ino file is a WORKING copy of a test sketch, designed to test a 74HC165 shift register with an addessable LED strip.
The ESP32Sketch.ino is a copy of ArduinoSketch.ino with the pin numbers and Serial buad rate changed.
In theory, the ESP32Sketch.ino should work with the ESP32 microcontroller. However, it doesn't appear too.

ESP32Sketch.ino compiles fine and uploads easily to the ESP32 (as it should, the sketch really coudn't be any simpler).
