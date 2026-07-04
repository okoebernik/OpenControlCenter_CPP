\# ADR-0001: Application Lifetime



\## Status



Accepted



\## Context



The `Application` class grew over time and started to contain multiple long-lived components:



\- ScreenManager

\- EventBus

\- ServiceManager

\- SystemModel

\- SystemService

\- DashboardScreen

\- SettingsScreen



Originally, the application object was created as a local variable in `app\_main()`:



```cpp

OCC::Application app;

app.run();



After adding more members, the ESP32-P4 reported:



Guru Meditation Error

Stack protection fault

Detected in task "main"

Decision



The Application object is created as a static object:



static OCC::Application app;

app.run();



Additionally, the ESP main task stack size was increased:



CONFIG\_ESP\_MAIN\_TASK\_STACK\_SIZE=16384

Reasoning



Large object graphs should not be allocated on the small task stack of an embedded system.



Using a static application object gives the application a stable lifetime for the entire runtime.



This also matches the architecture of OCC, where Application acts as the central orchestrator.



Consequences



Positive:



Avoids main task stack overflow

Gives all application components stable lifetime

Makes object ownership clearer



Negative:



The application object exists for the entire program lifetime

Static lifetime must be used carefully and intentionally

Lesson Learned



Object lifetime is as important as object functionality in embedded C++.





\## 3. Commit



```cmd

git add docs\\adr\\ADR-0001-application-lifetime.md

git commit -m "Add ADR for application lifetime"

