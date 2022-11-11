#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const PROGMEM char* mqttServer = "mqttserverip";
const PROGMEM uint16_t mqttPort = 1883;
const PROGMEM char* mqttUser = "mqttusername";
const PROGMEM char* mqttPassword = "mqttpassword";


char msg[50];

WiFiClient espClient;
PubSubClient client(espClient);


 
 int sensorPin = A0;  // select the input pin for the CO sensor  
 int sensorValue = 0; // variable to store the value coming from the sensor  
 // Initial setup  
 void setup() {  
  // initialize digital pin LED_BUILTIN as an output  
 
  // initialize the serial port  
  Serial.begin(9600);  
  WiFi.begin("wifissid", "wifipassword");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    long rssi = WiFi.RSSI();
    Serial.print("RSSI: ");
    Serial.println(rssi);

    client.setServer(mqttServer, mqttPort);

    while (!client.connected()) {
      Serial.println("Connecting to MQTT...");

      if (client.connect("ESP32Client", mqttUser, mqttPassword )) {

        Serial.println("Broker connected");

      } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
      }
   }
}  
 
 void loop() {  

  int sensorValue = analogRead(sensorPin);
  sensorValue;
  Serial.println(sensorValue);
  
  // MQTT publish
  snprintf (msg, sizeof(msg), "%ld", sensorValue);
      client.publish("toaster/co/",  msg);
      Serial.println(msg);        // debug
      
 }  