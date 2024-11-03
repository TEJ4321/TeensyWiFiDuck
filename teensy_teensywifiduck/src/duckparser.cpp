/*
   Copyright (c) 2024 TEJ4321
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/TEJ4321/TeensyWiFiDuck
 */

#include "duckparser.h"

#include "config.h"
#include "debug.h"
#include <Keyboard.h>
#include <Mouse.h>
#include <Arduino.h>
#include <stdarg.h>
#include "led.h"

extern "C" {
 #include "parser.h" // parse_lines
}

#define CASE_INSENSETIVE 0
#define CASE_SENSETIVE 1

namespace duckparser {
    // ====== PRIVATE ===== //
    bool inString  = false;
    bool inComment = false;

    int defaultDelay = 5;
    int repeatNum    = 0;

    unsigned long interpretTime  = 0;
    unsigned long sleepStartTime = 0;
    unsigned long sleepTime      = 0;

    void type(const char* str, size_t len) {
        Keyboard.write(str, len);
    }

    void press(const char* str, size_t len) {
        // Letters        
        if (compare(str, len, "A", CASE_INSENSETIVE)) Keyboard.press(KEY_A);
        else if (compare(str, len, "B", CASE_INSENSETIVE)) Keyboard.press(KEY_B);
        else if (compare(str, len, "C", CASE_INSENSETIVE)) Keyboard.press(KEY_C);
        else if (compare(str, len, "D", CASE_INSENSETIVE)) Keyboard.press(KEY_D);
        else if (compare(str, len, "E", CASE_INSENSETIVE)) Keyboard.press(KEY_E);
        else if (compare(str, len, "F", CASE_INSENSETIVE)) Keyboard.press(KEY_F);
        else if (compare(str, len, "G", CASE_INSENSETIVE)) Keyboard.press(KEY_G);
        else if (compare(str, len, "H", CASE_INSENSETIVE)) Keyboard.press(KEY_H);
        else if (compare(str, len, "I", CASE_INSENSETIVE)) Keyboard.press(KEY_I);
        else if (compare(str, len, "J", CASE_INSENSETIVE)) Keyboard.press(KEY_J);
        else if (compare(str, len, "K", CASE_INSENSETIVE)) Keyboard.press(KEY_K);
        else if (compare(str, len, "L", CASE_INSENSETIVE)) Keyboard.press(KEY_L);
        else if (compare(str, len, "M", CASE_INSENSETIVE)) Keyboard.press(KEY_M);
        else if (compare(str, len, "N", CASE_INSENSETIVE)) Keyboard.press(KEY_N);
        else if (compare(str, len, "O", CASE_INSENSETIVE)) Keyboard.press(KEY_O);
        else if (compare(str, len, "P", CASE_INSENSETIVE)) Keyboard.press(KEY_P);
        else if (compare(str, len, "Q", CASE_INSENSETIVE)) Keyboard.press(KEY_Q);
        else if (compare(str, len, "R", CASE_INSENSETIVE)) Keyboard.press(KEY_R);
        else if (compare(str, len, "S", CASE_INSENSETIVE)) Keyboard.press(KEY_S);
        else if (compare(str, len, "T", CASE_INSENSETIVE)) Keyboard.press(KEY_T);
        else if (compare(str, len, "U", CASE_INSENSETIVE)) Keyboard.press(KEY_U);
        else if (compare(str, len, "V", CASE_INSENSETIVE)) Keyboard.press(KEY_V);
        else if (compare(str, len, "W", CASE_INSENSETIVE)) Keyboard.press(KEY_W);
        else if (compare(str, len, "X", CASE_INSENSETIVE)) Keyboard.press(KEY_X);
        else if (compare(str, len, "Y", CASE_INSENSETIVE)) Keyboard.press(KEY_Y);
        else if (compare(str, len, "Z", CASE_INSENSETIVE)) Keyboard.press(KEY_Z);

        // Numbers
        else if (compare(str, len, "0", CASE_SENSETIVE)) Keyboard.press(KEY_0);
        else if (compare(str, len, "1", CASE_SENSETIVE)) Keyboard.press(KEY_1);
        else if (compare(str, len, "2", CASE_SENSETIVE)) Keyboard.press(KEY_2);
        else if (compare(str, len, "3", CASE_SENSETIVE)) Keyboard.press(KEY_3);
        else if (compare(str, len, "4", CASE_SENSETIVE)) Keyboard.press(KEY_4);
        else if (compare(str, len, "5", CASE_SENSETIVE)) Keyboard.press(KEY_5);
        else if (compare(str, len, "6", CASE_SENSETIVE)) Keyboard.press(KEY_6);
        else if (compare(str, len, "7", CASE_SENSETIVE)) Keyboard.press(KEY_7);
        else if (compare(str, len, "8", CASE_SENSETIVE)) Keyboard.press(KEY_8);
        else if (compare(str, len, "9", CASE_SENSETIVE)) Keyboard.press(KEY_9);

        // Special Keys
        else if (compare(str, len, "\\", CASE_SENSETIVE) || compare(str, len, "BACKSLASH", CASE_SENSETIVE)) Keyboard.press(KEY_BACKSLASH);
        else if (compare(str, len, "/", CASE_SENSETIVE) || compare(str, len, "SLASH", CASE_SENSETIVE)) Keyboard.press(KEY_SLASH);
        else if (compare(str, len, ".", CASE_SENSETIVE) || compare(str, len, "PERIOD", CASE_SENSETIVE)) Keyboard.press(KEY_PERIOD);
        else if (compare(str, len, ",", CASE_SENSETIVE) || compare(str, len, "COMMA", CASE_SENSETIVE)) Keyboard.press(KEY_COMMA);
        else if (compare(str, len, "-", CASE_SENSETIVE) || compare(str, len, "MINUS", CASE_SENSETIVE)) Keyboard.press(KEY_MINUS);
        else if (compare(str, len, ";", CASE_SENSETIVE) || compare(str, len, "SEMICOLON", CASE_SENSETIVE)) Keyboard.press(KEY_SEMICOLON);
        else if (compare(str, len, "[", CASE_SENSETIVE) || compare(str, len, "LEFT_BRACE", CASE_SENSETIVE)) Keyboard.press(KEY_LEFT_BRACE);
        else if (compare(str, len, "]", CASE_SENSETIVE) || compare(str, len, "RIGHT_BRACE", CASE_SENSETIVE)) Keyboard.press(KEY_RIGHT_BRACE);
        else if (compare(str, len, "\"", CASE_SENSETIVE) || compare(str, len, "QUOTE", CASE_SENSETIVE)) Keyboard.press(KEY_QUOTE);
        else if (compare(str, len, "ENTER", CASE_SENSETIVE) || compare(str, len, "RETURN", CASE_SENSETIVE)) Keyboard.press(KEY_ENTER);
        else if (compare(str, len, "MENU", CASE_SENSETIVE) || compare(str, len, "APP", CASE_SENSETIVE)) Keyboard.press(KEY_MENU);
        else if (compare(str, len, "DELETE", CASE_SENSETIVE)) Keyboard.press(KEY_DELETE);
        else if (compare(str, len, "BACKSPACE", CASE_SENSETIVE)) Keyboard.press(KEY_BACKSPACE);
        else if (compare(str, len, "HOME", CASE_SENSETIVE)) Keyboard.press(KEY_HOME);
        else if (compare(str, len, "INSERT", CASE_SENSETIVE)) Keyboard.press(KEY_INSERT);
        else if (compare(str, len, "PAGEUP", CASE_SENSETIVE)) Keyboard.press(KEY_PAGE_UP);
        else if (compare(str, len, "PAGEDOWN", CASE_SENSETIVE)) Keyboard.press(KEY_PAGE_DOWN);
        else if (compare(str, len, "UPARROW", CASE_SENSETIVE) || compare(str, len, "UP", CASE_SENSETIVE)) Keyboard.press(KEY_UP);
        else if (compare(str, len, "DOWNARROW", CASE_SENSETIVE) || compare(str, len, "DOWN", CASE_SENSETIVE)) Keyboard.press(KEY_DOWN);
        else if (compare(str, len, "LEFTARROW", CASE_SENSETIVE) || compare(str, len, "LEFT", CASE_SENSETIVE)) Keyboard.press(KEY_LEFT);
        else if (compare(str, len, "RIGHTARROW", CASE_SENSETIVE) || compare(str, len, "RIGHT", CASE_SENSETIVE)) Keyboard.press(KEY_RIGHT);
        else if (compare(str, len, "TAB", CASE_SENSETIVE)) Keyboard.press(KEY_TAB);
        else if (compare(str, len, "END", CASE_SENSETIVE)) Keyboard.press(KEY_END);
        else if (compare(str, len, "ESC", CASE_SENSETIVE) || compare(str, len, "ESCAPE", CASE_SENSETIVE)) Keyboard.press(KEY_ESC);
        else if (compare(str, len, "SPACE", CASE_SENSETIVE)) Keyboard.press(KEY_SPACE);
        else if (compare(str, len, "PAUSE", CASE_SENSETIVE) || compare(str, len, "BREAK", CASE_SENSETIVE)) Keyboard.press(KEY_PAUSE);
        else if (compare(str, len, "CAPSLOCK", CASE_SENSETIVE) || compare(str, len, "CAPS", CASE_SENSETIVE) || compare(str, len, "CAPS_LOCK", CASE_SENSETIVE)) Keyboard.press(KEY_CAPS_LOCK);
        else if (compare(str, len, "NUMLOCK", CASE_SENSETIVE) || compare(str, len, "NUM_LOCK", CASE_SENSETIVE)) Keyboard.press(KEY_NUM_LOCK);
        else if (compare(str, len, "PRINTSCREEN", CASE_SENSETIVE) || compare(str, len, "PRTSC", CASE_SENSETIVE) || compare(str, len, "PRINT_SCREEN", CASE_SENSETIVE)) Keyboard.press(KEY_PRINTSCREEN);
        else if (compare(str, len, "SCROLLLOCK", CASE_SENSETIVE) || compare(str, len, "SCRLK", CASE_SENSETIVE) || compare(str, len, "SCROLL_LOCK", CASE_SENSETIVE)) Keyboard.press(KEY_SCROLL_LOCK);

        // Function Keys
        else if (compare(str, len, "F1", CASE_SENSETIVE)) Keyboard.press(KEY_F1);
        else if (compare(str, len, "F2", CASE_SENSETIVE)) Keyboard.press(KEY_F2);
        else if (compare(str, len, "F3", CASE_SENSETIVE)) Keyboard.press(KEY_F3);
        else if (compare(str, len, "F4", CASE_SENSETIVE)) Keyboard.press(KEY_F4);
        else if (compare(str, len, "F5", CASE_SENSETIVE)) Keyboard.press(KEY_F5);
        else if (compare(str, len, "F6", CASE_SENSETIVE)) Keyboard.press(KEY_F6);
        else if (compare(str, len, "F7", CASE_SENSETIVE)) Keyboard.press(KEY_F7);
        else if (compare(str, len, "F8", CASE_SENSETIVE)) Keyboard.press(KEY_F8);
        else if (compare(str, len, "F9", CASE_SENSETIVE)) Keyboard.press(KEY_F9);
        else if (compare(str, len, "F10", CASE_SENSETIVE)) Keyboard.press(KEY_F10);
        else if (compare(str, len, "F11", CASE_SENSETIVE)) Keyboard.press(KEY_F11);
        else if (compare(str, len, "F12", CASE_SENSETIVE)) Keyboard.press(KEY_F12);
        else if (compare(str, len, "F13", CASE_SENSETIVE)) Keyboard.press(KEY_F13);
        else if (compare(str, len, "F14", CASE_SENSETIVE)) Keyboard.press(KEY_F14);
        else if (compare(str, len, "F15", CASE_SENSETIVE)) Keyboard.press(KEY_F15);
        else if (compare(str, len, "F16", CASE_SENSETIVE)) Keyboard.press(KEY_F16);
        else if (compare(str, len, "F17", CASE_SENSETIVE)) Keyboard.press(KEY_F17);
        else if (compare(str, len, "F18", CASE_SENSETIVE)) Keyboard.press(KEY_F18);
        else if (compare(str, len, "F19", CASE_SENSETIVE)) Keyboard.press(KEY_F19);
        else if (compare(str, len, "F20", CASE_SENSETIVE)) Keyboard.press(KEY_F20);
        else if (compare(str, len, "F21", CASE_SENSETIVE)) Keyboard.press(KEY_F21);
        else if (compare(str, len, "F22", CASE_SENSETIVE)) Keyboard.press(KEY_F22);
        else if (compare(str, len, "F23", CASE_SENSETIVE)) Keyboard.press(KEY_F23);
        else if (compare(str, len, "F24", CASE_SENSETIVE)) Keyboard.press(KEY_F24);
        

        // NUMPAD KEYS
        else if (compare(str, len, "NUM_0", CASE_SENSETIVE) || compare(str, len, "KEYPAD_0", CASE_SENSETIVE)) Keyboard.press(KEYPAD_0);
        else if (compare(str, len, "NUM_1", CASE_SENSETIVE) || compare(str, len, "KEYPAD_1", CASE_SENSETIVE)) Keyboard.press(KEYPAD_1);
        else if (compare(str, len, "NUM_2", CASE_SENSETIVE) || compare(str, len, "KEYPAD_2", CASE_SENSETIVE)) Keyboard.press(KEYPAD_2);
        else if (compare(str, len, "NUM_3", CASE_SENSETIVE) || compare(str, len, "KEYPAD_3", CASE_SENSETIVE)) Keyboard.press(KEYPAD_3);
        else if (compare(str, len, "NUM_4", CASE_SENSETIVE) || compare(str, len, "KEYPAD_4", CASE_SENSETIVE)) Keyboard.press(KEYPAD_4);
        else if (compare(str, len, "NUM_5", CASE_SENSETIVE) || compare(str, len, "KEYPAD_5", CASE_SENSETIVE)) Keyboard.press(KEYPAD_5);
        else if (compare(str, len, "NUM_6", CASE_SENSETIVE) || compare(str, len, "KEYPAD_6", CASE_SENSETIVE)) Keyboard.press(KEYPAD_6);
        else if (compare(str, len, "NUM_7", CASE_SENSETIVE) || compare(str, len, "KEYPAD_7", CASE_SENSETIVE)) Keyboard.press(KEYPAD_7);
        else if (compare(str, len, "NUM_8", CASE_SENSETIVE) || compare(str, len, "KEYPAD_8", CASE_SENSETIVE)) Keyboard.press(KEYPAD_8);
        else if (compare(str, len, "NUM_9", CASE_SENSETIVE) || compare(str, len, "KEYPAD_9", CASE_SENSETIVE)) Keyboard.press(KEYPAD_9);
        else if (compare(str, len, "NUM_ASTERIX", CASE_SENSETIVE)) Keyboard.press(KEYPAD_ASTERIX);
        else if (compare(str, len, "NUM_ENTER", CASE_SENSETIVE)) Keyboard.press(KEYPAD_ENTER);
        else if (compare(str, len, "NUM_MINUS", CASE_SENSETIVE)) Keyboard.press(KEYPAD_MINUS);
        else if (compare(str, len, "NUM_DOT", CASE_SENSETIVE)) Keyboard.press(KEYPAD_PERIOD);
        else if (compare(str, len, "NUM_PLUS", CASE_SENSETIVE)) Keyboard.press(KEYPAD_PLUS);


        // Media Control
        else if (compare(str, len, "MEDIA_PLAY", CASE_SENSETIVE)) Keyboard.press(KEY_MEDIA_PLAY);
        else if (compare(str, len, "MEDIA_PAUSE", CASE_SENSETIVE)) Keyboard.press(KEY_MEDIA_PAUSE);
        else if (compare(str, len, "MEDIA_RECORD", CASE_SENSETIVE)) Keyboard.press(KEY_MEDIA_RECORD);
        else if (compare(str, len, "MEDIA_FAST_FORWARD", CASE_SENSETIVE)) Keyboard.press(KEY_MEDIA_FAST_FORWARD);
        else if (compare(str, len, "MEDIA_REWIND", CASE_SENSETIVE)) Keyboard.press(KEY_MEDIA_REWIND);
        else if (compare(str, len, "MEDIA_NEXT_TRACK", CASE_SENSETIVE)) Keyboard.press(KEY_MEDIA_NEXT_TRACK);
        else if (compare(str, len, "MEDIA_PREV_TRACK", CASE_SENSETIVE)) Keyboard.press(KEY_MEDIA_PREV_TRACK);
        else if (compare(str, len, "MEDIA_STOP", CASE_SENSETIVE)) Keyboard.press(KEY_MEDIA_STOP);
        else if (compare(str, len, "MEDIA_MUTE", CASE_SENSETIVE)) Keyboard.press(KEY_MEDIA_MUTE);
        else if (compare(str, len, "MEDIA_VOLUME_INC", CASE_SENSETIVE) || compare(str, len, "VOLUME_UP", CASE_SENSETIVE)) Keyboard.press(KEY_MEDIA_VOLUME_INC);
        else if (compare(str, len, "MEDIA_VOLUME_DEC", CASE_SENSETIVE) || compare(str, len, "VOLUME_DOWN", CASE_SENSETIVE)) Keyboard.press(KEY_MEDIA_VOLUME_DEC);
        else if (compare(str, len, "PLAY_PAUSE", CASE_SENSETIVE)) Keyboard.press(KEY_MEDIA_PLAY_PAUSE);
        else if (compare(str, len, "PLAY_SKIP", CASE_SENSETIVE)) Keyboard.press(KEY_MEDIA_PLAY_SKIP);
        else if (compare(str, len, "EJECT", CASE_SENSETIVE)) Keyboard.press(KEY_MEDIA_EJECT);
        else if (compare(str, len, "RANDOM_PLAY", CASE_SENSETIVE)) Keyboard.press(KEY_MEDIA_RANDOM_PLAY);


        // Modifiers
        else if (compare(str, len, "CTRL", CASE_SENSETIVE) || compare(str, len, "CONTROL", CASE_SENSETIVE)) Keyboard.press(KEY_LEFT_CTRL);
        else if (compare(str, len, "SHIFT", CASE_SENSETIVE)) Keyboard.press(KEY_LEFT_SHIFT);
        else if (compare(str, len, "ALT", CASE_SENSETIVE)) Keyboard.press(KEY_LEFT_ALT);
        else if (compare(str, len, "WINDOWS", CASE_SENSETIVE) || compare(str, len, "GUI", CASE_SENSETIVE) || compare(str, len, "WIN", CASE_SENSETIVE) || compare(str, len, "CMD", CASE_SENSETIVE)) Keyboard.press(KEY_LEFT_GUI);

        // System Keys
        else if (compare(str, len, "POWER_DOWN", CASE_SENSETIVE) || compare(str, len, "POWER", CASE_SENSETIVE)) Keyboard.press(KEY_SYSTEM_POWER_DOWN);
        else if (compare(str, len, "SLEEP", CASE_SENSETIVE)) Keyboard.press(KEY_SYSTEM_SLEEP);
        else if (compare(str, len, "WAKE_UP", CASE_SENSETIVE)) Keyboard.press(KEY_SYSTEM_WAKE_UP);

            
        // Mouse Keys
        else if (compare(str, len, "LEFT_CLICK", CASE_SENSETIVE) || compare(str, len, "MOUSE_LEFT", CASE_SENSETIVE)) Mouse.press(MOUSE_LEFT);
        else if (compare(str, len, "RIGHT_CLICK", CASE_SENSETIVE) || compare(str, len, "MOUSE_RIGHT", CASE_SENSETIVE)) Mouse.press(MOUSE_RIGHT);
        else if (compare(str, len, "MIDDLE_CLICK", CASE_SENSETIVE) || compare(str, len, "MOUSE_MIDDLE", CASE_SENSETIVE)) Mouse.press(MOUSE_MIDDLE);
        else if (compare(str, len, "FORWARD_CLICK", CASE_SENSETIVE) || compare(str, len, "MOUSE_FORWARD", CASE_SENSETIVE)) Mouse.press(MOUSE_FORWARD);
        else if (compare(str, len, "BACK_CLICK", CASE_SENSETIVE) || compare(str, len, "MOUSE_BACK", CASE_SENSETIVE)) Mouse.press(MOUSE_BACK);
        else if (compare(str, len, "CLICK_ALL", CASE_SENSETIVE) || compare(str, len, "MOUSE_ALL", CASE_SENSETIVE)) Mouse.press(MOUSE_ALL);

        // Utf8 character (Do nothing. Not supported by me yet)
        else {
            // Keyboard.press(str);
        }
    }

    void release() {
        Keyboard.releaseAll();
        Mouse.release(MOUSE_ALL);
    }

    int toInt(const char* str, size_t len) {
        if (!str || (len == 0)) return 0;

        int val = 0;
        bool isNegative = false;

        // Check for negative sign
        size_t start = 0;
        if (str[0] == '-') {
            isNegative = true;
            start = 1;
        }

        // HEX
        if ((len > start + 2) && (str[start] == '0') && (str[start + 1] == 'x')) {
            for (size_t i = start + 2; i < len; ++i) {
                int b = str[i];

                if ((b >= '0') && (b <= '9')) b = b - '0';
                else if ((b >= 'a') && (b <= 'f')) b = b - 'a' + 10;
                else if ((b >= 'A') && (b <= 'F')) b = b - 'A' + 10;

                val = (val << 4) | (b & 0xF);
            }
        }
        // DECIMAL
        else {
            for (size_t i = start; i < len; ++i) {
                if ((str[i] >= '0') && (str[i] <= '9')) {
                    val = val * 10 + (str[i] - '0');
                }
            }
        }

        if (isNegative) val = -val;

        // HEX
        // if ((len > 2) && (str[0] == '0') && (str[1] == 'x')) {
        //     for (size_t i = 2; i < len; ++i) {
        //         int b = str[i];

        //         if ((b >= '0') && (b <= '9')) b = b - '0';
        //         else if ((b >= 'a') && (b <= 'f')) b = b - 'a' + 10;
        //         else if ((b >= 'A') && (b <= 'F')) b = b - 'A' + 10;

        //         val = (val << 4) | (b & 0xF);
        //     }
        // }
        // // DECIMAL
        // else {
        //     for (size_t i = 0; i < len; ++i) {
        //         if ((str[i] >= '0') && (str[i] <= '9')) {
        //             val = val * 10 + (str[i] - '0');
        //         }
        //     }
        // }

        return val;
    }

    // Convert n arguments into integers using toInt
    void parseNumArgs(word_node *w, int *arr, int numArgs) {
        for (int i = 0; i < numArgs; ++i) {
            if (w) {
                arr[i] = toInt(w->str, w->len);
                w = w->next;
            } else {
                arr[i] = 0;
            }
        }
    }

    void sleep(unsigned long time) {
        unsigned long offset = millis() - interpretTime;

        if (time > offset) {
            sleepStartTime = millis();
            sleepTime      = time - offset;

            delay(sleepTime);
        }
    }

    // ====== PUBLIC ===== //

    void parse(const char* str, size_t len) {
        interpretTime = millis();

        // Split str into a list of lines
        line_list* l = parse_lines(str, len);

        // Go through all lines
        line_node* n = l->first;

        // Flag, no default delay after this command
        bool ignore_delay;

        while (n) {
            ignore_delay = false;

            word_list* wl  = n->words;
            word_node* cmd = wl->first;

            const char* line_str = cmd->str + cmd->len + 1;
            size_t line_str_len  = n->len - cmd->len - 1;

            char last_char = n->str[n->len];
            bool line_end  = last_char == '\r' || last_char == '\n';

            // REM or # (= Comment -> do nothing)
            if (inComment || (compare(cmd->str, cmd->len, "REM", CASE_SENSETIVE) || compare(cmd->str, cmd->len, "#", CASE_SENSETIVE)))
            {
                inComment    = !line_end;
                ignore_delay = true;
            }

            // LOCALE (-> change keyboard layout)
            else if (compare(cmd->str, cmd->len, "LOCALE", CASE_SENSETIVE)) {
                // SKIP. This feature has been removed, but left here to not break scripts.
                ignore_delay = true;
            }

            // DELAY (-> sleep for x ms)
            else if (compare(cmd->str, cmd->len, "DELAY", CASE_SENSETIVE)) {
                sleep(toInt(line_str, line_str_len));
                ignore_delay = true;
            }

            // DEFAULTDELAY/DEFAULT_DELAY (-> set default delay per command)
            else if (compare(cmd->str, cmd->len, "DEFAULTDELAY", CASE_SENSETIVE) || compare(cmd->str, cmd->len, "DEFAULT_DELAY", CASE_SENSETIVE)) {
                defaultDelay = toInt(line_str, line_str_len);
                ignore_delay = true;
            }

            // REPEAT or REPLAY (-> repeat last command n times)
            else if (compare(cmd->str, cmd->len, "REPEAT", CASE_SENSETIVE) || compare(cmd->str, cmd->len, "REPLAY", CASE_SENSETIVE)) {
                repeatNum    = toInt(line_str, line_str_len) + 1;
                ignore_delay = true;
            }

            // STRING (-> type each character)
            else if (inString || compare(cmd->str, cmd->len, "STRING", CASE_SENSETIVE)) {
                if (inString) {
                    type(n->str, n->len);
                } else {
                    type(line_str, line_str_len);
                }

                inString = !line_end;
            }

            // STRINGLN (-> type each character and then type enter)
            else if (inString || compare(cmd->str, cmd->len, "STRINGLN", CASE_SENSETIVE)) {
                if (inString) {
                    type(n->str, n->len);
                    type("\n", sizeof("\n"));
                } else {
                    type(line_str, line_str_len);
                    type("\n", sizeof("\n"));
                }

                inString = !line_end;
            }

            // LED (-> toggle LED onboard Teensy ON or OFF)
            else if (compare(cmd->str, cmd->len, "LED", CASE_SENSETIVE)) {
                if (line_str_len)
                {
                    if (line_str = "ON") digitalWrite(LED_BUILTIN, HIGH);
                    else if (line_str = "OFF") digitalWrite(LED_BUILTIN, LOW);
                }
            }

            // SCREENSIZE/SCREEN_SIZE (-> set the screensize to x by y pixels so absolute mouse works. Third argument of 1 means macintosh)
            else if (compare(cmd->str, cmd->len, "SCREENSIZE", CASE_SENSETIVE) || compare(cmd->str, cmd->len, "SCREEN_SIZE", CASE_SENSETIVE)) {
                int c[3];
                bool isMacintosh = false;
                parseNumArgs(cmd->next, c, 3);
                // word_node *w = cmd->next;

                // for (int i = 0; i < 2; ++i) {
                //     if (w) {
                //         c[i] = toInt(w->str, w->len);
                //         w = w->next;
                //     }
                //     else {
                //         c[i] = 0;
                //     }
                // }

                if (c[2] == 1) isMacintosh=true;
                Mouse.screenSize(c[0], c[1], isMacintosh);
            }

            // MOVEMOUSE/MOVE_MOUSE/MOVE (-> move the mouse by x pixels horizontally and y pixels vertically)
            else if (compare(cmd->str, cmd->len, "MOVEMOUSE", CASE_SENSETIVE) || compare(cmd->str, cmd->len, "MOVE_MOUSE", CASE_SENSETIVE)
            || compare(cmd->str, cmd->len, "MOVE", CASE_SENSETIVE)) {
                int c[2];
                parseNumArgs(cmd->next, c, 2);
                Mouse.move(c[0], c[1]);
            }

            // MOVEMOUSETO/MOVE_MOUSE_TO/MOVETO/MOVE_TO (-> move the mouse to the absolute location of (x, y))
            else if (compare(cmd->str, cmd->len, "MOVEMOUSETO", CASE_SENSETIVE) || compare(cmd->str, cmd->len, "MOVE_MOUSE_TO", CASE_SENSETIVE)
            || compare(cmd->str, cmd->len, "MOVETO", CASE_SENSETIVE) || compare(cmd->str, cmd->len, "MOVE_TO", CASE_SENSETIVE)) {
                int c[2];
                parseNumArgs(cmd->next, c, 2);
                Mouse.moveTo(c[0], c[1]);
            }

            // SCROLL (-> scroll by n pixels up and m pixels horizontally)
            else if (compare(cmd->str, cmd->len, "SCROLL", CASE_SENSETIVE)) {
                int c[2];
                parseNumArgs(cmd->next, c, 2);
                Mouse.scroll(c[0], c[1]);
            }

            // PRESS or HOLD (-> press and hold hold button(s))
            else if (compare(cmd->str, cmd->len, "PRESS", CASE_SENSETIVE) || compare(cmd->str, cmd->len, "HOLD", CASE_SENSETIVE))
            {
                word_node* w = cmd->next;

                while (w) {
                    press(w->str, w->len);
                    w = w->next;
                }
            }

            // RELEASE or RELEASE_ALL (-> release all button(s))
            else if (compare(cmd->str, cmd->len, "RELEASE", CASE_SENSETIVE) || compare(cmd->str, cmd->len, "RELEASE_ALL", CASE_SENSETIVE))
            {
                release();
            }

            // KEYCODE
            else if (compare(cmd->str, cmd->len, "KEYCODE", CASE_SENSETIVE)) {
              word_node* w = cmd->next;
              if (w) {
                // Read modifiers
                int modifiers = (int)toInt(w->str, w->len);
                w = w->next;

                // Apply modifiers (if any)
                if (modifiers) {
                    Keyboard.press(modifiers);
                }

                // Read keycodes and press them
                for (int i = 0; i < 6; ++i) {
                    if (w) {
                      int keycode = (int)toInt(w->str, w->len);
                      Keyboard.press(keycode); // Press the key
                      w = w->next;
                    } else {
                      break; // Exit if there are no more keycodes
                    }
                }

                // Release all pressed keys
                for (int i = 0; i < 6; ++i) {
                    if (w) {
                        int keycode = (int)toInt(w->str, w->len);
                        Keyboard.release(keycode); // Release the key
                        w = w->next;
                    }
                }

                // Release modifiers if any
                if (modifiers) {
                    Keyboard.release(modifiers);
                }
              }
            }

            // Otherwise go through words and look for keys to press
            else {
                word_node* w = wl->first;

                while (w) {
                    press(w->str, w->len);
                    w = w->next;
                }

                if (line_end) release();
            }

            n = n->next;

            if (!inString && !inComment && !ignore_delay) sleep(defaultDelay);

            if (line_end && (repeatNum > 0)) --repeatNum;

            interpretTime = millis();
        }

        line_list_destroy(l);
    }

    int getRepeats() {
        return repeatNum;
    }

    unsigned int getDelayTime() {
        unsigned long finishTime  = sleepStartTime + sleepTime;
        unsigned long currentTime = millis();

        if (currentTime > finishTime) {
            return 0;
        } else {
            unsigned long remainingTime = finishTime - currentTime;
            return (unsigned int)remainingTime;
        }
    }
}
