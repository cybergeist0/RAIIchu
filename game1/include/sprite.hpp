#pragma once

#include <cstdint>

class Sprite {
public:
    Sprite(const uint8_t* bitmap, int width, int height, uint16_t transparentColor = 0x0000);
    
    void setPosition(int x, int y);
    void move(int dx, int dy);
    void draw(class ILI9341_TFT& display);
    void drawScaled(class ILI9341_TFT& display, float scale);
    
    int getX() const { return x_pos; }
    int getY() const { return y_pos; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    
    bool collidesWith(const Sprite& other) const;
    
private:
    const uint8_t* bitmap_data;
    int width;
    int height;
    int x_pos;
    int y_pos;
    uint16_t transparent_color;
};