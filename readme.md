# RAIIchu
Open-source and customizable game development platform built around a Raspberry Pi Pico.
*This project is very much still in development.*

**Currently, the `game1` project is a simple "collect the coins" game where the onboard LED turns on during a collision. I plan on adding more features as I develop this project and add more examples later.**

## Features
* Uses an ILI9341 Driver to control a 320x240 TFT Display
* Touch input via XPT2046
* Custom `Collider`, `Vector2D`, and `Sprite` classes for ease of use.
* Encapsulating `Screen` class that allows for touch input and display output 
## TODO
1. Implement a passive buzzer to play sfxs on collisions
2. Actually use the SD Card reader to save sprites or audio files?
3. Multiplayer support using LoRa???