#include <Arduino.h>

// 板载 LED 在 UNO 上是 13 号引脚
const uint8_t LED_PIN = 13;

// 闪烁间隔（毫秒）
const uint16_t BLINK_INTERVAL = 500;

uint32_t lastToggleTime = 0;
bool ledState = false;

void setup() {
    pinMode(LED_PIN, OUTPUT);

    Serial.begin(9600);
    while (!Serial) {
        // 部分板子（如 Leonardo / ESP32）串口就绪需要时间
    }

    Serial.println(F("========================="));
    Serial.println(F("  embedded-starter 启动"));
    Serial.println(F("  输入任意字符可改变闪烁节奏"));
    Serial.println(F("========================="));
}

void loop() {
    // 非阻塞延时：不用 delay()，这样串口随时能响应
    if (millis() - lastToggleTime >= BLINK_INTERVAL) {
        lastToggleTime = millis();
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
        Serial.println(ledState ? F("LED ON") : F("LED OFF"));
    }

    // 串口回显：把收到的字符原样发回去
    if (Serial.available() > 0) {
        char received = Serial.read();
        Serial.print(F("收到: "));
        Serial.println(received);
    }
}
