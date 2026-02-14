# Raijin
Open-source and customizable game development platform built around a Raspberry Pi Pico.
*This project is very much still in development.*

## Features
* Uses an ILI9341 Driver to control a 320x240 TFT Display
* Touch input via XPT2046
* Custom `Collider`, `Vector2D`, and `Sprite` classes for ease of use.
* Encapsulating and `Screen` class that allows for touch input and display output 
* Main `Game` class for state and game methods
* Basic (blocking) SFX through an `AudioChannel` but could possibly be offloaded to a second thread
* Editors in `/editors` for custom sprites and PWM tunes

## TODO
1. Finish the first game
2. Actually use the SD Card reader to save sprites or audio files?
3. Multiplayer support using SX162 LoRa???