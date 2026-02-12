#include "sprite.hpp"
#include "displaylib_16/ili9341.hpp"

Sprite::Sprite(const uint8_t* bitmap, int w, int h, uint16_t transparentColor)
    : bitmap_data(bitmap), width(w), height(h), x_pos(0), y_pos(0), transparent_color(transparentColor) {}

void Sprite::setPosition(int x, int y) {
    x_pos = x;
    y_pos = y;
}

void Sprite::move(int dx, int dy) {
    x_pos += dx;
    y_pos += dy;
}

void Sprite::draw(ILI9341_TFT& display) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = (y * width + x) * 2;
            uint16_t color = (bitmap_data[index] << 8) | bitmap_data[index + 1];
            
            if (color != transparent_color) {
                display.drawPixel(x_pos + x, y_pos + y, color);
            }
        }
    }
}

void Sprite::drawScaled(ILI9341_TFT& display, float scale) {
    int new_width = (int)(width * scale);
    int new_height = (int)(height * scale);
    
    for (int y = 0; y < new_height; y++) {
        for (int x = 0; x < new_width; x++) {
            int src_x = (int)(x / scale);
            int src_y = (int)(y / scale);
            int index = (src_y * width + src_x) * 2;
            uint16_t color = (bitmap_data[index] << 8) | bitmap_data[index + 1];
            
            if (color != transparent_color) {
                display.drawPixel(x_pos + x, y_pos + y, color);
            }
        }
    }
}

bool Sprite::collidesWith(const Sprite& other) const {
    return x_pos < other.x_pos + other.width &&
           x_pos + width > other.x_pos &&
           y_pos < other.y_pos + other.height &&
           y_pos + height > other.y_pos;
}