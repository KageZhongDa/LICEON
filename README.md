### Upload data to the flash memory of ESP32

The ESP32 COM PORT doesn't get automatically detected by Windows or the IDE. You must first install the [CP2102 driver](https://www.youtube.com/watch?v=h-jqF8Y5iV4) first and the **board package** in the Arduino IDE.

Make sure to change the flash mode from `QIO` to `DIO`, otherwise it will show a [corruption error.](https://github.com/HomeSpan/HomeSpan/discussions/490).

ESP32 does have SPIFFS (SPI Flash File System) support. SPIFFS is a file system designed for small embedded systems with limited resources, and it uses the flash memory of the ESP32 for file storage.

Upload the files to the SPIFFS file system using the ESP32 Sketch Data Upload tool in the Arduino IDE. The tool will take the files from a data folder in your sketch directory and upload them to the SPIFFS partition on the ESP32.

The folder that contains the files to be uploaded to SPIFFS should be named "data".

```
- /your_project_folder
  - /data
    - index.html
  - your_project.ino
```
