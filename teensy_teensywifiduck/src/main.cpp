/*
   Copyright (c) 2024 TEJ4321
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/TEJ4321/TeensyWiFiDuck
 */

#include "config.h"
#include "debug.h"
#include <Arduino.h>
#include <Keyboard.h>
#include <Mouse.h>
#include "led.h"
#include "com.h"
#include "duckparser.h"

// ===== SETUP ====== //
void setup() {
    debug_init();

    led::begin();
    Keyboard.begin();
    Mouse.begin();
    com::begin();

    debugs("Started! ");
    debugln(VERSION);
}

// ===== LOOOP ===== //
void loop() {
    com::update();
    if (com::hasData()) {
        const buffer_t& buffer = com::getBuffer();

        debugs("Interpreting: ");

        for (size_t i = 0; i<buffer.len; i++) debug(buffer.data[i]);

        duckparser::parse(buffer.data, buffer.len);

        com::sendDone();
    }
}