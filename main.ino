#define BLYNK_TEMPLATE_ID "Template_ID"
#define BLYNK_TEMPLATE_NAME "Template_Name"
#define BLYNK_AUTH_TOKEN "Your_Token"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// Blynk auth token from the app
char auth[] = "Your_Token";

// Wi-Fi credentials
char ssid[] = "WiFiName";
char pass[] = "WiFiPassword";

// Pin definition
int sensorPin = A0; // KY-039 connected to A0 (analog pin)
int sensorValue = 0; // Variable to store sensor value

// Timer for reading sensor data
BlynkTimer timer;

void sendSensorData()
{
  float pulse;             // Variable to store pulse value
  int sum = 0;             // Variable to accumulate sensor readings

  // Take 20 readings from the sensor
  for (int i = 0; i < 20; i++) {
    sum += analogRead(A0); // Read the analog value from pin A0
  }

  pulse = sum / 20.0;      // Calculate the average of the 20 readings
  //sensorValue = analogRead(sensorPin); // Read the analog value
  //Serial.print("Heartbeat sensor value: ");
  Serial.println(pulse);

  // Send value to Blynk (to virtual pin V1)
  Blynk.virtualWrite(A0, pulse);

  Serial.println(pulse);   // Print the average pulse value to the Serial Monitor
  delay(100);   
}

void setup() {
  pinMode(A0, INPUT);      // Set pin A0 as input for sensor readings
  Serial.begin(9600);      // Initialize serial communication at 9600 baud rate


  // Connect to Wi-Fi and Blynk
  Blynk.begin(auth, ssid, pass);

  // Set a timer to read sensor data every second
  timer.setInterval(1000L, sendSensorData);
}

void loop() {
  Blynk.run();    // Run the Blynk process
  timer.run();           // Wait for 100 milliseconds before taking the next set of readings
}