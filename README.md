## Setup Instructions

DOWNLOAD ARDUINO IDE


BOARD MANAGER
> DOWNLOAD esp32 by Espressif Systems

LIBRARY MANAGER
> DOWNLOAD ESPAsyncWebServer by lacamera
> ArduinoJson by Benoit Blanchon
> OneWire by Jim Studt, etc
> DallasTemperature by Miles Burton

TOP LEFT
> BOARD: ESP32 Dev Module
> COM: kun unsay first makita


THEN CHANGE SSID AND PASSWORD,

CLICK RST ON ESP32 TO SHOW THE IP WHEN IT STARTS WITHOUT RECONNECTING THE USB.



=============================================================================





GO TO env.js

CHNAGE THE 
IP_ESP32_LICEON = '192.168.4.1'; (ip addr ni esp32 from the same wifi nga gi connect niya)
SSID_ESP32_LICEON = 'LICEON_ESP32'; (ssid sa wifi na gi connect ni esp32)



====================================================

the terminal must be on the < LICEON/server/ > directory

START THE SERVER
node listen.js


START THE CLIENT
pnpm run dev -- --host


GET THE IP ADDRESS THAT STARTS WITH 192.*.*.*

THEN, REPLACE SA IP_KAGE_SERVER IN THE env.js



