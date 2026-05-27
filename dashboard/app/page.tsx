"use client";

import { useState } from "react";
import { Header } from "@/components/dashboard/header";
import { ClassroomDashboard } from "@/components/dashboard/classroom-dashboard";
import { Tabs, TabsList, TabsTrigger, TabsContent } from "@/components/ui/tabs";
import type { ClassroomConfig } from "@/lib/types";

const CLASSROOMS: ClassroomConfig[] = [
  { id: "B1", name: "B1", building: "Building B", floor: 2 },
  { id: "B11", name: "B11", building: "Building B", floor: 2 },
  { id: "A3", name: "Lab A3", building: "Building B", floor: 1 },
  { id: "MA", name: "Bigg Lecture Hall", building: "Building A", floor: 1 },
];

export default function Home() {
  const [activeTab, setActiveTab] = useState(CLASSROOMS[0].id);

  return (
    <div className="flex min-h-screen flex-col bg-background">
      <Header />
      <main className="mx-auto w-full max-w-7xl flex-1 px-4 py-6 sm:px-6">
        <Tabs
          value={activeTab}
          onValueChange={(val) => setActiveTab(val as string)}
        >
          <TabsList className="mb-6 w-full sm:w-auto">
            {CLASSROOMS.map((room) => (
              <TabsTrigger key={room.id} value={room.id}>
                {room.name}
              </TabsTrigger>
            ))}
          </TabsList>

          {CLASSROOMS.map((room) => (
            <TabsContent key={room.id} value={room.id}>
              <ClassroomDashboard config={room} />
            </TabsContent>
          ))}
        </Tabs>
      </main>
    </div>
  );
}
