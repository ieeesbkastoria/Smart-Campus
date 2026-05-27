export interface SensorData {
  doorOpen: boolean;
  temperature: number;
  feltTemperature: number;
  humidity: number;
  luminosity: number;
  timestamp: Date;
}

export interface TemperaturePoint {
  time: string;
  temperature: number;
  feltTemperature: number;
}

export interface ClassroomData {
  roomId: string;
  roomName: string;
  sensors: SensorData;
  temperatureHistory: TemperaturePoint[];
}

export interface ClassroomConfig {
  id: string;
  name: string;
  building: string;
  floor: number;
}
