# TeensyWiFiDuck
## Project Overview
My project, the TeensyWiFiDuck involves using the Arduino framework with ESP8266 and Teensy microcontrollers I already had lying around to construct my own makeshift Wireless BadUSB.
![image](https://github.com/user-attachments/assets/b4294280-fc6b-43f8-a11b-d22a1ab95ec2)

The TeensyWiFiDuck extends the functionality of normal BadUSBs to allow remote control and execution capability via WiFi, including the ability to view, edit and deploy scripts directly from the web browser dynamically without needing any compilation.
It uses a custom variation of the scripting language DuckyScript, used by the actual Rubber Ducky and other BadUSB products to maintain compatibility with scripts written for any of the other products.
My project’s modified DuckyScript allows for more native key inputs than was allowed by the original, such as additional keys like F13-F24, media keys, as well as system keys like power, sleep and wake and many more. My implementation of DuckyScript also includes mouse buttons, mouse movement and scroll functionality as well as persistent key hold commands.
All possible commands and keys are given in the landing page of the website after connecting to the TeensyWiFiDuck network.
Note that DuckyScript was originally a scripting language which provided an easy method of writing payloads for the USB Rubber Ducky. However, since its original release, DuckyScript has constantly been evolving, with the latest version being almost a full turing-complete programming language with variables, flow control, loops, functions, extensions and more. My version does not include these additional features in its current form, but can be expanded to include at least some of them in the future.

## Usage
1.	Plug in a data-capable cable to the TeensyWiFiDuck’s microUSB port.
2.	Connect to the WiFi network called wifiduck with password wifiduck (can customise this in the WebUI).
3.	Open the browser and visit the site http://wifi.duck/ (or http://192.168.4.1)
4.	Create, edit, deploy or delete scripts as well as manage the settings from here on.

## Hardware
The microcontroller hardware used in this project is two small development boards each serving different purposes in this project:
1. LOLIN Wemos D1 Mini V4.0.0
  - This board serves as the wireless access point
  - Hosts the web server and DNS server
  - Maintains the script storage and user interface
![image](https://github.com/user-attachments/assets/72a4c9e5-106f-4aa0-87f6-c8defa13b97f)
2. PJRC Teensy® 3.6
  - USB interface for debugging and HID attacks
  - DuckyScript parser and translator
  - Power source for both boards from onboard USB
![image](https://github.com/user-attachments/assets/c44d47a2-a115-4db3-9231-fb7e4e1322c9)
3. Headers for each of the microcontrollers
4. 4 PCB jumper wires
5. (Optional) 3D printed case


### Physical Connections
The Teensy needs to power the ESP8266 so that only one USB connection is needed to run the whole thing. Both the ESP8266 and the Teensy both run at 3.3V internally, but USB power is 5V. Unfortunately, the 3.3V pins of each board CANNOT simply be connected to each other, as the 3.3V pin of the Teensy only supports up to 100mA of power, with the ESP8266 sometimes known to exceed that value, potentially causing damage.
Therefore, to achieve goal of only one USB connection to run both boards, the following connections need to be made:
-	D1 Mini’s ground pin (GND) to Teensy’s ground pin (GND).
-	D1 Mini’s USB voltage pin (VBUS) to Teensy’s USB voltage pin (VUSB).

The two boards communicate with each other via serial. The Teensy 3.6 has 6 serial interfaces while the D1 Mini only has 1. Since all 6 of the serial interfaces are not needed on the Teensy, only the Serial1 interface (RX1 and TX1) is used to communicate to the D1 Mini.
Since the control voltage of both the ESP8266 and the Teensy is 3.3V, no logic level shifters are needed for the communication lines between the two boards.
Therefore, for a serial connection between the two boards, the following connections need to be made:
-	D1 Mini’s transmit pin (TX) to Teensy’s receive pin (RX) [Pin 0].
-	D1 Mini’s receive pin (RX) to Teensy’s transmit pin (TX) [Pin 1].

Based on the previously described requirements, a colour coded diagram and photo of the physical connections are given below:
![image](https://github.com/user-attachments/assets/14254d3f-59ef-48cf-a4f9-ec910fadc18f)

### (Optional) Case
The TeensyWiFiDuck also features a completely custom designed 2-part case that is easy to 3D print that maintains access to all buttons and ports both the Teensy and Wemos D1 Mini.
![image](https://github.com/user-attachments/assets/0e31a80f-3589-4750-98f5-4f1ea215864a)
![image](https://github.com/user-attachments/assets/18694dfa-dc4e-441a-b1f3-114dc4909fdd)

The CAD and 3D Model files are located in the CAD folder.

## Software Installation
The software run by both controllers is completely separate, yet designed to interface in a way that each one requires the other to function (as specified in the hardware section).
To flash the TeensyWiFiDuck software onto the microcontrollers, unfortunately the process is not super streamlined as of this current moment, but is still quite straightforward if instructions are followed.
### Requirements
- Arduino IDE
- Visual Studio Code with the PlatformIO add-on.
- USB-C cable
- USB Micro-B cable

### Flashing the Wemos D1 Mini
1. Plug in the USB-C cable into the Wemos D1 Mini’s port
2. Open Arduino IDE to the esp_duck sketch
3. Go to the File->Preferences menu, and in the Additional boards manager URLs section, add the following text to install packages for the ESP8266 boards: http://arduino.esp8266.com/stable/package_esp8266com_index.json,https://dl.espressif.com/dl/package_esp32_index.json
4. In the toolbar at the top left, select Tools->Board->esp8266->LOLIN(WEMOS) D1 R2 & Mini (or whatever other ESP8266 board you are using).
5. Go to Tools->USB Type and select one of the options including a Keyboard, Mouse and Serial.
6. Click the Upload button in the top left of the screen (It looks like a right arrow)

Please note that when flashing the Wemos D1 Mini, you may have to disconnect any wires connected to its RX port as its serial interface is shared between USB and the Teensy, so flashing may not work if it’s still connected to the Teensy.
Also, in order to modify the website files, please modify the files in the web folder and then run webconverter.py to update the ESP8266 header files to include them.

### Flashing the Teensy
1.	Plug in the USB Micro-B cable into the Teensy 3.6
2.	Open Visual Studio Code to the teensy folder as the workspace.
3.	(Optional) To make sure the TeensyWiFiDuck can bypass the Mac keyboard wizard, modify arduino.py located at: $USERPROFILE%\.platformio\platforms\teensy\builder\frameworks\arduino.py to include “MAC_USB_SERIAL_HID” in the BUILTIN_USB_FLAGS definition.
4.	Click the Upload button in the bottom left of the screen
5.	If/when prompted to, press the reset button on the Teensy. This is located at the bottom of the 3D printed case.

## Demonstrations
The use cases of this device are quite literally limitless, and are almost solely bounded by the imagination of the user. However, to demonstrate some of the functionality of the product, I have recorded a few videos showing the capabilities of it.
Playlist link: https://www.youtube.com/playlist?list=PLS1pwokbQ3npOu7_kbTR1ngxRYM52md-a

## Disclaimer
This tool was created for and is intended to be used for educational purposes only.  
Do NOT use it to do harm or inflict damage!

## License
This software is licensed under the MIT License.
See the [license file](LICENSE) for details.  

## Credits
The TeensyWiFiDuck directly utilises or is built off parts of the following projects:
-	[WiFiDuck](https://github.com/SpacehuhnTech/WiFiDuck)
- [Arduino](https://www.arduino.cc)
- [Neopixel Library](https://github.com/adafruit/Adafruit_NeoPixel)
- [Dotstar Library](https://github.com/adafruit/Adafruit_DotStar)
- [AVR, ESP8266 & SAMD Arduino Core](https://github.com/spacehuhn/hardware/tree/master/wifiduck)
- [ESPAsyncTCP](https://github.com/me-no-dev/ESPAsyncTCP)
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)
- [SimpleCLI](https://github.com/spacehuhn/SimpleCLI)

