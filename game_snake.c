//Snake game

#include <util/delay.h>
#include <Arduino.h>
#include "game_hw.h"
#include "game_draw.h"
#include "game_snake.h"

void snake_DrawBody(uint8_t L, int8_t *BX, int8_t *BY)
{
	uint8_t i;
	for (i=0;i<L;i++)
	{
		g_SetPixel(BX[i],BY[i]);
	};
}

void snake_GameOver(uint8_t L, int8_t *BX, int8_t *BY)
{
	uint8_t i;
	for (i=0;i<L;i++)
	{
		delay_ms(30);
		g_ClearPixel(BX[i],BY[i]);
		g_Update();
	};
	g_Clear();
}


void snake_Step(int8_t X, int8_t Y, uint8_t L, int8_t *BX, int8_t *BY)
{
	uint8_t i,n=0;
	L--;
	for (i=0;i<L;i++)
	{
		n=L-i;
		BX[n]=BX[n-1]; BY[n]=BY[n-1];
	};
	BX[0]=X; BY[0]=Y;
}

uint8_t snake_CheckStep(int8_t X, int8_t Y, uint8_t L, int8_t *BX, int8_t *BY)
{
	uint8_t i;
	for (i=0;i<L;i++)
	{
		if ((BX[i]==X)&(BY[i]==Y))
		{
			return 1;
		};
	};
	
	if (X<0) return 1;
	if (Y<0) return 1;
	if (X>7) return 1;
	if (Y>15) return 1;
	
	return 0;
}

void snake_NewFood(int8_t HX, int8_t HY, uint8_t BL, int8_t *BX, int8_t *BY, int8_t *FX, int8_t *FY)
{
	int8_t BufX[128];
	int8_t BufY[128];
	uint8_t i, j, k=0;
	
	for (j=0;j<16;j++)
	{
		for (i=0;i<8;i++)
		{
			BufX[k]=i; BufY[k]=j; k++;
		};
	};
	
	k=0;
	for (i=0;i<BL;i++)
	{
		k=BY[i]*8+BX[i];
		BufX[k]=-1; BufY[k]=-1;
	};
	
	k=HY*8+HX;
	BufX[k]=-1; BufY[k]=-1;
	
	k=0;
	for (i=0;i<128;i++)
	{
		if (BufX[i]!=-1)
		{
			BufX[k]=BufX[i]; BufY[k]=BufY[i];
			k++;
		};
	};
	
	i=v_rnd%k;
	FX[0]=BufX[i];
	FY[0]=BufY[i];
}



void snake_Game(void)
{
	int8_t v_BodyX[128];//X positions
	int8_t v_BodyY[128];//Y positions
	uint8_t v_Dir=0, v_DirNew=0;//Moving drirection (=0 down, =1 right, =2 up, =3 left)
	uint8_t v_L=2;//Snake length (without head)
	int8_t v_X=3,v_Y=2;//Head position
	int8_t v_Fx=3,v_Fy=3;//Food position
	uint8_t v_HeadState=0; //Head blink
	uint8_t v_FoodState=0; //Food blink
	uint8_t v_NotEnd=1;//Game continue?
	uint8_t v_Redraw=1;//Redraw?

	uint16_t v_CicleCount=ht0_cnt;
	uint16_t v_HeadBlink=ht0_cnt;//Head blink timer
	uint16_t v_FoodBlink=ht0_cnt;//Food blink timer
	uint16_t v_CicleTime=GameSpeedCount();

	pkeys_Unused=0b11000000;
	
	//Start positon
	v_BodyX[0]=3; v_BodyY[0]=1;
	v_BodyX[1]=3; v_BodyY[1]=0;
	
	snake_NewFood(v_X,v_Y,v_L,v_BodyX,v_BodyY,&v_Fx,&v_Fy);
	v_GamePoints=0; UpdateGamePoints();
	v_NotEnd=1; v_Redraw=1;
	g_Clear(); g_Update();
	
	while(v_NotEnd)
	{
		wdr(); v_rnd++;

		if (pKeySwitch(0x40) == 2) 
        {
            v_NotEnd = 0;
            continue;
        }

		if (pReadKeys())
		{
			if (pKeySwitch(0x01)==2)
			{//Up
				v_DirNew=2;
				v_rnd++;
			};
			if (pKeySwitch(0x02)==2)
			{//Left
				v_DirNew=3;
				v_rnd++;
			};
			if (pKeySwitch(0x04)==2)
			{//Down
				v_DirNew=0;
				v_rnd++;
			};
			if (pKeySwitch(0x08)==2)
			{//Right
				v_DirNew=1;
				v_rnd++;
			};
			if (pKeySwitch(0x10)==2)
			{//Rotate
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
			if ((ht0_cnt-v_HeadBlink)>50/ht0_time)
			{//Head blinks
				v_HeadBlink=ht0_cnt; v_Redraw=1;
				if (v_HeadState>0)
				{
					v_HeadState=0;
				}
				else
				{
					v_HeadState=1;
				};
			};
			
			if ((ht0_cnt-v_FoodBlink)>200/ht0_time)
			{//Food blinks
				v_FoodBlink=ht0_cnt; v_Redraw=1;
				if (v_FoodState>0)
				{
					v_FoodState=0;
				}
				else
				{
					v_FoodState=1;
				};
			};

			if ((ht0_cnt-v_CicleCount)>v_CicleTime)
			{//Snake moving
				uint8_t f_eat=0;
				v_rnd++;
				v_CicleCount=ht0_cnt; v_Redraw=1;
				if (v_DirNew==2)
				{//Up
					if (v_Dir!=0)
					{
						v_Dir=2;
					};
				};
				if (v_DirNew==3)
				{//Left
					if (v_Dir!=1)
					{
						v_Dir=3;
					};
				};
				if (v_DirNew==0)
				{//Down
					if (v_Dir!=2)
					{
						v_Dir=0;
					};
				};
				if (v_DirNew==1)
				{//Right
					if (v_Dir!=3)
					{
						v_Dir=1;
					};
				};
				if ((v_X==v_Fx)&(v_Y==v_Fy))
				{//Find food
					v_L++; f_eat=1;
				};
				
				snake_Step(v_X,v_Y,v_L,v_BodyX,v_BodyY);
				if (v_Dir==0)
				{
					v_Y++;
				};
				if (v_Dir==1)
				{
					v_X++;
				};
				if (v_Dir==2)
				{
					v_Y--;
				};
				if (v_Dir==3)
				{
					v_X--;
				};
				if (f_eat)
				{
					v_GamePoints++; UpdateGamePoints();
					snake_NewFood(v_X,v_Y,v_L,v_BodyX,v_BodyY,&v_Fx,&v_Fy);
				};
				v_rnd++;
				if (snake_CheckStep(v_X,v_Y,v_L,v_BodyX,v_BodyY)>0)
				{
					v_NotEnd=0; v_Redraw=0;
				};
			};
		};

		if (v_Redraw>0)
		{
			g_Clear();
			snake_DrawBody(v_L,v_BodyX,v_BodyY);
			if (v_HeadState)
			{
				g_SetPixel(v_X,v_Y);
			};
			if (v_FoodState)
			{
				g_SetPixel(v_Fx,v_Fy);
			};
			g_Update();
			v_Redraw=0;
		};
	};
	
	snake_GameOver(v_L,v_BodyX,v_BodyY);//Delete snake
	RandomGameOver();
};
