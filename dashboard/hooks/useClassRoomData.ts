"use client";
import { useState, useEffect, useRef } from "react";
import type { ClassroomData, TemperaturePoint } from "@/lib/types";

const HISTORY_LENGTH = 30;

function formatTime(date: Date): string {
  return date.toLocaleTimeString("en-GB", {
    hour: "2-digit",
    minute: "2-digit",
    second: "2-digit",
  });
}

export function useClassroomData(roomId: string = "A1") {
  const [data, setData] = useState<ClassroomData | null>(null);
  const wsRef = useRef<WebSocket | null>(null);

  useEffect(() => {
    const wsUrl = process.env.NODERED_WS_URL || process.env.NEXT_PUBLIC_NODERED_WS_URL || 'ws://localhost:1880/ws/smart-campus';
    const ws = new WebSocket("ws://localhost:1880/ws/classroom");

    ws.onopen = () => {
      console.log("Connect to Smart-Campus NodeRed");
    };

    ws.onmessage = (event) => {
      try {
        const message = JSON.parse(event.data);

        // TODO: Update to Node-RED payload structure
        if (message.roomId === roomId) {
          const sensors = message.sensors;
          const point: TemperaturePoint = {
            time: formatTime(new Date(sensors.timestamp || Date.now())),
            temperature: sensors.temperature,
            feltTemperature: sensors.feltTemperature,
          };

          setData(prev =>
            prev
              ? {
                ...prev,
                sensors: { ...sensors, timestamp: new Date(sensors.timestamp) },
                temperatureHistory: [
                  ...prev.temperatureHistory.slice(-HISTORY_LENGTH + 1),
                  point,
                ],
              }
              : {
                roomId,
                roomName: message.roomName || `Classroom ${roomId}`,
                sensors: { ...sensors, timestamp: new Date(sensors.timestamp) },
                temperatureHistory: [point],
              }
          );
        }
      } catch (err) {
        // Handle malformed messages etc.
        console.error("WS message error", err, event.data);
      }
    };

    ws.onerror = (e) => console.error("WebSocket error", e);
    ws.onclose = () => console.log("WS closed");

    wsRef.current = ws;
    return () => {
      ws.close();
    };
  }, [roomId]);

  return data;
}
