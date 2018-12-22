# ESP32 SHT1x InfluxDB
Sending measurements data from Sensirion Temperature and Humidity sensor SHT1x (SHT10, SHT11, SHT15) connected to ESP32 to your InfluxDB database.

Based on [SHT1x library](https://github.com/practicalarduino/SHT1x) and [ESP_influxdb library](https://github.com/hwwong/ESP_influxdb).

### Wiring
 SHT1x - ESP32:
 * VCC - 3.3V
 * GND - G
 * SCL - IO32
 * SDA(DATA) - IO32 – required pull-up resistor 10k to VCC
 
#### Tested on:

* ArduinoIDE 1.8.5
* ESP32-PICO-KIT-V4.1
* Sensirion SHT10
