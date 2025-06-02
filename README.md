# ESP32-Ultrasonic-Sensor-Test
# HC-SR04 Ultrasonic Sensor Test with ESP32 (ESP-IDF v5.4.1)

This repository contains an ESP-IDF v5.4.1 project for testing the HC-SR04 ultrasonic sensor with an ESP32 microcontroller. The code measures distances using the sensor’s trigger and echo signals, handling out-of-range cases with a timeout mechanism. Developed and tested in Visual Studio Code with the ESP-IDF extension, it includes precise timing for reliable measurements and serial output for monitoring distances in real-time.

Features:

Measures distances from 2 cm to 400 cm using the HC-SR04 sensor.
Implements precise timing with esp_timer and ets_delay_us for accurate trigger pulses.
Handles out-of-range errors with a 30ms timeout, reporting invalid measurements.
Configurable GPIO pins (default: TRIG on GPIO 5, ECHO on GPIO 18).
Built for ESP32 using ESP-IDF v5.4.1, compatible with VS Code’s ESP-IDF extension.
Setup:

Install ESP-IDF v5.4.1 and the ESP-IDF VS Code extension.
Connect the HC-SR04 to your ESP32 (VCC, GND, TRIG, ECHO).
Clone this repository and open it in VS Code.
Configure the project using ESP-IDF: SDK Configuration Editor.
Build, flash, and monitor using VS Code’s ESP-IDF commands.
Usage:

Place a flat object 2–400 cm from the sensor.
Monitor distance readings via the serial console (ESP-IDF: Monitor Your Device).
Modify main.c to change GPIO pins or timing parameters as needed.
Requirements:

ESP32 development board (e.g., ESP32-WROOM-32).
HC-SR04 ultrasonic sensor.
ESP-IDF v5.4.1 and VS Code with the ESP-IDF extension.
USB-to-serial connection for flashing and monitoring.

Hardware Design:


Output:


Challenges:
1. "Cannot Open Source File" Error
Description:
This error occurs in VS Code when the ESP-IDF project cannot locate header files (e.g., freertos/FreeRTOS.h, driver/gpio.h, or ets_sys.h) during compilation or IntelliSense processing. It typically indicates issues with the include path configuration, missing ESP-IDF components, or an improperly set up VS Code environment.
Common error messages in the VS Code Problems panel or build output include:
#include errors detected. cannot open source file "freertos/FreeRTOS.h"
fatal error: driver/gpio.h: No such file or directory
Causes:
Incorrect IDF_PATH: The IDF_PATH environment variable or VS Code settings don’t point to the ESP-IDF v5.4.1 directory (e.g., C:\Espressif\esp\esp-idf).
Missing c_cpp_properties.json: The .vscode/c_cpp_properties.json file, which configures IntelliSense, lacks correct include paths for ESP-IDF components.
Incomplete ESP-IDF Installation: ESP-IDF v5.4.1 or its tools (e.g., CMake, Ninja) are not fully installed.
CMakeLists.txt Issues: The project’s CMakeLists.txt doesn’t specify required components (e.g., driver, esp_timer).
Extension Misconfiguration: The ESP-IDF VS Code extension isn’t properly configured to locate ESP-IDF.
Solutions:
Verify IDF_PATH: Ensure IDF_PATH is set to the ESP-IDF v5.4.1 directory. In VS Code, run ESP-IDF: Configure ESP-IDF Extension and select v5.4.1. Check the environment variable:
Windows: echo %IDF_PATH% in Command Prompt.
Linux/macOS: echo $IDF_PATH in terminal.
Set manually if needed (e.g., export IDF_PATH=/path/to/esp-idf on Linux/macOS).
Update c_cpp_properties.json: Run ESP-IDF: SDK Configuration Editor or ESP-IDF: Configure Paths to generate/update .vscode/c_cpp_properties.json.

2. HC-SR04 "Out of Range" Errors
Challenge: The HC-SR04 reports "Distance: Out of range" due to no echo signal, an excessively long echo pulse, or measurements outside the sensor’s 2–400 cm range.
Causes:
Wiring Issues: Loose connections, incorrect GPIO pins, or mismatched voltage levels (HC-SR04 often requires 5V, while ESP32 uses 3.3V logic).
Environmental Factors: Objects too close (<2 cm), too far (>400 cm), or non-reflective surfaces (e.g., soft fabrics) disrupting the echo.
Timing Errors: Inaccurate trigger pulse timing or echo detection due to FreeRTOS scheduling or coarse delays.
Solutions:
Verify Wiring: Ensure TRIG (e.g., GPIO 5) and ECHO (e.g., GPIO 18) are correctly connected. Use a 5V power source for the HC-SR04 if required, with a level shifter for the ECHO pin to convert 5V to 3.3V for ESP32 compatibility.
Test Environment: Place a flat, reflective object (e.g., a wall) 10–100 cm away. Avoid soft or angled surfaces.
Improve Timing: The provided code uses ets_delay_us for precise 10µs trigger pulses and a 30ms timeout. If errors persist, increase TIMEOUT_US to 40000 (40ms) to account for longer distances.
Code Check: Ensure the code from my previous response is used, as it includes timeout handling. Verify GPIO pins match your wiring.
