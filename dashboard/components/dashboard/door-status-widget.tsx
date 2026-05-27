"use client";

import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card";
import { DoorOpen, DoorClosed } from "lucide-react";
import { cn } from "@/lib/utils";

interface DoorStatusWidgetProps {
  isOpen: boolean;
}

export function DoorStatusWidget({ isOpen }: DoorStatusWidgetProps) {
  return (
    <Card className="relative overflow-hidden">
      <CardHeader>
        <CardTitle className="text-sm font-medium text-muted-foreground">
          Door Status
        </CardTitle>
      </CardHeader>
      <CardContent className="flex items-center gap-4">
        <div
          className={cn(
            "flex h-14 w-14 items-center justify-center rounded-xl transition-colors duration-500",
            isOpen
              ? "bg-amber-500/15 text-amber-500"
              : "bg-emerald-500/15 text-emerald-500"
          )}
        >
          {isOpen ? (
            <DoorOpen className="h-7 w-7" />
          ) : (
            <DoorClosed className="h-7 w-7" />
          )}
        </div>
        <div className="flex flex-col">
          <span
            className={cn(
              "text-2xl font-bold tracking-tight transition-colors duration-500",
              isOpen ? "text-amber-500" : "text-emerald-500"
            )}
          >
            {isOpen ? "Open" : "Closed"}
          </span>
          <span className="text-xs text-muted-foreground">
            {isOpen ? "Door is currently open" : "Door is secured"}
          </span>
        </div>
      </CardContent>
      <div
        className={cn(
          "absolute inset-x-0 bottom-0 h-1 transition-colors duration-500",
          isOpen ? "bg-amber-500" : "bg-emerald-500"
        )}
      />
    </Card>
  );
}
