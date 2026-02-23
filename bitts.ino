#include <Arduino.h>
#include <util/delay.h>

#include "game_hw.h"
#include "game_draw.h"
#include "game_pics.h"
#include "game_maze.h"
#include "game_bricks.h"
#include "game_snake.h"
#include "game_drive.h"
#include "game_shooter.h"
#include "game_simon.h"
#include "game_sound.h"

void setup()
{    
    Serial.begin(9600);
    Serial.println("Start...");

    adc_Init(); 
    spi_MasterInit();
    max7219_Init();
    pkeys_Init();
    sound_Init();

    // ТЕСТ: Зажжем один пиксель в углу
    g_Clear();
    g_SetPixel(0, 0); // Левый верхний угол
    g_Update();
    Serial.println("Pixel set. Display should show 1 dot.");
}

void loop()
{
	GameMenu();
}