#pragma once

namespace OCC
{

class PreferencesHardware
{
public:
    static void begin();

    static void readString(const char *key, const char *defaultValue, char *buffer, int bufferSize);
    static void writeString(const char *key, const char *value);

    static int readInt(const char *key, int defaultValue);
    static void writeInt(const char *key, int value);
};

}