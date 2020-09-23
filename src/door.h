#include <Arduino.h>
#include <EspMQTTClient.h>
#include <FastLED.h>

#define RELAY_PIN	(4)		// Blue wire
#define DATA_PIN	(5)		// White wire

#define DEBOUNCE_MS	(100)
#define NUM_PIXELS	(30)

CRGB leds[NUM_PIXELS];

void parse_rgb_value(const String &payload)
{
	if (payload.length() != 7) {
        Serial.printf("invalid payload: '%s'\n", payload.c_str());
        return;
    }
	uint32_t rgb = strtol(payload.c_str() + 1, 0, 16); // parse as Hex, skipping the leading '#'
    uint8_t r = (rgb >> 16) & 0xFF;
    uint8_t g = (rgb >> 8) & 0xFF;
    uint8_t b = rgb & 0xFF;
	leds[0] = CRGB(gamma8[r],gamma8[g],gamma8[b]);
  	FastLED.show();
    // Serial.printf("r = %d, g = %d, b = %d\n",gamma8[r],gamma8[g],gamma8[b]);
}

void door_connected()
{
	mqtt.subscribe("light/main", [] (const String &payload) {
		Serial.println(payload);
        digitalWrite(RELAY_PIN, payload.toInt());
	});

	mqtt.subscribe("light/rgb", [] (const String &payload) {
		parse_rgb_value(payload);
	});
}

void door_setup()
{
    FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_PIXELS);
    pinMode(LED_BUILTIN, OUTPUT);	//Control LED
	pinMode(RELAY_PIN, OUTPUT);
	leds[0] = CRGB::Black;
  	FastLED.show();
}

void door_loop()
{

}
