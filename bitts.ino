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
    sound_Init();
    
    adc_Init(); 
    spi_MasterInit();
    max7219_Init();
    pkeys_Init();
    RNDpADC(10);
    
    sound_MenuBeep();
}

void loop()
{
	GameMenu();
}