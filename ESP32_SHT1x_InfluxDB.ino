#include <WiFi.h>
#include <SHT1x.h>; // https://github.com/practicalarduino/SHT1x

#include "src/ESPinfluxdb.h" // https://github.com/hwwong/ESP_influxdb

//=======================================================================
//                    Config
//=======================================================================
// WiFi – Config
const char* ssid = "SSID";
const char* passwd = "password";

// SHT1x – Config
#define dataPin  33
#define clockPin 32
SHT1x sht1x(dataPin, clockPin);

// InfluxDB – Config
#define INFLUXDB_HOST "INFLUXDB_ADRESS"
#define INFLUXDB_PORT 8086

#define DATABASE  "mydb"
#define DB_USER "mydb_username"
#define DB_PASSWORD "mydb_password"

Influxdb influxdb(INFLUXDB_HOST, INFLUXDB_PORT);

// Sleep time – send data every 60 seconds
const int sleepTime = 60;

// Your device name!
#define DEVICE_NAME "ESP32_SHT1x"

//=======================================================================
//                    Power on setup
//=======================================================================
void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin(ssid, passwd);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // wait 5 seconds for connection:
    Serial.print("Status = ");
    Serial.println(WiFi.status());
    Serial.println(" ");
    delay(500);
  }
  if (influxdb.opendb(DATABASE) != DB_SUCCESS) {
    Serial.println("Connecting to database failed");
  }
}

//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
  float temp_c;
  float temp_f;
  float humidity;

  // Read values from the sensor
  temp_c = sht1x.readTemperatureC(); // Celsius
  temp_f = sht1x.readTemperatureF(); // Fahrenheit
  humidity = sht1x.readHumidity();


  // Print the values to the serial port
  Serial.print("Temperature: ");
  Serial.print(temp_c);
  Serial.print(" C\n");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  dbMeasurement row(DEVICE_NAME);
  row.addField("temperature", (temp_c));
  row.addField("humidity", (humidity));
  if (influxdb.write(row) == DB_SUCCESS) {
    Serial.println("Data send to InfluxDB\n\n");
  }
  row.empty();

  delay(sleepTime * 1000);
}
