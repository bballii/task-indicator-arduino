# Task Indicator - IoT Todo List (Arduino)

## Configuration

Before you start, make sure to configure the following values in the Arduino code to match your setup.

### Values to Change

-   **LED Configuration:**

    -   `#define DATA_PIN 14` - Pin number to which the LED strip is connected. Replace with your actual data pin.
    -   `#define NUM_LEDS 19` - Number of LEDs in your LED strip. Replace with the actual number of LEDs.
    -   `#define BRIGHTNESS 30` - Brightness level of the LEDs (range: 0-255). Adjust based on your preference.

-   **WiFi Credentials:**

    -   `const char *ssid = "ssid";` - Replace `"ssid"` with your WiFi network name.
    -   `const char *password = "pass";` - Replace `"pass"` with your WiFi network password.

-   **MQTT Server Credentials:**
    -   `const char *mqtt_server = "test.placeholder";` - Replace with the address of your MQTT broker.
    -   `const int mqtt_port = 1883;` - Replace with your MQTT broker's port if it differs from the default.
    -   `const char *mqtt_user = "user";` - Replace with your MQTT username, if any.
    -   `const char *mqtt_password = "pass";` - Replace with your MQTT password, if any.

Make sure to update these values in the code before uploading it to your ESP microcontroller.
