/*
   Copyright (c) 2024 TEJ4321
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/TEJ4321/TeensyWiFiDuck
 */

#pragma once

/*! \typedef com_callback
 *  \brief Callback function to react on different responses
 */
typedef void (* com_callback)();

/*! \namespace com
 *  \brief Communication module
 */
namespace com {
    /*! Initializes the communication module */
    void begin();

    /*! Updates the communication module */
    void update();

    /*! Transmits string */
    unsigned int send(char str);
    unsigned int send(const char* str);
    unsigned int send(const char* str, unsigned int len);

    /*! Sets callback for status done */
    void onDone(com_callback c);

    /*! Sets callback for status error */
    void onError(com_callback c);

    /*! Sets callback for status repeat */
    void onRepeat(com_callback c);

    /*! Returns state of connection */
    bool connected();

    int getVersion();
}