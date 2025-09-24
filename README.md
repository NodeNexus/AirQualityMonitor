# 🌫️ ESP32 Air Quality & Pollution Monitor

## 📌 Overview
This project monitors **air quality (AQI)**, **temperature**, and **humidity** using an ESP32, **MQ135 gas sensor**, and **DHT22**.  
It hosts a **local web dashboard** updating readings in real-time.

---

## 🛠️ Hardware Required
- ESP32 Dev Board  
- MQ135 Gas Sensor  
- DHT22 Temperature & Humidity Sensor  
- Jumper wires, breadboard  

---

## 🔌 Wiring
- MQ135 → ESP32  
  - VCC → 5V  
  - GND → GND  
  - OUT → GPIO34  

- DHT22 → ESP32  
  - VCC → 3.3V  
  - GND → GND  
  - Data → GPIO35  

---

## ▶️ Usage
1. Upload the sketch to ESP32.  
2. Connect to Wi-Fi AP `ESP32-AP` (password: `12345678`).  
3. Open browser → go to `192.168.4.1`.  
4. Dashboard shows AQI, temperature, and humidity updating every second.

---

## 📂 Repo Structure
