#include <Arduino.h>
#include <EspMQTTClient.h>

#define WARM_LED_PIN    (0)
#define COLD_LED_PIN    (4)

#define FADE_TIME       (10)

uint8_t warm_cur_val;
uint8_t warm_target_val;
uint8_t cold_cur_val;
uint8_t cold_target_val;
uint32_t cur_ms;

void window_connected()
{
	mqtt.subscribe("light/window/cold", [] (const String &payload) {
		Serial.println(payload);
        cold_target_val = payload.toInt();
	});

    mqtt.subscribe("light/window/warm", [] (const String &payload) {
		Serial.println(payload);
        warm_target_val = payload.toInt();
	});
}

void window_setup()
{
    pinMode(WARM_LED_PIN, OUTPUT);
    pinMode(COLD_LED_PIN, OUTPUT);
    digitalWrite(WARM_LED_PIN, 0);
    digitalWrite(COLD_LED_PIN, 0);
}

void window_loop()
{
    if (millis() - cur_ms >= FADE_TIME){
        if (cold_cur_val <= cold_target_val) {
            cold_cur_val++;
            analogWrite(COLD_LED_PIN, gamma8[cold_cur_val]);
        }
        if (cold_cur_val >= cold_target_val) {
            cold_cur_val--;
            analogWrite(COLD_LED_PIN, gamma8[cold_cur_val]);
        }
        if (warm_cur_val <= warm_target_val) {
            warm_cur_val++;
            analogWrite(WARM_LED_PIN, gamma8[warm_cur_val]);
        }
        if (warm_cur_val >= warm_target_val) {
            warm_cur_val--;
            analogWrite(WARM_LED_PIN, gamma8[warm_cur_val]);
        }
        cur_ms = millis();
    }
}
