void sleep(str time) {
    #ifdef ESP32
        esp_sleep_enable_timer_wakeup(time);
        esp_deep_sleep_start();
    #else
        ESP.deepSleep(time);
    #endif
}