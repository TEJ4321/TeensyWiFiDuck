/*
   Copyright (c) 2024 TEJ4321
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/TEJ4321/TeensyWiFiDuck
 */

#pragma once

#include <EEPROM.h>

namespace eeprom {
    void begin();
    void end();

    bool checkBootNum();
    void resetBootNum();

    template<typename T>
    void saveObject(const int address, const T& t) {
        EEPROM.put(address, t);

        EEPROM.commit();
    }

    template<typename T>
    void getObject(const int address, const T& t) {
        EEPROM.get(address, t);
    }
};