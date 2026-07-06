#include "PreferencesHardware.h"

#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"

#include <cstring>

namespace OCC
{

static const char *TAG = "PreferencesHardware";
static const char *NAMESPACE = "occ";
static bool s_initialized = false;

void PreferencesHardware::begin()
{
    if (s_initialized)
    {
        return;
    }

    esp_err_t err = nvs_flash_init();

    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }

    ESP_ERROR_CHECK(err);

    s_initialized = true;
    ESP_LOGI(TAG, "Preferences initialized");
}

void PreferencesHardware::readString(const char *key, const char *defaultValue, char *buffer, int bufferSize)
{
    if (!buffer || bufferSize <= 0)
    {
        return;
    }

    std::strncpy(buffer, defaultValue ? defaultValue : "", bufferSize);
    buffer[bufferSize - 1] = '\0';

    begin();

    nvs_handle_t handle;
    if (nvs_open(NAMESPACE, NVS_READONLY, &handle) != ESP_OK)
    {
        return;
    }

    size_t requiredSize = bufferSize;
    nvs_get_str(handle, key, buffer, &requiredSize);

    buffer[bufferSize - 1] = '\0';

    nvs_close(handle);
}

void PreferencesHardware::writeString(const char *key, const char *value)
{
    begin();

    nvs_handle_t handle;
    if (nvs_open(NAMESPACE, NVS_READWRITE, &handle) != ESP_OK)
    {
        return;
    }

    nvs_set_str(handle, key, value ? value : "");
    nvs_commit(handle);
    nvs_close(handle);
}

int PreferencesHardware::readInt(const char *key, int defaultValue)
{
    begin();

    nvs_handle_t handle;
    if (nvs_open(NAMESPACE, NVS_READONLY, &handle) != ESP_OK)
    {
        return defaultValue;
    }

    int32_t value = defaultValue;
    nvs_get_i32(handle, key, &value);

    nvs_close(handle);
    return value;
}

void PreferencesHardware::writeInt(const char *key, int value)
{
    begin();

    nvs_handle_t handle;
    if (nvs_open(NAMESPACE, NVS_READWRITE, &handle) != ESP_OK)
    {
        return;
    }

    nvs_set_i32(handle, key, value);
    nvs_commit(handle);
    nvs_close(handle);
}

}