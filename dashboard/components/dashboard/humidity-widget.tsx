"use client";

import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card";
import { Droplets } from "lucide-react";
import { cn } from "@/lib/utils";

interface HumidityWidgetProps {
  humidity: number;
}

function getHumidityStatus(value: number): {
  label: string;
  color: string;
  barColor: string;
} {
  if (value < 30) return { label: "Low", color: "text-amber-500", barColor: "bg-amber-500" };
  if (value > 60) return { label: "High", color: "text-blue-500", barColor: "bg-blue-500" };
  return { label: "Optimal", color: "text-emerald-500", barColor: "bg-emerald-500" };
}

export function HumidityWidget({ humidity }: HumidityWidgetProps) {
  const status = getHumidityStatus(humidity);

  return (
    <Card>
      <CardHeader>
        <CardTitle className="text-sm font-medium text-muted-foreground">
          Humidity
        </CardTitle>
      </CardHeader>
      <CardContent className="space-y-4">
        <div className="flex items-center gap-4">
          <div className="flex h-14 w-14 items-center justify-center rounded-xl bg-sky-500/15 text-sky-500">
            <Droplets className="h-7 w-7" />
          </div>
          <div className="flex flex-col gap-0.5">
            <div className="flex items-baseline gap-1">
              <span className="text-4xl font-bold tracking-tight">
                {humidity}
              </span>
              <span className="text-lg text-muted-foreground">%</span>
            </div>
            <span className={cn("text-xs font-medium", status.color)}>
              {status.label}
            </span>
          </div>
        </div>

        <div className="space-y-2">
          <div className="flex items-center justify-between text-xs text-muted-foreground">
            <span>0%</span>
            <span>100%</span>
          </div>
          <div className="relative h-3 w-full overflow-hidden rounded-full bg-muted">
            <div
              className={cn(
                "h-full rounded-full transition-all duration-700 ease-out",
                status.barColor
              )}
              style={{ width: `${humidity}%` }}
            />
            <div className="absolute inset-0 flex">
              <div className="w-[30%] border-r border-background/40" />
              <div className="w-[30%] border-r border-background/40" />
            </div>
          </div>
          <div className="flex items-center justify-between text-[10px] text-muted-foreground">
            <span>Dry</span>
            <span>Comfortable</span>
            <span>Humid</span>
          </div>
        </div>
      </CardContent>
    </Card>
  );
}
