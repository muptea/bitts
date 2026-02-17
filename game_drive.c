//Ship game

#include <util/delay.h>
#include <Arduino.h>
#include "game_hw.h"
#include "game_draw.h"
#include "game_drive.h"
#include "game_sound.h"

void drive_Explode01(int8_t x)
{
	g_SetPixel(x,13);
	g_ClearPixel(x,12);
	g_ClearPixel(x,14);
	g_ClearPixel(x-1,13);
	g_ClearPixel(x+1,13);
	g_ClearPixel(x-1,12);
	g_ClearPixel(x+1,12);
	g_ClearPixel(x-1,14);
	g_ClearPixel(x+1,14);
}

void drive_Explode02(int8_t x)
{
	g_ClearPixel(x,13);
	g_SetPixel(x,12);
	g_SetPixel(x,14);
	g_SetPixel(x-1,13);
	g_SetPixel(x+1,13);
	g_SetPixel(x-1,12);
	g_SetPixel(x+1,12);
	g_SetPixel(x-1,14);
	g_SetPixel(x+1,14);
}

void drive_GameOver(int8_t x)
{//Explode animation
	delay_ms(30);
	g_ClearPixel(x,13); g_Update(); delay_ms(30);
	drive_Explode01(x); g_Update(); delay_ms(30);
	drive_Explode02(x); g_Update(); delay_ms(30);
	drive_Explode01(x); g_Update(); delay_ms(30);
	drive_Explode02(x); g_Update(); delay_ms(30);
	drive_Explode01(x); g_ClearPixel(x,13);
	g_Update();
}

void drive_ClearMap(uint8_t *map)
{
	uint8_t i;
	for (i=0;i<128;i++)
	{
		map[i]=0;
	};
}

void drive_NewMap(int8_t *R1,int8_t *R2, uint8_t *map)
{
	uint8_t k=0b111;
	uint8_t m=0xFF;
	uint8_t z=v_rnd%3;
	uint8_t n;
	if (z==0)
	{
		if (R1[0]<5) R1[0]++;
	};
	if (z==2)
	{
		if (R1[0]>0) R1[0]--;
	};
	k<<=R1[0];
	m&=~k;
	z=(v_rnd>>4)%3;
	if (z==0)
	{
		if (R2[0]<5) R2[0]++;
	};
	if (z==2)
	{
		if (R2[0]>0) R2[0]--;
	};
	
	k=0b111;
	k<<=R2[0];
	m&=~k;
	for (k=0;k<15;k++)
	{
		z=(14-k)*8;
		n=z+8;
		map[n++]=map[z++];
		map[n++]=map[z++];
		map[n++]=map[z++];
		map[n++]=map[z++];
		map[n++]=map[z++];
		map[n++]=map[z++];
		map[n++]=map[z++];
		map[n]=map[z];
	};
	
	if ((m&0x01)>0) map[0]=1; else map[0]=0;
	if ((m&0x02)>0) map[1]=1; else map[1]=0;
	if ((m&0x04)>0) map[2]=1; else map[2]=0;
	if ((m&0x08)>0) map[3]=1; else map[3]=0;
	if ((m&0x10)>0) map[4]=1; else map[4]=0;
	if ((m&0x20)>0) map[5]=1; else map[5]=0;
	if ((m&0x40)>0) map[6]=1; else map[6]=0;
	if ((m&0x80)>0) map[7]=1; else map[7]=0;
}

uint8_t drive_TestX(int8_t x, uint8_t *map)
{
	if (map[x+8*13]>0)
	{
		return 1;
	}
	else
	{
		if (map[x+8*14]>0)
		{
			return 1;
		};
	};
	return 0;
}

uint8_t drive_BRun(uint8_t run,int8_t x,int8_t *y, uint8_t *map)
{
	if (run>0)
	{
		uint8_t tmp=x+8*y[0];
		if (map[tmp]>0)
		{
			map[tmp]=0;
			return 0;
		};
		
		if (y[0]>0)
		{
			y[0]--;
			tmp=x+8*y[0];
			if (map[tmp]>0)
			{
				map[tmp]=0;
				return 0;
			};
			return 1;
		}
		else
		{
			return 0;
		};
	};
	return 0;
}


uint8_t drive_GetTimeCycle(uint8_t speed)
{
	if (speed==0) return 700/ht0_time;
	if (speed==1) return 600/ht0_time;
	if (speed==2) return 500/ht0_time;
	if (speed==3) return 400/ht0_time;
	if (speed==4) return 300/ht0_time;
	if (speed==5) return 200/ht0_time;
	return 100/ht0_time;
}

void drive_Game(void){
	pkeys_Unused=0b11000000;

	uint8_t v_Map[128];
	int8_t v_X=3;//Player position
	int8_t v_BX=0,v_BY=0;//Bullet position
	uint8_t v_BRun=0;//Bullet fly
	uint8_t v_PointsCounter=0;//Game pointers
	int8_t v_Road1=3,v_Road2=4;//Roads positions
	uint8_t v_ManState=0;//Player blink
	uint8_t v_NotEnd=1;//Game continue?
	uint8_t v_Redraw=1;//Redraw?
	uint8_t v_Speed=0;//Speed
	uint16_t v_CycleCount=ht0_cnt;
	uint16_t v_ManBlink=ht0_cnt;
	uint8_t v_TimeCycle=70;

	v_TimeCycle=drive_GetTimeCycle(v_Speed);
	v_GamePoints=0; UpdateGamePoints();
	v_NotEnd=1; v_Redraw=1;
	drive_ClearMap(v_Map);
	g_Clear(); g_Update();
	
	while(v_NotEnd)
	{
		wdr(); v_rnd++;

        if (pKeySwitch(0x40) == 2) 
        {
            v_NotEnd = 0;
			sound_GameOver();
            continue;
        }

		if (pReadKeys())
		{
			if (pKeyPressed(0x01)==2)
			{//Up
				if (v_Speed<6) v_Speed++;
				v_TimeCycle=drive_GetTimeCycle(v_Speed);
				v_rnd++;
			};
			if (pKeySwitch(0x02)==2)
			{//Left
				if (v_X>0) v_X--;
				if (drive_TestX(v_X,v_Map)>0)
				{
					v_X++;
				};
				v_rnd++;
			};
			if (pKeySwitch(0x04)==2)
			{//Down
				if (v_Speed>0) v_Speed--;
				v_TimeCycle=drive_GetTimeCycle(v_Speed);
				v_rnd++;
			};
			if (pKeySwitch(0x08)==2)
			{//Right
				if (v_X<7) v_X++;
				if (drive_TestX(v_X,v_Map)>0)
				{
					v_X--;
				};
				v_rnd++;
			};
			if (pKeySwitch(0x10)==2)
			{//Rotate
				if (v_BRun==0)
				{
					v_BRun=1;
					v_BX=v_X;
					v_BY=13;
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
			if ((ht0_cnt-v_CycleCount)>v_TimeCycle)
			{//New road
				v_CycleCount=ht0_cnt; sei(); v_Redraw=1;
				drive_NewMap(&v_Road1,&v_Road2,v_Map);
				if (v_PointsCounter<100)
				{
					v_PointsCounter++;
				}
				else
				{
					v_GamePoints++; UpdateGamePoints();
					v_PointsCounter=0;
				};
			};
			cli();
			
			if ((ht0_cnt-v_ManBlink)>50/ht0_time)
			{//Blink
				v_ManBlink=ht0_cnt; sei(); v_Redraw=1;
				if (v_ManState>0)
				{
					v_ManState=0;
				}
				else
				{
					v_ManState=1;
				};
				v_BRun=drive_BRun(v_BRun,v_BX,&v_BY,v_Map);
			};
			sei();
		};
		
		if (v_Redraw>0)
		{
			g_Clear();
			int8_t i,j;
			for (j=0;j<16;j++)
			{
				for (i=0; i<8; i++)
				{
					if (v_Map[j*8+i]>0)
					{
						g_SetPixel(i,j);
					};
				};
			};
			if (v_ManState)
			{
				g_SetPixel(v_X,13);
				g_SetPixel(v_X,14);
			};
			if (v_BRun>0)
			{
				g_SetPixel(v_BX,v_BY);
			};
			g_Update();
			if (v_Map[13*8+v_X]>0)
			{
				drive_GameOver(v_X);
				v_NotEnd=0;
			};
			v_Redraw=0;
		};
	};
	sound_GameOver();
	RandomGameOver();
};
