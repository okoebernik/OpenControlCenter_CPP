\# OpenControlCenter Developer Log



\## Initial Foundation



The project was started as a clean C++17 ESP-IDF project for the Waveshare ESP32-P4-WIFI6-Touch-LCD-7B.



Important early decisions:



\- use C++17

\- use ESP-IDF directly

\- use LVGL for the UI

\- use the Waveshare BSP only for hardware integration

\- build a modular architecture instead of a single main.cpp



\## Architecture decisions so far



Introduced:



\- Application

\- ScreenManager

\- EventBus

\- ServiceManager

\- LayoutManager

\- Theme

\- Card

\- MetricRow

\- PrimaryValue

\- SystemModel

\- SystemService



\## Important bug: main task stack overflow



Symptom:



\- turquoise screen after multiple screen switches

\- later Guru Meditation

\- Stack protection fault in task main



Cause:



The Application object had grown too large to be safely created on the main task stack.



Old code:



```cpp

OCC::Application app;

app.run();

