\# ADR-0002: Widget Create Pattern



\## Status



Accepted



\## Context



Early widget classes created LVGL objects directly in their constructors.



Example:



```cpp

Card card(parent, "System");

This tightly coupled C++ object construction with LVGL object creation.



This caused problems when widgets needed to become long-lived member objects, because the LVGL parent is often only available later during screen creation.



Decision



Widgets should use a two-step lifecycle:



Card card;

card.create(parent, "System");



The C++ object can exist before the LVGL object is created.



Reasoning



This separates:



C++ object lifetime

LVGL object lifetime

UI initialization



It also makes widgets easier to use as member objects inside screens or composite widgets.



Consequences



Positive:



More predictable object lifetime

Easier composition

Better support for long-lived widgets

Consistent widget API



Negative:



Widgets can exist before being fully initialized

Methods should guard against null LVGL object pointers when needed

Rule



Every OCC widget should follow this pattern:



Widget widget;

widget.create(parent);



or:



Widget widget;

widget.create(parent, "Title");

Lesson Learned



Creating an object and creating its UI are not the same thing.

