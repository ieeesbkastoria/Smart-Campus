"use client";

import { Activity, GraduationCap } from "lucide-react";

export function Header() {
  return (
    <header className="sticky top-0 z-50 w-full border-b bg-background/80 backdrop-blur-lg">
      <div className="mx-auto flex h-16 max-w-7xl items-center justify-between px-4 sm:px-6">
        <div className="flex items-center gap-3">
          <div className="flex h-9 w-9 items-center justify-center rounded-lg bg-primary text-primary-foreground">
            <GraduationCap className="h-5 w-5" />
          </div>
          <div className="flex flex-col">
            <span className="text-base font-bold leading-tight tracking-tight">
              Smart-Campus
            </span>
            <span className="text-[10px] uppercase tracking-widest text-muted-foreground">
              Classroom Monitoring
            </span>
          </div>
        </div>

        <div className="flex items-center gap-2 rounded-full border bg-emerald-500/10 px-3 py-1.5">
          <Activity className="h-3.5 w-3.5 text-emerald-500" />
          <span className="text-xs font-medium text-emerald-500">
            System Online
          </span>
          <span className="relative flex h-2 w-2">
            <span className="absolute inline-flex h-full w-full animate-ping rounded-full bg-emerald-400 opacity-75" />
            <span className="relative inline-flex h-2 w-2 rounded-full bg-emerald-500" />
          </span>
        </div>
      </div>
    </header>
  );
}
