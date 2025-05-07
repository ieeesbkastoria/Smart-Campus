# Smart-Campus


# ESP-Snippets: Smart Campus Temperature Monitoring System

Welcome to the ESP-Snippets project! This project is part of the IEEE Student Branch initiative aimed at developing a smart campus system. The goal of this project is to create a system using ESP32 microcontrollers and advanced sensors to improve the comfort, energy efficiency, and automation of lecture rooms.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Usage](#usage)


## Introduction

The Smart Campus Temperature Monitoring System is designed to improve the comfort, energy efficiency, and automation of lecture rooms. The system uses ESP32 microcontrollers along with advanced sensors like the BME680, Waveshare mmWave HMMD, and Fermion BH1750 to monitor environmental conditions and automate lighting. By continuously tracking temperature, humidity, air quality, motion, and ambient light levels, the system ensures an optimal learning environment while minimizing energy consumption.

## Features

- Real-time monitoring of temperature, humidity, air quality, and barometric pressure using the BME680 sensor
- Motion detection and presence sensing with the Waveshare mmWave HMMD Sensor
- Ambient light measurement with the Fermion BH1750 Ambient Light Sensor
- Automated lighting control based on motion and ambient light levels
- Wireless data transmission using ESP32 microcontrollers
- Centralized data collection and reporting
- Easy installation and setup

## Hardware Requirements

To set up the Smart Campus Temperature Monitoring System, you will need the following hardware components:

- ESP32 microcontrollers (one for each lecture room)
- BME680 sensors (for temperature, humidity, air quality, gas sensing, and barometric pressure measurements)
- Waveshare mmWave HMMD Sensor (for motion detection and presence sensing)
- Fermion BH1750 Ambient Light Sensor (for ambient light measurement)
- Door sensors
- Red Node (central node for data collection)
- Wi-Fi network for communication

## Usage

Once the system is set up, the ESP32 microcontrollers will start monitoring the temperature, motion, and ambient light levels of the lecture rooms and send the data to the central node. The central node will collect and report the data, enabling automated control of lights and other environmental factors to optimize comfort and energy efficiency.