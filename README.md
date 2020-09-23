# Smart Room Based MQTT
 The program counts visitors in my room, controls the main light, and the window's light.

## Getting Started
#### Flash code using platformio
 This code runs on "window" and "door".  
 Please change platform definition in [platformio.ini](platformio.ini) before flashing.

 #### Install and run MQTT broker
 Remember to set the RPi with a static IP address

* Install [mosquitto](https://mosquitto.org/download/): ```sudo apt install mosquitto mosquitto-clients```
* Enable the Mosquitto Broker & allow auto-start after reboot: ```sudo systemctl enable mosquitto```
* Subscribe to the MQTT Topic Locally: ```mosquitto_sub -h localhost -t "test/message"```
* Publish to the MQTT Topic Locally: ```mosquitto_pub -h localhost -t "test/message" -m "Hello, world"```

### Copyright (C) 2020 Yuval Kedar & Arad Eizen
## Stay Creative & Enjoy
