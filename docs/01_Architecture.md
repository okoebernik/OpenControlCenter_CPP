# OpenControlCenter Architecture

## Overview

OpenControlCenter is built as a modular embedded HMI platform.

The architecture is designed around clear separation of responsibilities:

- Application lifecycle
- Core infrastructure
- Services
- Models
- ViewModels
- Screens
- Widgets

The goal is to keep the system understandable, testable and expandable.

---

## High Level Architecture

```text
Application
│
├── Core
│   ├── ScreenManager
│   ├── EventBus
│   ├── ServiceManager
│   └── LayoutManager
│
├── Services
│   ├── SystemService
│   ├── WifiService
│   ├── MQTTService
│   └── OTAService
│
├── Models
│   ├── SystemModel
│   ├── AquariumModel
│   ├── VictronModel
│   └── WeatherModel
│
├── ViewModels
│   ├── DashboardViewModel
│   ├── SettingsViewModel
│   └── ModuleViewModels
│
├── Screens
│   ├── DashboardScreen
│   ├── SettingsScreen
│   └── ModuleScreens
│
└── Widgets
    ├── Card
    ├── SystemCard
    ├── MetricRow
    └── PrimaryValue
	
	
Data Flow
Hardware / Network / System
        │
        ▼
Service
        │
        ▼
Model
        │
        ▼
ViewModel
        │
        ▼
Screen
        │
        ▼
Widget
        │
        ▼
LVGL

Data should flow in one direction.

Services collect data.

Models store data.

ViewModels transform data into display-ready values.

Screens arrange widgets.

Widgets render UI.

Core Components
Application

The Application class is the main orchestrator.

Responsibilities:

initialize hardware
initialize display and LVGL
register screens
register events
start services
run the main loop

The Application object is static to avoid stack overflow on the ESP32 main task.

ScreenManager

The ScreenManager controls which screen is currently visible.

It does not know business logic.

It only knows registered screens and can switch between them.

EventBus

The EventBus is infrastructure for loose communication.

It should be used for system-wide events such as:

navigation requests
heap changes
WiFi changes
MQTT status changes
future notifications
ServiceManager

The ServiceManager owns the service update cycle.

Each service receives deltaMs, the time elapsed since the last update.

This avoids each service having to implement its own timing logic.

Services

Services collect or generate data.

Examples:

SystemService
WifiService
MQTTService
ClockService

Rules:

Services do not know widgets.
Services do not know screens.
Services write to models.
Services may publish events.
Models

Models store raw application data.

Example:

SystemModel::setHeap(uint32_t heap);

Models should not contain LVGL code.

Models should not format display text.

ViewModels

ViewModels translate raw model data into UI-ready data.

Example:

SystemModel heap: 1234567 bytes
DashboardViewModel heapText: "1205 KB"

Rules:

ViewModels may read models.
ViewModels prepare text, status and display values.
ViewModels should not create LVGL objects.
Screens

Screens arrange widgets.

Examples:

DashboardScreen
SettingsScreen

Rules:

Screens should not collect data.
Screens should not directly call ESP-IDF system functions.
Screens should use ViewModels and Widgets.
Widgets

Widgets render reusable UI components.

Examples:

Card
MetricRow
PrimaryValue
SystemCard

Rules:

Widgets should not know services.
Widgets should not know models.
Widgets should provide clean setter methods such as:
setHeap(...)
setStatus(...)
setPrimaryValue(...)
Object Lifetime

Object lifetime is critical in embedded C++.

Avoid creating long-lived UI objects as local variables if they are referenced later.

Preferred pattern:

Card card;
card.create(parent, "Title");

This separates object lifetime from LVGL object creation.

Current Design Rules
Architecture before implementation.
Widgets use create().
Services use begin() and update(deltaMs).
Large application objects should not be placed on task stack.
No global application state unless unavoidable.
Prefer composition over inheritance.
Keep dependencies one-directional.
