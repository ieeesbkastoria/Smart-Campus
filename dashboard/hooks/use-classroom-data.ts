"use client";

import { useState, useEffect, useCallback, useRef } from "react";
import type { ClassroomData, TemperaturePoint } from "@/lib/types";

function clamp(value: number, min: number, max: number): number {
  return Math.min(Math.max(value, min), max);
}

function fluctuate(current: number, range: number, min: number, max: number): number {
  const delta = (Math.random() - 0.5) * range;
  return clamp(parseFloat((current + delta).toFixed(1)), min, max);
}

function formatTime(date: Date): string {
  return date.toLocaleTimeString("en-GB", {
    hour: "2-digit",
    minute: "2-digit",
    second: "2-digit",
  });
}

const HISTORY_LENGTH = 30;
const UPDATE_INTERVAL_MS = 2000;

function generateInitialHistory(): TemperaturePoint[] {
  const now = Date.now();
  const points: TemperaturePoint[] = [];
  let temp = 22.0;
  let felt = 23.0;

  for (let i = HISTORY_LENGTH - 1; i >= 0; i--) {
    const time = new Date(now - i * UPDATE_INTERVAL_MS * 10);
    temp = fluctuate(temp, 0.6, 18, 30);
    felt = fluctuate(felt, 0.5, 18, 32);
    points.push({
      time: formatTime(time),
      temperature: temp,
      feltTemperature: felt,
    });
  }

  return points;
}

export function useClassroomData(roomId: string = "A1"): ClassroomData {
  const [data, setData] = useState<ClassroomData>(() => ({
    roomId,
    roomName: `Classroom ${roomId}`,
    sensors: {
      doorOpen: false,
      temperature: 22.5,
      feltTemperature: 23.1,
      humidity: 45,
      luminosity: 300,
      timestamp: new Date(),
    },
    temperatureHistory: generateInitialHistory(),
  }));

  const dataRef = useRef(data);
  dataRef.current = data;

  const updateData = useCallback(() => {
    const prev = dataRef.current;
    const now = new Date();

    const newTemp = fluctuate(prev.sensors.temperature, 0.4, 18, 30);
    const newFelt = fluctuate(prev.sensors.feltTemperature, 0.3, 18, 32);
    const newHumidity = fluctuate(prev.sensors.humidity, 2, 20, 80);
    const newLux = Math.round(clamp(prev.sensors.luminosity + (Math.random() - 0.5) * 40, 0, 1000));
    const doorToggle = Math.random() < 0.05;

    const newPoint: TemperaturePoint = {
      time: formatTime(now),
      temperature: newTemp,
      feltTemperature: newFelt,
    };

    const newHistory = [...prev.temperatureHistory.slice(-HISTORY_LENGTH + 1), newPoint];

    setData({
      ...prev,
      sensors: {
        doorOpen: doorToggle ? !prev.sensors.doorOpen : prev.sensors.doorOpen,
        temperature: newTemp,
        feltTemperature: newFelt,
        humidity: Math.round(newHumidity),
        luminosity: newLux,
        timestamp: now,
      },
      temperatureHistory: newHistory,
    });
  }, []);

  useEffect(() => {
    const interval = setInterval(updateData, UPDATE_INTERVAL_MS);
    return () => clearInterval(interval);
  }, [updateData]);

  return data;
}
