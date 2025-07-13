# 💧 Irrigation System

The Irrigation System is an automated solution designed to manage and optimize the watering of plants or crops.
It ensures efficient water usage by delivering the right amount of water at the right time, reducing waste and
promoting healthy plant growth.

This irrigation system supports 4 to 16 independent outlets, depending on the model - suffix determines
number of outlets e.g O4 - has 4 independent outlet, O16 - 16 outlets.
Each outlet can be individually configured with:
- Irrigation frequency (e.g., every 4 days)
- Start time (e.g., 12:00),
- Watering volume.

A built-in water flow sensor monitors water activity. If no water is detected during a scheduled irrigation,
the system alerts the user with an audible beep warning.
The system includes an internal real-time clock powered by a backup battery, ensuring scheduled operations
continue without disruption even if the main power supply is lost.

## Source Code

The system is based on ESP32 and Arduino Framework. Refer to [tutorial] to setup the environment.
Besides, the source code relies on the following libraries from Adafruit:
- [RTClib] - for interaction with RTC clock.
- [Adafruit_SSD1306] and [Adafruit-GFX-Library]- working with I2C display.

[tutorial]:https://randomnerdtutorials.com/getting-started-with-esp32/
[RTClib]:https://github.com/adafruit/RTClib
[Adafruit_SSD1306]:https://github.com/adafruit/Adafruit_SSD1306
[Adafruit-GFX-Library]:https://github.com/adafruit/Adafruit-GFX-Library