/*
 * RFM01S Tester
 *
 * Sample check to see if an RFM01S is responsive over SPI
 *
 * There's no version register, but disabling the FIFO produces sets bit 6:
 * - Reset the radio (0xFF00)
 * - Disables the FIFO (0xCE84, default is 0xCE85)
 * - Performs a status read (0x0000)
 * - Checks the 16-bit masked status is 0x400 (bit 6 of 16)
 */
#include <SPI.h>

// Pins that the RFM01S is connected to
#define RFM01S_DATA D12
#define RFM01S_NSEL D13

// An SPI command is two bytes long
uint16_t spi_command(uint16_t input) {
  digitalWrite(RFM01S_NSEL, LOW);
  uint16_t status = SPI.transfer16(input);
  digitalWrite(RFM01S_NSEL, HIGH);
  return status;
}

void setup() {
  // Serial console setup
  Serial.begin(115200);
  delay(5000);

  // Setup all non-SPI pins
  pinMode(RFM01S_DATA, INPUT);
  pinMode(RFM01S_NSEL, OUTPUT);
  
  // SPI Setup with RFM01S
#if defined(ARDUINO_CHALLENGER_2040_WIFI_RP2040)
  SPI.setRX(PIN_WIRE0_SDA); // Challenger 2040 WiFi fix
#endif
  SPI.begin();
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(RFM01S_NSEL, HIGH);
  
  // Software reset
  spi_command(0xFF00);
  delay(1000);
  // Disable FIFO
  spi_command(0xCE84);
}

void loop() {
  // Status read and bitmask for the bits we are looking for
  int status = spi_command(0x0000) & 0x400;

  // Visual output
  Serial.print(F("Status should read 0x400 with FIFO disabled: 0x"));
  Serial.print(status, HEX);
  if (status == 0x400)
    Serial.println(" **PASS**");
  else 
    Serial.println(" **FAIL**");

  delay(10000);
}