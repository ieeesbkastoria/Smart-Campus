# Smart Campus

> A smart, sensor-driven system for efficient classroom management and environmental monitoring.

---

## Project Overview

**Smart Campus** is an **IoT-based sensor network** designed to help universities manage classroom environments efficiently.
By monitoring **temperature**, **humidity**, **luminosity**, **motion**, and **door status**, the system helps detect:

* Forgotten lights or open doors
* Uncomfortable temperature or humidity levels
* Classroom occupancy
* Forgotten open doors

All sensor data is visualized through an **OpenHub UI**, allowing administrators to monitor conditions in real time and optimize energy use.

---

## Objectives

* Enhance **energy efficiency** across campus classrooms
* Improve **comfort** and **safety** for students and staff
* Provide a **real-time monitoring** solution for facility management
* Build a scalable and open-source **IoT framework** for academic environments

---

## System Architecture

The Smart Campus system is built around a **sensor network** powered by ESP32 devices, each node collecting environmental data and transmitting it through **MQTT** to a central **Mosquitto broker**. The backend communicates with the **OpenHub UI** for visualization and analytics.

```
[ Sensors ] → [ ESP32 Node ] → [ MQTT Broker (Mosquitto) ] → [ OpenHub UI ]
```

---

##  Features

*️ **Temperature & Humidity** monitoring (DHT11)
* **Luminosity** detection (BH1750)
* **Motion** detection
* **Door status** detection
* **Wireless communication** via MQTT
* **Dockerized deployment** for easy setup
* **Auto-generated documentation** using Doxygen

---

## Tech Stack

| Component                  | Technology                                                        |
| -------------------------- | ----------------------------------------------------------------- |
| **Microcontroller**        | ESP32                                                             |
| **Programming Language**   | C++                                                               |
| **Framework**              | Arduino                                                           |
| **Sensors**                | BH1750 (Light), DHT11 (Temp/Humidity), Door Sensor, Motion Sensor |
| **Communication Protocol** | MQTT                                                              |
| **Broker**                 | Mosquitto                                                         |
| **Deployment**             | Docker                                                            |
| **Tooling**            | PlatformIO                                                        |
| **Documentation**          | Doxygen                                                           |

---

## 🚀 Setup & Installation

### 1. Clone the repository

```bash
git clone https://github.com/<your-org>/smart-campus.git
cd smart-campus
```

### 2. Configure PlatformIO

Open the project in VS Code with the **PlatformIO** extension installed.
Adjust `platformio.ini` as needed for your ESP32 board.

### 3. Flash the firmware

```bash
pio run --target upload
```

### 4. Run Mosquitto MQTT Broker via Docker

```bash
docker run -it -p 1883:1883 -p 9001:9001 eclipse-mosquitto
```

### 5. Connect to OpenHub UI

Once devices are connected and publishing data, visualize metrics on the OpenHub dashboard.

---

## Team Credits

This project was developed by the **IEEE Student Branch UoWM Kastoria's** Smart-Campus Team:

| Name         | Role                           |
| ------------ | ------------------------------ |
| [Dimitrios Papakonstantinou](https://www.linkedin.com/in/dimitrios-papakonstantinou-44a7672b3/)  | Project Lead /  Software Developer  |
| [George Tingos](https://www.linkedin.com/in/george-tingos-6288a0389?utm_source=share&utm_campaign=share_via&utm_content=profile&utm_medium=android_app) | Software Developer              |

> Special thanks to our IEEE Student Branch and University mentors for their support and guidance.

---

## License

This project is licensed under the **MIT License** – see the [LICENSE](./LICENSE) file for details.

---

## Acknowledgments

* IEEE Student Branch [UoWM Kastoria](https://ieee.cs.uowm.gr/)
* [University of Westen Machedonia](https://www.uowm.gr/)
* OpenHub Community
* PlatformIO and Arduino Open Source Contributors
* Espressif Systems for the ESP32 platform
