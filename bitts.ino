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

void setup()
{
/*	sbi(DDRD,2);
	sbi(PORTD,2);//Led
	delay_ms(500);
	cbi(PORTD,2);//Led
	delay_ms(500);
	sbi(PORTD,2);//Led*/
	
	adc_Init();//ADC is for Random number generator
 	spi_MasterInit();
 	max7219_Init();
	pkeys_Init();
	RNDpADC(10);
}

void loop()
{
	GameMenu();
}