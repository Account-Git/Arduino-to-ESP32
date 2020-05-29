# Arduino-to-ESP32
Porting Arduino shift register sketch to ESP32

Included are two sketches created in the Arduino IDE.
The ArduinoSketch.ino file is a WORKING copy of a test sketch, designed to test a 74HC165 shift register with an addessable LED strip.
The ESP32Sketch.ino is a copy of ArduinoSketch.ino with the pin numbers and Serial buad rate changed.
In theory, the ESP32Sketch.ino should work with the ESP32 microcontroller. However, it doesn't appear too.

ESP32Sketch.ino compiles fine and uploads easily to the ESP32 (as it should, the sketch really coudn't be any simpler).

So what's the problem?

Let's go back to the Arduino sketch.
This sketch works fine, that is to say:
When one or more of the data input pins (D0-D7) on the shift register is pulled HIGH or LOW, the corresponding bit in the byte transfered to the Arduino is set to either 1 or 0.

If we now look at the ESP32 sketch:
When one or more of the data input pins (D0-D7) on the shift register is pulled HIGH or LOW, the byte transfered to the ESP32 is garbage.
By garbage, I mean the bits do not reflect the state of the input pins of the shift register.

UPDATE:

After lots of tinkering I have now added a new sketch to this repository, NEW-ESP32-SPI-TEST.ico
The SPI transfer is still not working correctly, but progress has been made.
Here are the results from the new sketch:

With all input pins (D0-D7) on the 74HC165 pulled HIGH, we receive a byte of: 11111111
If we (individually) pull each input pin LOW there is no change to the byte received, except for on the last pin (D7).
With D7 pulled LOW, we receive a byte of: 11111110, although the 0 on the eighth bit is intermittent.
If we keep D7 pulled LOW and then individually cycle through the other inputs again we get:

D7 + D0 LOW = 11111110 (0 is intermittent)

D7 + D1 LOW = 11111011 (0 is steady)

D7 + D2 LOW = 11110111 (0 is steady)

D7 + D3 LOW = 11101110 (0s are steady)

D7 + D4 LOW = 11011011 (0s are steady)

D7 + D5 LOW = 10101010 (first three 0s are intermittent, bit eight 0 is steady)

D7 + D6 LOW = 01111110 (bit one 0 is intermittent, bit eight 0 is steady)

So, now the problems are:
1. Why are we getting intermittent readings in some configurations?
2. Why do we receive 0s on some bits in the byte when the corresponding inputs are pulled HIGH?
3. Why is the seventh bit ALWAYS 1?

With even more tinkering we get these results:

This time we start with all inputs on the shift register pulled LOW, then individually pull each input HIGH.

All LOW = 00000000

D0 HIGH = 10000000

D1 HIGH = 01000000

D2 HIGH = 00100000

D3 HIGH = 00010000

D4 HIGH = 10001000

D5 HIGH = 00100100

D6 HIGH = 10101010

D7 HIGH = 11111111

So what did we change to get these latest results?
We have changed the SPI_MODE and set the bit order back to MSBFIRST. On the previous test we had the bit order set to LSBFIRST and we also had SPI_MODE0 set. After testing, SPI_MODE0, SPI_MODE1 and SPI_MODE3 yielded the same results, but changing to SPI_MODE2 gave us these new results, which are much nearer to our goal.
