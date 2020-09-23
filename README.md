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


## OLD ROOM
![freeform_back](media/freeform_back.jpg "freeform_back")
![freeform_front](media/freeform_front.jpg "freeform_front")
![hotglue](media/hotglue.jpg "hotglue")

## The algorithm
The code is a machine state.

When someone comes in:
1. sensor 1 detects, sensor 2 doesn't
2. both sensors detect
3. no detection

**I could add one more state between 2 and 3 where sensor 2 detects and sensor 1 doesn't, but I modified the code to my needs.

when someone goes out:
1. sensor 2 detects, sensor 1 doesn't
2. both sensors detect
3. no detection

**Also passed a state between 2 and 3

Down below You will find the sate diagram:
![state_diagram](media/state_diagram.jpg "state_diagram")

And the result:
![door1](media/door1.jpg "door1")
![door2](media/door2.jpg "door2")


### Copyright (C) 2020 Yuval Kedar & Arad Eizen
## Stay Creative & Enjoy
