# Task Indicator - IoT Todo List (Arduino)

## Overview
At its core, the Task Indicator - IoT Todo List is a web-based task management application developed using Laravel. However, it goes beyond traditional to-do list applications by integrating with an ESP microcontroller, which is programmed to control a series of LEDs. Each LED corresponds to a task in the to-do list, providing a visual representation of the task's status.

Whenever a task is added, completed, or deleted, the corresponding LED on the ESP device reacts in real time, either lighting up, changing color, or turning off entirely. This project exemplifies how IoT can enhance user interaction by making abstract concepts, such as task completion, more tangible and immediate.

## PlatformIO Configuration

To ensure your project compiles correctly with PlatformIO, you need to update the `platformio.ini` file with the appropriate build flags. Additionally, you'll need to set the necessary environment variables on your system.

### Updating `platformio.ini`

Add the following lines to your `platformio.ini` file under the `[env]` section:

```ini
build_flags = 
    -D TOTAL_LEDS=19
    -D WIFI_SSID=\"${sysenv.IoT_WIFI_SID}\"
    -D WIFI_PASSWORD=\"${sysenv.IoT_WIFI_PASS}\"
    -D MQTT_BROKER=\"${sysenv.MQTT_BROKER}\"
    -D MQTT_USERNAME=\"${sysenv.MQTT_USERNAME}\"
    -D MQTT_PASSWORD=\"${sysenv.MQTT_PASSWORD}\"
    -D MQTT_PORT=\"${sysenv.MQTT_PORT}\"
```

### Important Notes

- **TOTAL_LEDS:** Replace `19` with the number of LEDs in your WS2812B LED strip.
- **Environment Variables:** Ensure the following environment variables are set on your system:
  - `IoT_WIFI_SID` - Your WiFi SSID.
  - `IoT_WIFI_PASS` - Your WiFi password.
  - `MQTT_BROKER` - The address of your MQTT broker.
  - `MQTT_USERNAME` - Your MQTT username (if applicable).
  - `MQTT_PASSWORD` - Your MQTT password (if applicable).
  - `MQTT_PORT` - The port your MQTT broker uses.

### Setting Environment Variables

Depending on your operating system, you can set environment variables as follows:

- **Windows:**
  - Open Command Prompt or PowerShell and run:
    ```sh
    setx IoT_WIFI_SID "your_wifi_ssid"
    setx IoT_WIFI_PASS "your_wifi_password"
    setx MQTT_BROKER "your_mqtt_broker_address"
    setx MQTT_USERNAME "your_mqtt_username"
    setx MQTT_PASSWORD "your_mqtt_password"
    setx MQTT_PORT "your_mqtt_port"
    ```

- **macOS/Linux:**
  - Add the following lines to your `~/.bashrc`, `~/.zshrc`, or the relevant shell configuration file:
    ```sh
    export IoT_WIFI_SID="your_wifi_ssid"
    export IoT_WIFI_PASS="your_wifi_password"
    export MQTT_BROKER="your_mqtt_broker_address"
    export MQTT_USERNAME="your_mqtt_username"
    export MQTT_PASSWORD="your_mqtt_password"
    export MQTT_PORT="your_mqtt_port"
    ```

  - After saving the file, run:
    ```sh
    source ~/.bashrc
    # or
    source ~/.zshrc
    ```

### Final Steps

Once you've updated the `platformio.ini` file and set the environment variables, you should be ready to compile and upload the code to your ESP device. Make sure to verify that all values are correct and correspond to your setup.
