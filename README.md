## Setup Instructions

DOWNLOAD ARDUINO IDE

BOARD MANAGER
> DOWNLOAD esp32 by Espressif Systems
> INSTALL PYTHON as dependency for esp32tool.py

LIBRARY MANAGER
> DOWNLOAD ESPAsyncWebServer by lacamera
> ArduinoJson by Benoit Blanchon
> OneWire by Jim Studt, etc
> DallasTemperature by Miles Burton

TOP LEFT
> BOARD: ESP32 Dev Module
> COM: kun unsay first makita

MODIFY LICEON.ino

ssid, password, static ip address



OPTIONAL CHANGES

change pin 0, 35, 34 to chosen pins, change other ip address settings



UPLOAD TO ESP32

=============================================================================

GO TO env.js

CHANGE 

IP_ESP32_LICEON = '192.168.192.168'; (192.168.192.168 to static ip)

SSID_ESP32_LICEON = 'SSID'; (SSID = name of the network)


====================================================

SETUP MARIADB/MYSQL

======================================================

SETUP SERVER AND WEBSITE

the terminal must be on the < LICEON/server/ > directory

START THE SERVER
node listen.js

START THE CLIENT
pnpm run dev -- --host

GET THE IP ADDRESS THAT STARTS WITH 192.*.*.*

THEN, REPLACE SA IP_KAGE_SERVER IN THE env.js



