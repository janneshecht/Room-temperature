#include <MySQL_Cursor.h>
#include <MySQL_Connection.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"

// DHT22:   PIN 1:  VCC     connect to 3.3V
//          PIN 2:  Data    connect to D2
//          PIN 3:  NC      not used
//          PIN 4:  GND     connect to G

// Type of Sensor, in this case DHT22
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// Wifi-login
const char* ssid = "Your_SSID";
const char* password = "Your_wifi-pass";

// Widget-URL
const char* widgeturl = "http://smashing-dashboard-url:3030/widgets/roomtemperature";

// DHT Sensor
// Connected Pin of "Data" from DHT22
// uint8_t DHTPin = D2;
uint8_t DHTPin = 4;

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

// define variables
float Temperature;
float Humidity;

IPAddress server_addr(172,16,1,15);  // IP of the MySQL *server* here
char mysqluser[] = "db-user";              // MySQL user login username
char mysqlpassword[] = "db-pw";        // MySQL user login password

WiFiClient client;
MySQL_Connection conn((Client *)&client);

void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(DHTPin, INPUT);

  dht.begin();

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  //Serial.println(WiFi.status());
  Serial.println("Connecting...");
  }
  Serial.println("");
  Serial.println("WiFi connected..Yeeha!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
}

int counter = 0;

void loop() {
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity

  // Output on screen (for debug)
  Serial.print("Temperature: ");
  Serial.println(Temperature);
  Serial.print("Humidity: ");
  Serial.println(Humidity);

  // Declare an object of class HTTPClient
  HTTPClient http;

  // Dashboard-Update start
  http.begin(widgeturl);

  // HTTP request with a content type: application/json
  http.addHeader("Content-Type", "application/json");
  String Post = "{\"auth_token\":\"YOUR_AUTH_TOKEN\",\"temperature\":" + String(Temperature) + ",\"humidity\":" + String(Humidity) + "}";
  int httpResponseCode = http.POST(Post);

  // Check return-code
  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);

  // Free resources
  http.end();

counter += 1;

if (counter > 1) {
  delay(1000);

  // Database-connect
  Serial.print(server_addr);
  Serial.print(", ");
  Serial.print(3306);
  Serial.print(", ");
  Serial.print(mysqluser);
  Serial.print(", ");
  Serial.println(mysqlpassword);

  Serial.println("Connecting MySQL...");
  if (conn.connect(server_addr, 3306, mysqluser, mysqlpassword)) {
    delay(5000);
    Serial.println("Yeah! Mysql-Connection stable!");

    // Float to String
    String tempf = String(Temperature);
    String humif = String(Humidity);

    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    String INSERT_SQL = "INSERT INTO db.table(`temperature`, `humidity`, `room`) VALUES (" + tempf + "," + humif + ", 'Wohnzimmer')";
    int str_len = INSERT_SQL.length() + 1;
    char char_array[str_len];
    INSERT_SQL.toCharArray(char_array, str_len);
    // Execute the query
    cur_mem->execute(char_array);
    // Deleting the cursor also frees up memory used
    delete cur_mem;
  }
  else
  {  Serial.println("Connection to MySQL failed.");
    //  Serial.println(connected());
  }
  conn.close();
  counter = 0;
}
  delay(15000); // wait 15 seconds
}
