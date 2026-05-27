"use client";

import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card";
import { Thermometer } from "lucide-react";
import type { TemperaturePoint } from "@/lib/types";
import {
  ResponsiveContainer,
  LineChart,
  Line,
  XAxis,
  YAxis,
  Tooltip,
  CartesianGrid,
} from "recharts";

interface TemperatureWidgetProps {
  temperature: number;
  feltTemperature: number;
  history: TemperaturePoint[];
}

export function TemperatureWidget({
  temperature,
  feltTemperature,
  history,
}: TemperatureWidgetProps) {
  return (
    <Card className="col-span-1 md:col-span-2">
      <CardHeader>
        <CardTitle className="text-sm font-medium text-muted-foreground">
          Temperature
        </CardTitle>
      </CardHeader>
      <CardContent className="space-y-4">
        <div className="flex items-start gap-4">
          <div className="flex h-14 w-14 items-center justify-center rounded-xl bg-rose-500/15 text-rose-500">
            <Thermometer className="h-7 w-7" />
          </div>
          <div className="flex flex-col gap-0.5">
            <div className="flex items-baseline gap-1">
              <span className="text-4xl font-bold tracking-tight">
                {temperature.toFixed(1)}
              </span>
              <span className="text-lg text-muted-foreground">C</span>
            </div>
            <span className="text-xs text-muted-foreground">
              Feels like{" "}
              <span className="font-semibold text-foreground">
                {feltTemperature.toFixed(1)}C
              </span>
            </span>
          </div>
        </div>

        <div className="h-48 w-full">
          <ResponsiveContainer width="100%" height="100%">
            <LineChart data={history}>
              <CartesianGrid
                strokeDasharray="3 3"
                className="stroke-border"
              />
              <XAxis
                dataKey="time"
                tick={{ fontSize: 10 }}
                className="fill-muted-foreground"
                interval="preserveStartEnd"
                tickCount={5}
              />
              <YAxis
                domain={["dataMin - 1", "dataMax + 1"]}
                tick={{ fontSize: 10 }}
                className="fill-muted-foreground"
                width={35}
              />
              <Tooltip
                contentStyle={{
                  backgroundColor: "hsl(var(--card))",
                  border: "1px solid hsl(var(--border))",
                  borderRadius: "8px",
                  fontSize: "12px",
                }}
              />
              <Line
                type="monotone"
                dataKey="temperature"
                stroke="#f43f5e"
                strokeWidth={2}
                dot={false}
                name="Actual"
                animationDuration={300}
              />
              <Line
                type="monotone"
                dataKey="feltTemperature"
                stroke="#fb923c"
                strokeWidth={2}
                strokeDasharray="4 4"
                dot={false}
                name="Felt"
                animationDuration={300}
              />
            </LineChart>
          </ResponsiveContainer>
        </div>

        <div className="flex items-center justify-center gap-6 text-xs text-muted-foreground">
          <div className="flex items-center gap-1.5">
            <span className="inline-block h-2.5 w-2.5 rounded-full bg-rose-500" />
            Actual
          </div>
          <div className="flex items-center gap-1.5">
            <span className="inline-block h-2.5 w-2.5 rounded-full bg-orange-400" />
            Felt
          </div>
        </div>
      </CardContent>
    </Card>
  );
}
