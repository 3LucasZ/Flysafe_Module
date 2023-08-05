# How to build PlatformIO based project

1. [Install PlatformIO Core](https://docs.platformio.org/page/core.html)
2. Download [development platform with examples](https://github.com/platformio/platform-espressif32/archive/develop.zip)
3. Extract ZIP archive
4. Run these commands:

```shell
# Change directory to example
$ cd platform-espressif32/examples/espidf-arduino-blink

# Build project
$ pio run

# Upload firmware
$ pio run --target upload

# Build specific environment
$ pio run -e esp32dev

# Upload firmware for the specific environment
$ pio run -e esp32dev --target upload

# Clean build files
$ pio run --target clean
```

Notes:
Technical Manual:
https://cdn.sparkfun.com/assets/f/e/6/3/7/PM-14032.pdf?_gl=1*xwk7iu*_ga*ODczNjg1MjM3LjE2OTEyMDkwNjM.*_ga_T369JS7J9N*MTY5MTIwOTA2My4xLjAuMTY5MTIwOTA2My42MC4wLjA.

Operation modes:
https://github.com/garmin/LIDARLite_Arduino_Library/blob/master/src/LIDARLite.cpp
