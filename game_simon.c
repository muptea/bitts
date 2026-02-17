#include <Arduino.h>
#include <util/delay.h>
#include "game_hw.h"
#include "game_draw.h"
#include "game_sound.h"
#include "game_simon.h"

void safe_delay_ms(uint16_t ms) {
    while(ms--) {
        _delay_ms(1);
        v_rnd++; 
    }
}

// Функция отрисовки стрелок
void simon_DrawArrow(uint8_t dir) {
    if (dir == 0) { 
        g_SetPixel(3, 0); g_SetPixel(4, 0);
        g_SetPixel(2, 1); g_SetPixel(5, 1);
        g_SetPixel(1, 2); g_SetPixel(6, 2);
        g_SetPixel(3, 1); g_SetPixel(4, 1);
        g_SetPixel(3, 2); g_SetPixel(4, 2);
        g_SetPixel(3, 3); g_SetPixel(4, 3);
        g_SetPixel(3, 4); g_SetPixel(4, 4);
    } 
    else if (dir == 1) { 
        g_SetPixel(0, 7); g_SetPixel(0, 8);
        g_SetPixel(1, 6); g_SetPixel(1, 9);
        g_SetPixel(2, 5); g_SetPixel(2, 10);
        g_SetPixel(1, 7); g_SetPixel(1, 8);
        g_SetPixel(2, 7); g_SetPixel(2, 8);
        g_SetPixel(3, 7); g_SetPixel(3, 8);
        g_SetPixel(4, 7); g_SetPixel(4, 8);
    } 
    else if (dir == 2) { 
        g_SetPixel(3, 11); g_SetPixel(4, 11);
        g_SetPixel(3, 12); g_SetPixel(4, 12);
        g_SetPixel(3, 13); g_SetPixel(4, 13);
        g_SetPixel(3, 14); g_SetPixel(4, 14);
        g_SetPixel(1, 13); g_SetPixel(6, 13);
        g_SetPixel(2, 14); g_SetPixel(5, 14);
        g_SetPixel(3, 15); g_SetPixel(4, 15);
    } 
    else if (dir == 3) { 
        g_SetPixel(3, 7); g_SetPixel(3, 8);
        g_SetPixel(4, 7); g_SetPixel(4, 8);
        g_SetPixel(5, 7); g_SetPixel(5, 8);
        g_SetPixel(6, 7); g_SetPixel(6, 8);
        g_SetPixel(5, 5); g_SetPixel(5, 10);
        g_SetPixel(6, 6); g_SetPixel(6, 9);
        g_SetPixel(7, 7); g_SetPixel(7, 8);
    }
}

void simon_Flash(uint8_t dir) {
    g_Clear();
    simon_DrawArrow(dir);
    g_Update();
    
    sound_SimonTone(dir);
    
    safe_delay_ms(250); 
    
    g_Clear();
    g_Update();
    safe_delay_ms(100);
}

void simon_Game(void) {
    uint8_t seq[50]; 
    uint8_t count = 0;
    uint8_t fail = 0;
    uint8_t v_NotEnd = 1;

    v_GamePoints = 0;
    UpdateGamePoints(); 
    
    pkeys_Unused = 0b10110000; 

    safe_delay_ms(500);

    while (count < 50 && !fail && v_NotEnd) {
        RNDpADC(1); 
        seq[count] = v_rnd % 4; 
        count++;

        safe_delay_ms(500);

        for (uint8_t i = 0; i < count; i++) {
            if (pKeySwitch(0x40) == 2) { v_NotEnd = 0; break; } 
            simon_Flash(seq[i]);
        }
        if (!v_NotEnd) break;

        for (uint8_t i = 0; i < count; i++) {
            uint8_t user_input = 255;
            
            while (user_input == 255) {
                if (pReadKeys()) {
                    if (pKeySwitch(0x01) == 2) user_input = 0; // Up
                    if (pKeySwitch(0x02) == 2) user_input = 1; // Left
                    if (pKeySwitch(0x04) == 2) user_input = 2; // Down
                    if (pKeySwitch(0x08) == 2) user_input = 3; // Right
                    
                    if (pKeySwitch(0x40) == 2) { 
                        v_NotEnd = 0;
                        return; 
                    }
                }
                wdr(); 
                v_rnd++;
                _delay_ms(1);
            }
            
            simon_Flash(user_input);

            if (user_input != seq[i]) {
                fail = 1;
                break;
            }
        }

        if (fail) {
            sound_GameOver();
            safe_delay_ms(1000);
            RandomGameOver();
        } else {
            v_GamePoints++;
            UpdateGamePoints(); 
            safe_delay_ms(200);
            sound_Win(); 
        }
    }
}