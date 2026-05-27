"use client";

import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card";
import { Sun, SunDim, Lightbulb } from "lucide-react";
import { cn } from "@/lib/utils";

interface LuminosityWidgetProps {
  luminosity: number;
}

function getLuminosityInfo(value: number) {
  if (value < 100)
    return {
      label: "Dim",
      description: "Low light conditions",
      icon: SunDim,
      color: "text-slate-400",
      bg: "bg-slate-500/10",
      glowOpacity: 0.1,
    };
  if (value < 300)
    return {
      label: "Moderate",
      description: "Normal indoor lighting",
      icon: Lightbulb,
      color: "text-yellow-500",
      bg: "bg-yellow-500/15",
      glowOpacity: 0.3,
    };
  if (value < 600)
    return {
      label: "Bright",
      description: "Well-lit environment",
      icon: Sun,
      color: "text-amber-400",
      bg: "bg-amber-400/15",
      glowOpacity: 0.5,
    };
  return {
    label: "Very Bright",
    description: "Maximum brightness",
    icon: Sun,
    color: "text-yellow-300",
    bg: "bg-yellow-300/20",
    glowOpacity: 0.8,
  };
}

export function LuminosityWidget({ luminosity }: LuminosityWidgetProps) {
  const info = getLuminosityInfo(luminosity);
  const Icon = info.icon;
  const normalizedValue = Math.min(luminosity / 1000, 1);

  return (
    <Card className="relative overflow-hidden">
      <div
        className="pointer-events-none absolute inset-0 transition-opacity duration-700"
        style={{
          background: `radial-gradient(circle at 70% 30%, rgba(250, 204, 21, ${info.glowOpacity * 0.4}), transparent 70%)`,
        }}
      />
      <CardHeader className="relative">
        <CardTitle className="text-sm font-medium text-muted-foreground">
          Luminosity
        </CardTitle>
      </CardHeader>
      <CardContent className="relative space-y-4">
        <div className="flex items-center gap-4">
          <div
            className={cn(
              "flex h-14 w-14 items-center justify-center rounded-xl transition-all duration-500",
              info.bg,
              info.color
            )}
          >
            <Icon className="h-7 w-7" />
          </div>
          <div className="flex flex-col gap-0.5">
            <div className="flex items-baseline gap-1">
              <span className="text-4xl font-bold tracking-tight">
                {luminosity}
              </span>
              <span className="text-lg text-muted-foreground">lux</span>
            </div>
            <span className={cn("text-xs font-medium", info.color)}>
              {info.label}
            </span>
          </div>
        </div>

        <div className="space-y-1.5">
          <div className="relative h-2 w-full overflow-hidden rounded-full bg-muted">
            <div
              className="h-full rounded-full transition-all duration-700 ease-out"
              style={{
                width: `${normalizedValue * 100}%`,
                background: `linear-gradient(90deg, #94a3b8, #eab308, #fbbf24)`,
              }}
            />
          </div>
          <p className="text-[10px] text-muted-foreground">
            {info.description}
          </p>
        </div>
      </CardContent>
    </Card>
  );
}
