//Maze game

#include <util/delay.h>
#include <Arduino.h>
#include "game_hw.h"
#include "game_draw.h"
#include "game_pics.h"
#include "game_maze.h"

void maze_LoadLevel(uint8_t *level,uint8_t *map){
uint16_t i,n=0;
uint8_t b;
for (i=0;i<128;i++){
	b=pgm_read_byte(&level[i]);
	if ((b&(1<<0))>0) map[n]=1; else map[n]=0;
	n++;
	if ((b&(1<<1))>0) map[n]=1; else map[n]=0;
	n++;
	if ((b&(1<<2))>0) map[n]=1; else map[n]=0;
	n++;
	if ((b&(1<<3))>0) map[n]=1; else map[n]=0;
	n++;
	if ((b&(1<<4))>0) map[n]=1; else map[n]=0;
	n++;
	if ((b&(1<<5))>0) map[n]=1; else map[n]=0;
	n++;
	if ((b&(1<<6))>0) map[n]=1; else map[n]=0;
	n++;
	if ((b&(1<<7))>0) map[n]=1; else map[n]=0;
	n++;
	};
}

void maze_LoadLevelHM(uint8_t *level,uint8_t *map){
uint16_t i,n=0;
uint8_t b;
for (i=0;i<128;i++){
	b=pgm_read_byte(&level[127-i]);
	if ((b&(1<<7))>0) map[n]=1; else map[n]=0;
	n++;
	if ((b&(1<<6))>0) map[n]=1; else map[n]=0;
	n++;
	if ((b&(1<<5))>0) map[n]=1; else map[n]=0;
	n++;
	if ((b&(1<<4))>0) map[n]=1; else map[n]=0;
	n++;
	if ((b&(1<<3))>0) map[n]=1; else map[n]=0;
	n++;
	if ((b&(1<<2))>0) map[n]=1; else map[n]=0;
	n++;
	if ((b&(1<<1))>0) map[n]=1; else map[n]=0;
	n++;
	if ((b&(1<<0))>0) map[n]=1; else map[n]=0;
	n++;
	};
}

void maze_GameOver(uint8_t L, int8_t *BX, int8_t *BY)
{
	g_Clear();
}

uint8_t maze_GetMapValue(int16_t x, int16_t y, uint8_t *map)
{
	if ((x>=0)&(x<32)&(y>=0)&(y<32))
	{
		y*=32; y+=x;
		return map[y];
	}
	else
	{
		if (x<-1) return 0;
		if (y<-1) return 0;
		if (x>32) return 0;
		if (y>32) return 0;
		return 1;
	};
}

uint8_t maze_GetStep(int16_t x, int16_t y, uint8_t *map)
{
	if ((x>-1)&(x<32)&(y>-1)&(y<32))
	{
		y*=32;
		y+=x;
		if (map[y]==1)
		{
			return 1;
		}
		else
		{
			return 0;
		};
	}
	else
	{
		return 1;
	};
}

void maze_SetMapValue(int16_t x, int16_t y, uint8_t *map, uint8_t v)
{
	if ((x>-1)&(x<32)&(y>-1)&(y<32))
	{
		y*=32; y+=x;
		map[y]=v;
	};
}

uint16_t maze_CreatePoints(uint8_t *map)
{
	uint16_t n=0;
	uint8_t k,m,h;
	int8_t i, j;
	for (j=0;j<32;j++)
	{
		for (i=0;i<32;i++)
		{
			if (maze_GetMapValue(i,j, map)==0)
			{
				k=0; m=0; h=0;
				if (maze_GetStep(i-1,j-1, map)==1) m+=(1<<0);
				if (maze_GetStep(i,j-1, map)==1) m+=(1<<1);
				if (maze_GetStep(i+1,j-1, map)==1) m+=(1<<2);
				if (maze_GetStep(i+1,j, map)==1) m+=(1<<3);
				if (maze_GetStep(i+1,j+1, map)==1) m+=(1<<4);
				if (maze_GetStep(i,j+1, map)==1) m+=(1<<5);
				if (maze_GetStep(i-1,j+1, map)==1) m+=(1<<6);
				if (maze_GetStep(i-1,j, map)==1) m+=(1<<7);

				if (v_rnd&0x01)
				{
					v_rnd++;
					if (m==0xF7) k++;
					if (m==0xE7) k++;
					if (m==0xF3) k++;
					if (m==0xE3) k++;
				};
				
				if (m==0xDF) k++;
				if (m==0x9F) k++;
				if (m==0xCF) k++;
				if (m==0x8F) k++;
				
				if (v_rnd&0x02)
				{
					if (m==0x7F) k++;
					if (m==0x3F) k++;
					if (m==0x7E) k++;
					if (m==0x3E) k++;
				};
				
				if (v_rnd&0x04)
				{
					if (m==0xFD) k++;
					if (m==0xFC) k++;
					if (m==0xF9) k++;
					if (m==0xF8) k++;
				};
				
				if (m==0xE2) k++;
				if (m==0xA3) k++;
				if (m==0xA2) k++;
				if (m==0xB6) k++;
				if (m==0xF6) k++;
				if (m==0xB7) k++;

				if (v_rnd&0x08)
				{
					if (m==0x8E) k++;
					if (m==0x8B) k++;
					if (m==0x8A) k++;
					if (m==0xDE) k++;
					if (m==0xDB) k++;
					if (m==0xDA) k++;
				};
				
				if (v_rnd&0x10)
				{
					if (m==0x3A) k++;
					if (m==0x2E) k++;
					if (m==0x2A) k++;
					if (m==0x6B) k++;
					if (m==0x6F) k++;
					if (m==0x7B) k++;
				};
				
				if (m==0xB8) k++;
				if (m==0xE8) k++;
				if (m==0xA8) k++;
				if (m==0xAD) k++;
				if (m==0xED) k++;
				if (m==0xBD) k++;
				
				if (v_rnd&0x20)
				{
					if (m==0xB9) k++;
					if (m==0xBC) k++;
					if (m==0xAC) k++;
					if (m==0xA9) k++;
					if (m==0xE9) k++;
					if (m==0xEC) k++;
				};
				
				if (v_rnd&0x40)
				{
					if (m==0xF2) k++;
					if (m==0xE6) k++;
					if (m==0xA7) k++;
					if (m==0xB3) k++;
					if (m==0xB2) k++;
					if (m==0xA6) k++;
				};

				if (m==0xCB) k++;
				if (m==0x9B) k++;
				if (m==0x9E) k++;
				if (m==0xCE) k++;
				if (m==0xCA) k++;
				if (m==0x9A) k++;

				if (v_rnd&0x80)
				{
				if (m==0x6E) k++;
				if (m==0x2F) k++;
				if (m==0x7A) k++;
				if (m==0x2B) k++;
				if (m==0x3B) k++;
				if (m==0x6A) k++;
				};

				if (k>0)
				{
					maze_SetMapValue(i,j,map,2);
					v_rnd++; n++;
				};
				v_rnd++;
				RNDpADC(3);
			};
		};
		wdr();
	};
return n;
}

void maze_CreateMan(int8_t *x, int8_t *y, uint8_t *map)
{
	uint16_t n=(uint16_t)v_rnd;
	n*=4;
	while (map[n]!=0)
	{
		if (n<1023)
		{
			n++;
		}
		else
		{
			n=0;
		};
		wdr();
	};
	x[0]=n%32;
	y[0]=n/32;
};

uint8_t maze_Step(uint16_t *n, int8_t x, int8_t y, uint8_t *map)
{
	uint8_t m=maze_GetMapValue(x,y,map);
	if (m==1) return 1;
	if (m==2)
	{
		maze_SetMapValue(x,y,map,0);
		if (n[0]>0) n[0]--;
		v_GamePoints=n[0]; UpdateGamePoints();
	};
	return 0;
}

void maze_CreateLevel(uint8_t *map)
{
	uint8_t rnd=v_rnd%35;
	switch (rnd)
	{
		case  0:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_000,map); else maze_LoadLevelHM(maze_Level_000,map); return;};
		case  1:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_001,map); else maze_LoadLevelHM(maze_Level_001,map); return;};
		case  2:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_002,map); else maze_LoadLevelHM(maze_Level_002,map); return;};
		case  3:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_003,map); else maze_LoadLevelHM(maze_Level_003,map); return;};
		case  4:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_004,map); else maze_LoadLevelHM(maze_Level_004,map); return;};
		case  5:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_005,map); else maze_LoadLevelHM(maze_Level_005,map); return;};
		case  6:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_006,map); else maze_LoadLevelHM(maze_Level_006,map); return;};
		case  7:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_007,map); else maze_LoadLevelHM(maze_Level_007,map); return;};
		case  8:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_008,map); else maze_LoadLevelHM(maze_Level_008,map); return;};
		case  9:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_009,map); else maze_LoadLevelHM(maze_Level_009,map); return;};
		case 10:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_010,map); else maze_LoadLevelHM(maze_Level_010,map); return;};
		case 11:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_011,map); else maze_LoadLevelHM(maze_Level_011,map); return;};
		case 12:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_012,map); else maze_LoadLevelHM(maze_Level_012,map); return;};
		case 13:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_013,map); else maze_LoadLevelHM(maze_Level_013,map); return;};
		case 14:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_014,map); else maze_LoadLevelHM(maze_Level_014,map); return;};
		case 15:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_015,map); else maze_LoadLevelHM(maze_Level_015,map); return;};
		case 16:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_016,map); else maze_LoadLevelHM(maze_Level_016,map); return;};
		case 17:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_017,map); else maze_LoadLevelHM(maze_Level_017,map); return;};
		case 18:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_018,map); else maze_LoadLevelHM(maze_Level_018,map); return;};
		case 19:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_019,map); else maze_LoadLevelHM(maze_Level_019,map); return;};
		case 20:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_020,map); else maze_LoadLevelHM(maze_Level_020,map); return;};
		case 21:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_021,map); else maze_LoadLevelHM(maze_Level_021,map); return;};
		case 22:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_022,map); else maze_LoadLevelHM(maze_Level_022,map); return;};
		case 23:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_023,map); else maze_LoadLevelHM(maze_Level_023,map); return;};
		case 24:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_024,map); else maze_LoadLevelHM(maze_Level_024,map); return;};
		case 25:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_025,map); else maze_LoadLevelHM(maze_Level_025,map); return;};
		case 26:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_026,map); else maze_LoadLevelHM(maze_Level_026,map); return;};
		case 27:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_027,map); else maze_LoadLevelHM(maze_Level_027,map); return;};
		case 28:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_028,map); else maze_LoadLevelHM(maze_Level_028,map); return;};
		case 29:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_029,map); else maze_LoadLevelHM(maze_Level_029,map); return;};
		case 30:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_030,map); else maze_LoadLevelHM(maze_Level_030,map); return;};
		case 31:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_031,map); else maze_LoadLevelHM(maze_Level_031,map); return;};
		case 32:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_032,map); else maze_LoadLevelHM(maze_Level_032,map); return;};
		case 33:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_033,map); else maze_LoadLevelHM(maze_Level_033,map); return;};
		case 34:{ if ((v_rnd&0x80)>0) maze_LoadLevel(maze_Level_034,map); else maze_LoadLevelHM(maze_Level_034,map); return;};
	};
}

int8_t maze_ShiftUp(int8_t s)
{
	if (s<64) s++;
	return s;
}

int8_t maze_ShiftDown(int8_t s)
{
	if (s>-64) s--;
	return s;
}

void maze_Game(void)
{
	pkeys_Unused=0b11010000;
	uint8_t v_Map[1024];
	uint16_t v_PN=0;
	int8_t v_X=0,v_Y=0;
	int8_t v_SX=0,v_SY=0;
	uint8_t v_SW=0;

	uint8_t v_ManState=0;
	uint8_t v_PState=0;
	uint8_t v_NotEnd=1;
	uint8_t v_Redraw=1;
	uint16_t v_ManBlink=ht0_cnt;
	uint16_t v_PBlink=ht0_cnt;

	maze_CreateLevel(v_Map);
	v_PN=maze_CreatePoints(v_Map);
	maze_CreateMan(&v_X,&v_Y, v_Map);
	v_GamePoints=v_PN; UpdateGamePoints();
	v_NotEnd=1; v_Redraw=1;
	g_Clear(); g_Update();
	while (v_NotEnd)
	{
		wdr(); v_rnd++;

		if (pKeySwitch(0x40) == 2) 
        {
            v_NotEnd = 0;
            continue;
        }

		if (pReadKeys())
		{
			if (inbit(pkeys_k4_pin,pkeys_k4_bit)==0)
			{
				pkeys_Value|=0x10;
				v_SW=1;
				v_rnd++;
			}
			else
			{
				v_SW=0; v_SX=0; v_SY=0;
			};
			
			if (pKeySwitch(0x01)==2)
			{//Up
				if (v_SW==0)
				{
					v_Y--;
					if (maze_Step(&v_PN,v_X,v_Y,v_Map))
					{
						v_Y++; v_rnd++;
					};
				}
				else
				{
					v_SY=maze_ShiftDown(v_SY);
				};
				v_rnd++;
			};
			
			if (pKeySwitch(0x02)==2)
			{//Left
				if (v_SW==0)
				{
					v_X--;
					if (maze_Step(&v_PN,v_X,v_Y,v_Map))
					{
						v_X++; v_rnd++;
					};
				}
				else
				{
					v_SX=maze_ShiftDown(v_SX);
				};
				v_rnd++;
			};
			
			if (pKeySwitch(0x04)==2)
			{//Down
				if (v_SW==0)
				{
					v_Y++;
					if (maze_Step(&v_PN,v_X,v_Y,v_Map))
					{
						v_Y--; v_rnd++;
					};
				}
				else
				{
					v_SY=maze_ShiftUp(v_SY);
				};
				v_rnd++;
			};
			
			if (pKeySwitch(0x08)==2)
			{//Right
				if (v_SW==0)
				{
					v_X++;
					if (maze_Step(&v_PN,v_X,v_Y,v_Map))
					{
						v_X--; v_rnd++;
					};
				}
				else
				{
					v_SX=maze_ShiftUp(v_SX);
				};
				v_rnd++;
			};
			
			if (pKeySwitch(0x20)==2)
			{//Pause
				GamePause();
				v_Redraw=1; v_rnd++;
			};
		}
		else
		{
			cli();
			if ((ht0_cnt-v_ManBlink)>50/ht0_time)
			{
				v_ManBlink=ht0_cnt; sei(); v_Redraw=1;
				if (v_ManState>0)
				{
					v_ManState=0;
				}
				else
				{
					v_ManState=1;
				};
			};
			cli();
			if ((ht0_cnt-v_PBlink)>200/ht0_time)
			{
				v_PBlink=ht0_cnt; sei(); v_Redraw=1;
				if (v_PState>0)
				{
					v_PState=0;
				}
				else
				{
					v_PState=1;
				};
			};
			sei();
		};
		
		if (v_Redraw>0)
		{
			g_Clear();
			int8_t i,j;
			uint8_t m;
			for (j=0;j<16;j++)
			{
				for (i=0; i<8; i++)
				{
					m=maze_GetMapValue(i-4+v_X+v_SX,j-7+v_Y+v_SY,v_Map);
					if (m==1)
					{
						g_SetPixel(i,j);
					};
					if (m==2)
					{
						if (v_PState)
						{
							g_SetPixel(i,j);
						};
					};
				};
			};
			
			if ((v_SW==0)&(v_ManState>0))
			{
				g_SetPixel(4,7);
			};
			g_Update(); v_Redraw=0;
			
			if (v_PN==0) v_NotEnd=0;
		};
	};
	RandomGameOver();
};