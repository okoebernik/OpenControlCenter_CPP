\# Changelog



\## 0.1.0 - The Foundation



Initial foundation release.



\### Added



\- Modular C++17 architecture

\- Application lifecycle

\- ScreenManager

\- EventBus

\- ServiceManager

\- LayoutManager

\- DashboardScreen

\- SettingsScreen

\- NavigationBar

\- StatusBar

\- Theme system

\- Card widget

\- MetricRow widget

\- PrimaryValue widget

\- SystemModel

\- SystemService

\- Documentation structure

\- Vision document

\- Roadmap

\- Architecture documentation

\- Developer log

\- ADR-0001 Application Lifetime

\- ADR-0002 Widget Create Pattern



\### Fixed



\- ESP32-P4 Rev 1.x boot configuration

\- 32 MB flash configuration

\- PSRAM configuration

\- Main task stack overflow by using static Application object

## v0.2.0-alpha1 – Alive

### Added

- ClockModel
- ClockService
- DashboardViewModel
- Persistent Screen Architecture
- Persistent Widget Architecture
- MVVM data flow
- StatusBar integration

### Changed

- Screen lifecycle redesigned
- Widget ownership redesigned
- ScreenManager updated

### Fixed

- LVGL object lifetime issues
- Screen switching crashes
- Guru Meditation caused by deleted LVGL objects