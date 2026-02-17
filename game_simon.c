#include <Arduino.h>
#include "game_hw.h"
#include "game_draw.h"
#include "game_sound.h"
#include "game_simon.h"

void simon_Flash(uint8_t dir) {
    g_Clear();
    // Рисуем жирную точку в зависимости от направления
    if (dir == 0) { for(int i=3;i<5;i++) for(int j=0;j<3;j++) g_SetPixel(i,j); } // Вверх
    if (dir == 1) { for(int i=0;i<3;i++) for(int j=7;j<9;j++) g_SetPixel(i,j); } // Влево
    if (dir == 2) { for(int i=3;i<5;i++) for(int j=13;j<16;j++) g_SetPixel(i,j); } // Вниз
    if (dir == 3) { for(int i=5;i<8;i++) for(int j=7;j<9;j++) g_SetPixel(i,j); } // Вправо
    g_Update();
    sound_SimonTone(dir);
    delay(300);
    g_Clear();
    g_Update();
}

void simon_Game() {
    uint8_t seq[20]; // Последовательность до 20 шагов
    uint8_t count = 0;
    uint8_t fail = 0;

    v_GamePoints = 0;
    UpdateGamePoints();

    while (count < 20 && !fail) {
        // Добавляем случайный шаг (0-3)
        seq[count] = v_rnd % 4;
        count++;

        // Показываем игроку всю текущую цепочку
        delay(800);
        for (uint8_t i = 0; i < count; i++) {
            simon_Flash(seq[i]);
            delay(200);
        }

        // Ждем ввода от игрока
        for (uint8_t i = 0; i < count; i++) {
            uint8_t user_input = 255;
            while (user_input == 255) {
                if (pReadKeys()) {
                    if (pKeySwitch(0x01) == 2) user_input = 0; // Up
                    if (pKeySwitch(0x02) == 2) user_input = 1; // Left
                    if (pKeySwitch(0x04) == 2) user_input = 2; // Down
                    if (pKeySwitch(0x08) == 2) user_input = 3; // Right
                    if (pKeySwitch(0x40) == 2) return; // Выход
                }
                wdr();
            }
            
            simon_Flash(user_input); // Подсветим что нажал игрок

            if (user_input != seq[i]) {
                sound_GameOver();
                fail = 1;
                break;
            }
        }

        if (!fail) {
            v_GamePoints++;
            UpdateGamePoints();
            delay(500);
            sound_Win();
        }
    }
    delay(1000);
    RandomGameOver();
}