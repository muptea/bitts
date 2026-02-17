// Draw and other helpful functions

#include <util/delay.h>
#include <Arduino.h>

#include "game_hw.h"
#include "game_pics.h"
#include "game_draw.h"
#include "game_sound.h"
#include "game_simon.h"

uint8_t gv_Buffer[gd_Bytes];

void g_SetPixel(int8_t x, int8_t y)
{
	if ((x >= 0) & (y >= 0) & (x < gd_XSize) & (y < gd_YSize))
	{
		uint8_t tmp = 2 * x;
		if (y > 7)
		{
			y -= 8;
			tmp++;
		};
		gv_Buffer[tmp] |= (1 << y);
	};
}

void g_ClearPixel(int8_t x, int8_t y)
{
	if ((x >= 0) & (y >= 0) & (x < gd_XSize) & (y < gd_YSize))
	{
		uint8_t tmp = 2 * x;
		if (y > 7)
		{
			y -= 8;
			tmp++;
		};
		gv_Buffer[tmp] &= ~(1 << y);
	};
}

void g_Clear(void)
{
	uint8_t i;
	for (i = 0; i < gd_Bytes; i++)
	{
		gv_Buffer[i] = 0;
	};
}

void g_FillAll(uint8_t v)
{
	uint8_t i;
	for (i = 0; i < gd_Bytes; i++)
	{
		gv_Buffer[i] = v;
	};
}

void g_Update(void)
{
	max7219_LoadBytes16(gv_Buffer);
}

void pic8x16_Draw(uint8_t frame, uint8_t *pic)
{
	uint16_t i, n = 16 * frame;
	uint8_t b, y = 0;
	g_Clear();
	for (i = 0; i < 16; i++)
	{
		b = pgm_read_byte(&pic[n++]);
		if ((b & (1 << 0)) > 0)
			g_SetPixel(0, y);
		if ((b & (1 << 1)) > 0)
			g_SetPixel(1, y);
		if ((b & (1 << 2)) > 0)
			g_SetPixel(2, y);
		if ((b & (1 << 3)) > 0)
			g_SetPixel(3, y);
		if ((b & (1 << 4)) > 0)
			g_SetPixel(4, y);
		if ((b & (1 << 5)) > 0)
			g_SetPixel(5, y);
		if ((b & (1 << 6)) > 0)
			g_SetPixel(6, y);
		if ((b & (1 << 7)) > 0)
			g_SetPixel(7, y);
		y++;
	};
	g_Update();
}

//============================================================
// Game

void ClearAnimation000(void)
{
	uint8_t i, j;
	for (j = 0; j < gd_YSize; j++)
	{
		for (i = 0; i < gd_XSize; i++)
		{
			g_ClearPixel(i, j);
		};
		g_Update();
		delay_ms(30);
	};
}

void ClearAnimation001(void)
{
	uint8_t i, j;
	for (j = 0; j < gd_YSize; j++)
	{
		for (i = 0; i < gd_XSize; i++)
		{
			g_ClearPixel(i, gd_YSizeM1 - j);
		};
		g_Update();
		delay_ms(30);
	};
}

void ClearAnimation002(void)
{
	uint8_t i, j;
	for (j = 0; j < gd_YSize; j++)
	{
		for (i = 0; i < gd_XSize; i++)
		{
			g_SetPixel(i, j);
		};
		g_Update();
		delay_ms(30);
	};
}

void ClearAnimation003(void)
{
	uint8_t i, j;
	for (j = 0; j < gd_YSize; j++)
	{
		for (i = 0; i < gd_XSize; i++)
		{
			g_SetPixel(i, gd_YSizeM1 - j);
		};
		g_Update();
		delay_ms(30);
	};
}

void RandomGameOver(void)
{
	uint8_t n = v_rnd % 2;
	if (n == 0)
	{
		ClearAnimation002();
		return;
	};
	if (n == 1)
	{
		ClearAnimation003();
		return;
	};
	if (n == 2)
	{
		ClearAnimation000();
		return;
	};
	if (n == 3)
	{
		ClearAnimation001();
		return;
	};
};

void GameSetAnimSize(uint8_t *GameNum, uint8_t *AnimSize)
{
	if (GameNum[0] == 0)
	{
		AnimSize[0] = 5;
		return;
	};
	if (GameNum[0] == 1)
	{
		AnimSize[0] = 5;
		return;
	};
	if (GameNum[0] == 2)
	{
		AnimSize[0] = 6;
		return;
	};
	if (GameNum[0] == 3)
	{
		AnimSize[0] = 11;
		return;
	};
	if (GameNum[0] == 4)
	{
		AnimSize[0] = 11;
		return;
	};
	if (GameNum[0] == 5)
	{
		AnimSize[0] = 13;
		return;
	};
	if (GameNum[0] == 6)
	{
		AnimSize[0] = 5;
		return;
	};
}

void GameNumUp(uint8_t *GameNum, uint8_t *AnimSize)
{
	if (GameNum[0] < (d_AllGamesNum - 1))
	{
		GameNum[0]++;
	}
	else
	{
		GameNum[0] = 0;
	};
}

void GameNumDown(uint8_t *GameNum, uint8_t *AnimSize)
{
	if (GameNum[0] > 0)
	{
		GameNum[0]--;
	}
	else
	{
		GameNum[0] = (d_AllGamesNum - 1);
	};
}

uint16_t GameSpeedCount(void)
{
	if (v_LevelSpeed == 0)
	{
		return 500 / ht0_time;
	};
	if (v_LevelSpeed == 1)
	{
		return 400 / ht0_time;
	};
	if (v_LevelSpeed == 2)
	{
		return 300 / ht0_time;
	};
	if (v_LevelSpeed == 3)
	{
		return 200 / ht0_time;
	};
	if (v_LevelSpeed == 4)
	{
		return 100 / ht0_time;
	};
	if (v_LevelSpeed == 5)
	{
		return 50 / ht0_time;
	};
	return 300 / ht0_time;
}

void GamePause(void)
{
	uint8_t sw = 0;
	uint32_t v_DelayCount = millis();
	while (1)
	{
		if (pReadKeys() > 0)
		{
			if (pkeys_Value & 0x7F)
			{
				sound_MenuBeep();
			}
			if (pKeySwitch(0x20) == 2)
			{ // Pause
				v_rnd++;
				return;
			};
			if (pKeySwitch(0x10) == 2)
			{ // Rotate
				v_rnd++;
			};
		};
		// wdr(); cli();
		if ((millis() - v_DelayCount) > 300 / ht0_time)
		{
			v_DelayCount = millis();
			sei();
			v_rnd++;
			if (sw == 0)
			{
				sw = 1;
				pic8x16_Draw(0, animation_008);
			}
			else
			{
				sw = 0;
				g_Clear();
				g_Update();
			};
		};
		// sei();
	};
}

/*Game number:
0 - Very simple bricks
1 - Classic bricks
2 - Hard bricks
3 - Snake
4 - Shooter
5 - drive
6 - Maze
*/
void GameMenu(void)
{
	pic8x16_Draw(0, animation_008);
	delay_ms(1000);

	uint8_t v_RunGame = 0;	  // Run game?
	uint8_t v_GameNumber = 0; // Game number
	uint8_t v_AnimFrame = 0;  // Current frame
	uint8_t v_AnimSize = 0;	  // Total frames
	uint8_t v_Redraw = 1;	  // Redraw?

	uint32_t v_AnimCount = millis();
	uint16_t v_CicleTime = GameSpeedCount();

	GameSetAnimSize(&v_GameNumber, &v_AnimSize);
	while (1)
	{
		pkeys_Unused = 0b11000000;
		v_rnd++;
		RNDpADC(3);
		if (pReadKeys() > 0)
		{
			if (pkeys_Value != 0)
			{
				sound_MenuBeep();
			}
			if (pKeySwitch(0x01) == 2)
			{ // Up
				GameNumUp(&v_GameNumber, &v_AnimSize);
				GameSetAnimSize(&v_GameNumber, &v_AnimSize);
				v_AnimFrame = 0;
				v_AnimCount = millis();
				v_Redraw = 1;
				v_rnd++;
			};
			if (pKeySwitch(0x02) == 2)
			{ // Left
				if (v_LevelSpeed > 0)
					v_LevelSpeed--;
				v_CicleTime = GameSpeedCount();
				v_Redraw = 1;
				v_rnd++;
			};
			if (pKeySwitch(0x04) == 2)
			{ // Down
				GameNumDown(&v_GameNumber, &v_AnimSize);
				GameSetAnimSize(&v_GameNumber, &v_AnimSize);
				v_AnimFrame = 0;
				v_AnimCount = millis();
				v_Redraw = 1;
				v_rnd++;
			};
			if (pKeySwitch(0x08) == 2)
			{ // Right
				if (v_LevelSpeed < 4)
					v_LevelSpeed++;
				v_CicleTime = GameSpeedCount();
				v_Redraw = 1;
				v_rnd++;
			};
			if (pKeySwitch(0x10) == 2)
			{ // Rotate
				v_RunGame = 1;
				v_Redraw = 1;
				v_rnd++;
			};
		};

		wdr();

		if ((millis() - v_AnimCount) > v_CicleTime)
		{
			v_AnimCount = millis();
			v_Redraw = 1;
			v_rnd++;
			if (v_AnimFrame < v_AnimSize)
			{
				v_AnimFrame++;
			}
			else
			{
				v_AnimFrame = 0;
			};
		};

		if (v_Redraw > 0)
		{
			switch (v_GameNumber)
			{
			case 0:
			{
				pic8x16_Draw(v_AnimFrame, animation_000);
				break;
			};
			case 1:
			{
				pic8x16_Draw(v_AnimFrame, animation_001);
				break;
			};
			case 2:
			{
				pic8x16_Draw(v_AnimFrame, animation_002);
				break;
			};
			case 3:
			{
				pic8x16_Draw(v_AnimFrame, animation_003);
				break;
			};
			case 4:
			{
				pic8x16_Draw(v_AnimFrame, animation_004);
				break;
			};
			case 5:
			{
				pic8x16_Draw(v_AnimFrame, animation_005);
				break;
			};
			case 6:
			{
				pic8x16_Draw(v_AnimFrame, animation_006);
				break;
			};
			case 7:
			{
				pic8x16_Draw(v_AnimFrame, animation_008);
				break;
			};
			};
			v_Redraw = 0;
		};

		if (v_RunGame > 0)
		{
			switch (v_GameNumber)
			{
			case 0:
			{
				bricks_Game(0);
				break;
			};
			case 1:
			{
				bricks_Game(1);
				break;
			};
			case 2:
			{
				bricks_Game(2);
				break;
			};
			case 3:
			{
				snake_Game();
				break;
			};
			case 4:
			{
				shoot_Game();
				break;
			};
			case 5:
			{
				drive_Game();
				break;
			};
			case 6:
			{
				maze_Game();
				break;
			};
			case 7:
			{
				simon_Game();
				break;
			};
			};
			v_RunGame = 0;
		};
	};
}

void UpdateGamePoints(void)
{
	// No Game points indicators
}
