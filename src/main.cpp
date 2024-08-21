#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <FastLED.h>

#define DATA_PIN 14
#define NUM_LEDS 19
#define BRIGHTNESS 30
#define NUM_COLORS 8

// WiFi credentials
#define ssid WIFI_SSID
#define password WIFI_PASSWORD

// MQTT Broker
const char *mqtt_server = MQTT_BROKER;
const char *mqtt_user = MQTT_USERNAME;
const char *mqtt_password = MQTT_PASSWORD;
const int mqtt_port = atoi(MQTT_PORT);

CRGB leds[NUM_LEDS];

CRGB colors[NUM_COLORS] = {
    CRGB::Red,
    CRGB::Green,
    CRGB::Blue,
    CRGB::Yellow,
    CRGB::Purple,
    CRGB::Grey,
    CRGB::Orange,
    CRGB::DeepPink,
};

WiFiClient espClient;
PubSubClient client(espClient);

void connectToWiFi();
void connectToMQTT();
void callback(char *topic, byte *payload, unsigned int length);
// To add task
void addTask(int index);
// To mark task as done
void markAsDone(int index);
// To remove task
void removeTask(int index);

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    ;
  }
  
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  // Connect to WiFi
  connectToWiFi();

  // Setup MQTT client
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  // Connect to MQTT broker
  connectToMQTT();

  // set an initial color
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Purple; // or any color you prefer
    delay(50);
    FastLED.show();
  }
  delay(1000);
  FastLED.clear(true);
}

void loop()
{
  // Ensure MQTT connection remains active
  if (!client.connected())
  {
    connectToMQTT();
  }
  client.loop();
}

// Connect to WiFi
void connectToWiFi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected, IP: ");
  Serial.println(WiFi.localIP());
}

// Connect to MQTT broker
void connectToMQTT()
{
  while (!client.connected())
  {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password))
    {
      Serial.println("connected");
      // Subscribe to topics
      client.subscribe("task-update/add");
      client.subscribe("task-update/delete");
      client.subscribe("task-update/done");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

// Callback function to handle incoming MQTT messages
void callback(char *topic, byte *payload, unsigned int length)
{
  String message;
  for (int i = 0; i < length; i++)
  {
    message += (char)payload[i];
  }
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  Serial.println(message);

  int ledIndex = message.toInt();
  // when task is added to the list
  if (String(topic) == "task-update/add")
  {
    if (ledIndex <= 19)
    {
      addTask(ledIndex);
    }
  }

  // when task is marked done ̰
  if (String(topic) == "task-update/done")
  {
    if (ledIndex <= 19)
    {
      markAsDone(ledIndex);
    }
  }

  // when task is deleted from the list
  if (String(topic) == "task-update/delete")
  {
    if (ledIndex <= 19)
    {
      removeTask(ledIndex);
    }
  }
}

void addTask(int index)
{
  leds[index] = CRGB::Orange;
  Serial.print("Add: ");
  Serial.println(index);
  FastLED.show();
}

void markAsDone(int index)
{
  leds[index] = CRGB::Green;
  Serial.print("Done: ");
  Serial.println(index);
  FastLED.show();
}

void removeTask(int index)
{
  leds[index] = CRGB::Black;
  Serial.print("Remove: ");
  Serial.println(index);
  FastLED.show();
}
