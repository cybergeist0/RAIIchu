#include <stdio.h>
#include <vector>
#include "pico/stdlib.h"
#include "screen.hpp"
#include "sprite.hpp"
#include "assets.hpp"

#define LED_PIN 25
#define MAX_COINS 5
#define COIN_SPAWN_INTERVAL_MS 800

struct FallingCoin {
    Sprite* sprite;
    float velocity;
    bool active;
};

int main() {
    stdio_init_all();
    sleep_ms(1000);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 0);

    Screen screen;
    ILI9341_TFT &display = screen.display();

    display.fillScreen(display.C_BLACK);
    
    Sprite player(PLAYER_SPRITE, PLAYER_WIDTH, PLAYER_HEIGHT, 0x0000);
    player.setPosition(120, 280);
    
    std::vector<FallingCoin> coins(MAX_COINS);
    for (int i = 0; i < MAX_COINS; i++) {
        coins[i].sprite = new Sprite(SILVER_COIN_SPRITE, SILVER_COIN_WIDTH, SILVER_COIN_HEIGHT, 0x0000);
        coins[i].active = false;
        coins[i].velocity = 0;
    }
    
    const int move_speed = 5;
    const float gravity = 0.3f;
    int old_player_x = player.getX();
    int old_player_y = player.getY();
    
    uint32_t last_spawn_time = 0;
    uint32_t frame_count = 0;
    
    while(true) {
        frame_count++;
        uint32_t current_time = to_ms_since_boot(get_absolute_time());
        
        if (current_time - last_spawn_time > COIN_SPAWN_INTERVAL_MS) {
            for (int i = 0; i < MAX_COINS; i++) {
                if (!coins[i].active) {
                    int random_x = (frame_count * 37) % (240 - SILVER_COIN_WIDTH); // Pseudo-random
                    coins[i].sprite->setPosition(random_x, 0);
                    coins[i].velocity = 1.0f;
                    coins[i].active = true;
                    last_spawn_time = current_time;
                    break;
                }
            }
        }
        
        // input handler
        uint16_t touch_x, touch_y;
        if (screen.readTouch(touch_x, touch_y)) {
            display.fillRect(old_player_x, old_player_y, PLAYER_WIDTH, PLAYER_HEIGHT, display.C_BLACK);
            
            int sprite_x = player.getX();
            int sprite_y = player.getY();
            
            if (touch_x < sprite_x) sprite_x -= move_speed;
            if (touch_x > sprite_x) sprite_x += move_speed;
            if (touch_y < sprite_y) sprite_y -= move_speed;
            if (touch_y > sprite_y) sprite_y += move_speed;
            
            player.setPosition(sprite_x, sprite_y);
            old_player_x = sprite_x;
            old_player_y = sprite_y;
        }
        
        // update/check collisions
        bool collision_detected = false;
        for (int i = 0; i < MAX_COINS; i++) {
            if (coins[i].active) {
                int old_coin_y = coins[i].sprite->getY();
                
                coins[i].velocity += gravity;
                int new_y = old_coin_y + (int)coins[i].velocity;
                
                // clear old position
                display.fillRect(coins[i].sprite->getX(), old_coin_y, 
                                SILVER_COIN_WIDTH, SILVER_COIN_HEIGHT, display.C_BLACK);
                
                // check if coin is off screen
                if (new_y > 320) {
                    coins[i].active = false;
                    continue;
                }
                
                coins[i].sprite->setPosition(coins[i].sprite->getX(), new_y);
                
                // check collision with player
                if (player.collidesWith(*coins[i].sprite)) {
                    collision_detected = true;
                    coins[i].active = false;
                    display.fillRect(coins[i].sprite->getX(), coins[i].sprite->getY(), 
                                    SILVER_COIN_WIDTH, SILVER_COIN_HEIGHT, display.C_BLACK);
                } else {
                    coins[i].sprite->draw(display);
                }
            }
        }
        
        gpio_put(LED_PIN, collision_detected ? 1 : 0);
        
        player.draw(display);
        
        sleep_ms(16);
    }
    
    for (int i = 0; i < MAX_COINS; i++) {
        delete coins[i].sprite;
    }
    
    return 0;
}