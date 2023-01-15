/*
  Copyright (c) 2022 fotonix@pm.me  All right reserved.

  This code is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
*/
#include <TinyWireS.h>
#include <DigiCDC.h>

// onRecive callback
void onReciveCB(uint8_t num_bytes) {
  uint8_t i;

// Sanity check
  if (num_bytes > 0) {
    // LED on
    digitalWrite(PB1, HIGH);
    // Read all bytes from I2C and put into USB serial buffer
    for (i = 0; i < num_bytes; i++) {
      SerialUSB.write(TinyWireS.receive());
    }
  }
}

void setup() {
  // Set LED pin as out
  pinMode(PB1, OUTPUT);
  // LED on
  digitalWrite(PB1, HIGH);
  // Initialize USB serial
  SerialUSB.begin();
  while (!SerialUSB) {};
  // Initialize USI as I2C slave @ address 0x22 (like FTDI chip)
  TinyWireS.begin(0x22);
  // Set callback
  TinyWireS.onReceive(onReciveCB);
}

void loop() {
  // Echo on USB serial  - for test
  if (SerialUSB.available()) {
    SerialUSB.write(SerialUSB.read());
  }
  // Check stop sequence
  TinyWireS_stop_check();
  // LED off
  digitalWrite(PB1, LOW);
}
