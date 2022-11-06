RFM01S Reference
================
This contains a very brief amount of detail around the RFM01 Receiver for Arduino.

The radio itself is simple when compared to a RFM69HCW:
- Based on the Silicon Labs Si4322
- 12ix 16-bit commands with compound variables
- No preamble detection / timing
- Fixed syncword of 0x2DD4 (0010 1101 1101 0100)
- FIFO of just 16 bits, so limited application

It seems to be less fiddly with raw data versus the RFM69HCW.

The only code in this repo is to check the status over SPI when FIFO is disabled.

Tips
====
- The SMD version has 7 x 2 pins - it's possible to solder it two 6-pin headers with a little bending, avoiding the two center contacts (DLCK/CFIL/FFIT & VDI).
- Can fit onto a FeatherWing Proto.
- The Data Filter command: "Digital filter" is FSK binary out.
- The detailed datasheet here is becoming hard to find, so I've included it here.
