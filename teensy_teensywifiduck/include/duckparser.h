/*
   Copyright (c) 2024 TEJ4321
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/TEJ4321/TeensyWiFiDuck
 */

#include <stddef.h> // size_t
#include <Keyboard.h> // Include Keyboard.h here

namespace duckparser {
  void parse(const char* str, size_t len);
  int getRepeats();
  unsigned int getDelayTime();
};