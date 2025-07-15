# 🔐 Smart Home Automation with Voice Control

An innovative, IoT-powered home automation system designed to deliver convenience, security, and hands-free control using Google Assistant, Blynk IoT, RFID access, and sensor-based automation — all seamlessly integrated with traditional manual switches.

---

## 📌 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [System Architecture](#-system-architecture)
- [Hardware Used](#-hardware-used)
- [Software Used](#-software-used)
- [How It Works](#-how-it-works)
- [Installation](#-installation)
- [Future Scope](#-future-scope)
- [Team](#-team)
- [License](#-license)

---

## 🔍 Overview

This project provides a comprehensive smart home automation system that integrates:

- 🔊 Voice control via Google Assistant  
- 📱 Mobile app control via Blynk  
- 🧠 Smart features such as motion detection, gas leak alerts, and RFID door locks  
- 🧾 Manual override switches for reliability and inclusivity  

It modernizes and secures home environments while offering real-time control and monitoring.

---

## ✨ Features

- ✅ Control lights, fans, and appliances via app, voice, or physical switches  
- 🎤 Google Assistant integration using IFTTT and Sinric Pro  
- 📲 Blynk IoT app interface with real-time feedback  
- 🔐 RFID-enabled smart door lock system  
- 🚨 Smoke and gas leakage alerts with auto-cutoff  
- 🕵️‍♂️ Motion detection and intrusion alert system  
- 🌿 Automatic smart plant watering using soil moisture sensor  

---

## 🏗️ System Architecture

- NodeMCU ESP8266 as the central controller  
- Google Assistant + IFTTT for voice control  
- Blynk for mobile interface and notifications  
- Sensors (PIR, gas, soil moisture, RFID) for automation  
- Relays to control appliances  
- Manual switches as fallback controls  

---

## 🔩 Hardware Used

| Component               | Quantity | Description                     |
|------------------------|----------|---------------------------------|
| NodeMCU ESP8266        | 1        | Wi-Fi microcontroller           |
| 4-Channel Relay Module | 1        | Appliance switching             |
| RFID Reader (RC522)    | 1        | Secure entry                    |
| MQ-2 Gas Sensor        | 1        | Smoke/gas detection             |
| PIR Sensor             | 1        | Motion/intruder detection       |
| Soil Moisture Sensor   | 1        | Smart plant watering            |
| Solenoid Lock          | 1        | For door lock control           |
| Others                 | —        | Switches, pump, wires, buzzer   |

---

## 💻 Software Used

- Arduino IDE (v2.2.1)  
- Blynk IoT Console + Mobile App  
- Sinric Pro for Google Assistant Integration  
- Google Home App  
- IFTTT for Webhooks  

---

## ⚙️ How It Works

- 📱 Blynk app provides appliance control & live sensor data  
- 🗣️ Google Assistant triggers IFTTT → SinricPro → NodeMCU  
- 🕹️ Manual switches toggle relays for redundancy  
- 🔐 RFID reader authenticates and unlocks door  
- 🌫️ MQ-2 sensor triggers gas/smoke alert and buzzer  
- 🕵️ PIR sensor detects motion and alerts the user  
- 🌱 Soil sensor triggers watering pump if too dry  

---

## 🚀 Installation
