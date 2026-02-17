#include <Arduino.h>
#include <util/delay.h>
#include "game_hw.h"
#include "game_draw.h"
#include "game_sound.h"
#include "game_simon.h"

// Безопасная задержка, которая продолжает крутить счетчик случайных чисел
void safe_delay_ms(uint16_t ms) {
    while(ms--) {
        _delay_ms(1);
        v_rnd++; 
    }
}

// Функция для подсветки сектора и воспроизведения звука
void simon_Flash(uint8_t dir) {
    g_Clear();
    
    // Рисуем стрелки или блоки в зависимости от направления
    if (dir == 0) { // ВВЕРХ
        g_SetPixel(3, 1); g_SetPixel(4, 1);
        g_SetPixel(3, 2); g_SetPixel(4, 2);
        g_SetPixel(3, 3); g_SetPixel(4, 3);
    } 
    if (dir == 1) { // ВЛЕВО
        g_SetPixel(1, 7); g_SetPixel(1, 8);
        g_SetPixel(2, 7); g_SetPixel(2, 8);
        g_SetPixel(3, 7); g_SetPixel(3, 8);
    } 
    if (dir == 2) { // ВНИЗ
        g_SetPixel(3, 12); g_SetPixel(4, 12);
        g_SetPixel(3, 13); g_SetPixel(4, 13);
        g_SetPixel(3, 14); g_SetPixel(4, 14);
    } 
    if (dir == 3) { // ВПРАВО
        g_SetPixel(6, 7); g_SetPixel(6, 8);
        g_SetPixel(5, 7); g_SetPixel(5, 8);
        g_SetPixel(4, 7); g_SetPixel(4, 8);
    }
    
    g_Update();
    sound_SimonTone(dir); // Играем звук (функция внутри сама делает задержку звучания)
    
    g_Clear();
    g_Update();
    safe_delay_ms(100); // Пауза после вспышки
}

void simon_Game(void) {
    uint8_t seq[50]; // Максимальная длина последовательности
    uint8_t count = 0;
    uint8_t fail = 0;
    uint8_t v_NotEnd = 1;

    // Сброс очков
    v_GamePoints = 0;
    UpdateGamePoints(); 
    
    // Отключаем неиспользуемые кнопки (оставляем только навигацию и выход)
    pkeys_Unused = 0b10110000; 

    safe_delay_ms(500);

    while (count < 50 && !fail && v_NotEnd) {
        // 1. Генерируем новый шаг
        RNDpADC(1); 
        seq[count] = v_rnd % 4; // Числа 0..3
        count++;

        safe_delay_ms(500);

        // 2. Показываем всю последовательность
        for (uint8_t i = 0; i < count; i++) {
            if (pKeySwitch(0x40) == 2) { v_NotEnd = 0; break; } // Проверка выхода
            simon_Flash(seq[i]);
            safe_delay_ms(200); 
        }
        if (!v_NotEnd) break;

        // 3. Ждем повторения от игрока
        for (uint8_t i = 0; i < count; i++) {
            uint8_t user_input = 255;
            
            // Ждем нажатия кнопки
            while (user_input == 255) {
                if (pReadKeys()) {
                    if (pKeySwitch(0x01) == 2) user_input = 0; // Up
                    if (pKeySwitch(0x02) == 2) user_input = 1; // Left
                    if (pKeySwitch(0x04) == 2) user_input = 2; // Down
                    if (pKeySwitch(0x08) == 2) user_input = 3; // Right
                    
                    if (pKeySwitch(0x40) == 2) { // Кнопка Exit
                        v_NotEnd = 0;
                        return; 
                    }
                }
                wdr(); // Сброс Watchdog таймера
                v_rnd++;
                _delay_ms(1);
            }
            
            // Показываем, что нажал игрок
            simon_Flash(user_input);

            // Проверяем правильность
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
            // Уровень пройден
            v_GamePoints++;
            UpdateGamePoints(); 
            safe_delay_ms(300);
            sound_Win(); // Звук победы в раунде
        }
    }
}