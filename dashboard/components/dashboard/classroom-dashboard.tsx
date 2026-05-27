"use client";

import { useClassroomDataMock } from "@/hooks/use-classroom-data-mock";
import { DoorStatusWidget } from "./door-status-widget";
import { TemperatureWidget } from "./temperature-widget";
import { HumidityWidget } from "./humidity-widget";
import { LuminosityWidget } from "./luminosity-widget";
import { MapPin, Clock } from "lucide-react";
import { useEffect, useState } from "react";
import type { ClassroomConfig } from "@/lib/types";

interface ClassroomDashboardProps {
  config: ClassroomConfig;
}

export function ClassroomDashboard({ config }: ClassroomDashboardProps) {
  const data = useClassroomDataMock(config.id);
  const [currentTime, setCurrentTime] = useState("");

  useEffect(() => {
    const update = () => {
      setCurrentTime(
        new Date().toLocaleTimeString("en-GB", {
          hour: "2-digit",
          minute: "2-digit",
          second: "2-digit",
        })
      );
    };
    update();
    const interval = setInterval(update, 1000);
    return () => clearInterval(interval);
  }, []);

  return (
    <div>
      <div className="mb-6 flex flex-col gap-1 sm:flex-row sm:items-center sm:justify-between">
        <div>
          <h1 className="text-2xl font-bold tracking-tight">
            {config.name}
          </h1>
          <div className="mt-1 flex items-center gap-3 text-sm text-muted-foreground">
            <div className="flex items-center gap-1">
              <MapPin className="h-3.5 w-3.5" />
              {config.building}, Floor {config.floor}
            </div>
            <div className="flex items-center gap-1">
              <Clock className="h-3.5 w-3.5" />
              {currentTime}
            </div>
          </div>
        </div>
        <div className="mt-2 flex items-center gap-2 rounded-lg border bg-muted/50 px-3 py-1.5 text-xs text-muted-foreground sm:mt-0">
          <span className="relative flex h-1.5 w-1.5">
            <span className="absolute inline-flex h-full w-full animate-ping rounded-full bg-emerald-400 opacity-75" />
            <span className="relative inline-flex h-1.5 w-1.5 rounded-full bg-emerald-500" />
          </span>
          Live data - Updating every 2s
        </div>
      </div>

      <div className="grid grid-cols-1 gap-4 md:grid-cols-2 lg:grid-cols-4">
        <TemperatureWidget
          temperature={data.sensors.temperature}
          feltTemperature={data.sensors.feltTemperature}
          history={data.temperatureHistory}
        />
        <DoorStatusWidget isOpen={data.sensors.doorOpen} />
        <HumidityWidget humidity={data.sensors.humidity} />
        <LuminosityWidget luminosity={data.sensors.luminosity} />
      </div>
    </div>
  );
}
