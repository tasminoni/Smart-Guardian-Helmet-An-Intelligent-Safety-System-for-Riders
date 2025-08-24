Smart Guardian Helmet
Overview
The Smart Guardian Helmet is an intelligent safety system designed for two-wheeler riders to enhance road safety and promote responsible driving. It integrates helmet detection, alcohol sensing, drowsiness monitoring, temperature/weather alerts, theft prevention, auto light activation, and wireless data transmission using Arduino-based microcontroller interfacing and IoT communication.
Features

Helmet wear detection
Alcohol detection in rider's breath
Drowsiness monitoring via eye blink detection
Temperature and weather alerts
Theft prevention with buzzer alerts
Auto light activation in low-light conditions
Real-time message display
Engine relay control for safe ignition
Wireless data transmission using 433 MHz RF module

Hardware Components

Arduino UNO (x3)
IR Module (x2)
DHT22 Sensor (x1)
Breadboard (x2)
MQ-3 Alcohol Sensor (x1)
5V 1-Channel Relay (x1)
DC Motor (x1)
433 MHz RF Module (x1)
3.7V Battery (x4)
Buzzer (x2)
16x2 LCD with I2C Adapter (x1)
LEDs (x5)
Jumper Wires (mix pack)
3.7V Battery Holder (x2)
1K, 220V Resistor (x10)
LDR (x1)

Software Tools

Arduino IDE
Embedded C/C++
Proteus / Tinkercad
Arduino Libraries: Adafruit Unified Sensor, DHT Sensor, LiquidCrystal, LiquidCrystal_I2C, RadioHead, VirtualWire

Cost Breakdown

Total Cost: 4780 BDT

Installation

Connect all hardware components as per the circuit schematic.
Upload the provided Arduino code using Arduino IDE.
Ensure proper power supply with 3.7V batteries.
Test the system for sensor readings and wireless communication.

Usage

Wear the helmet to start the engine.
The system will alert and disable the engine if alcohol, drowsiness, or helmet removal is detected.
Receive real-time alerts via buzzer and LCD display.
Auto lights activate in low-light conditions.

Challenges & Solutions

Weak RF Signals: Solved with a proper antenna and RadioHead library.
False Drowsiness Detection: Added time check for accurate detection.
Sensor Calibration: Adjusted thresholds in hardware and software.
Battery Drain: Optimized data transmission intervals.
Fitting Components: Used compact layout and strategic sensor placement.

Sustainability & Impact

Energy-efficient with low-power components.
Recyclable materials for reused parts.
Reduces accidents, medical waste, and pollution.

Future Work

GPS and GSM integration for location tracking and SMS alerts.
Bluetooth/Wi-Fi upgrade for better communication.
Smaller design with custom PCBs.
Rechargeable battery with solar charging.

Contributors

MD. Kawsar Habib (21201327)
Tasmin Ahmed Oni (21201532)
Tushar Chowdhury (21301010)
Swapnil Saha (21301217)

References

Krisna, R. (2025). How to Build a Smart Helmet using Arduino? CircuitDigest.
Solution, T. (n.d.). Myproject.docx. Scribd.
