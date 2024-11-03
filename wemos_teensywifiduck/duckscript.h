/*
   Copyright (c) 2024 TEJ4321
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/TEJ4321/TeensyWiFiDuck
 */

#pragma once

#include <Arduino.h> // String

namespace duckscript {
    void runTest();
    void run(String fileName);

    void nextLine();
    void repeat();
    void stopAll();
    void stop(String fileName);

    bool isRunning();
    String currentScript();
};