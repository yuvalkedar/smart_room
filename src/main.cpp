
/*
 * Smart Room V2.0 Software based on MQTT
 *
 * The program counts visitors in my room, controls the main light, and the window's light.
 * Please change platform definition in platformio.ini before flashing.
 *
 * Copyright (C) 2020 Yuval Kedar & Arad Eizen
 * Board: ESP8266 - Wemos D1 Mini
 * Date: Sep 2020
*/

#include <Arduino.h>
#include <ArduinoOTA.h>
#include <EspMQTTClient.h>
#include "macros.h"
#include "gamma_correction.h"

#ifdef DEVICE_DOOR
	#define DEVICE_LITERAL			door
#elif defined(DEVICE_WINDOW)
	#define DEVICE_LITERAL			window
#endif

#define DEVICE_NAME					STR(DEVICE_LITERAL)
#define DEVICE_FUNC(cmd)			JOIN(DEVICE_LITERAL, cmd)

bool ota_started = false;
EspMQTTClient mqtt(WIFI_SSID, WIFI_PASS, MQTT_ADDRESS, MQTT_USER, MQTT_PASS, DEVICE_NAME);

#ifdef DEVICE_DOOR
	#include "door.h"
#elif defined(DEVICE_WINDOW)
	#include "window.h"
#endif

void onConnectionEstablished()
{
	char msg[32];

	sprintf(msg, "%s connected to broker!", DEVICE_NAME);
	mqtt.publish("network", msg);

	// ArduinoOTA.setPort(OTA_PORT);
	// ArduinoOTA.setMdnsEnabled(false);
	// ArduinoOTA.onStart([]() { ota_started = true; });
	// ArduinoOTA.begin();

	DEVICE_FUNC(_connected)();
}

void setup()
{
	Serial.begin(115200);
	Serial.println(F("setup started!"));

	mqtt.enableMQTTPersistence();
	mqtt.enableDebuggingMessages();

	DEVICE_FUNC(_setup)();
	Serial.println(F("setup done!"));
}

void loop()
{
	mqtt.loop();

	do
		ArduinoOTA.handle();
	while (ota_started);

	DEVICE_FUNC(_loop)();
}