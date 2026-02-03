//Shooter game

#include <util/delay.h>
#include <Arduino.h>
#include "game_hw.h"
#include "game_draw.h"
#include "game_shooter.h"

void shoot_DrawShip(int8_t x)
{
	if (x>0)
	{
		g_SetPixel(x-1,15);
	};
	g_SetPixel(x,15); g_SetPixel(x,14);
	if (x<7)
	{
		g_SetPixel(x+1,15);
	};
}

void shoot_GameOver(uint8_t L, int8_t *BX, int8_t *BY)
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

void shoot_DrawBullets(uint8_t N, int8_t *BX, int8_t *BY)
{
	uint8_t i;
	for (i=0;i<N;i++)
	{
		g_SetPixel(BX[i],BY[i]);
	};
}

void shoot_DrawTargets(uint8_t N, int8_t *TX, int8_t *TY)
{
	uint8_t i;
	for (i=0;i<N;i++)
	{
		g_SetPixel(TX[i],TY[i]);
	};
}

uint8_t shoot_CheckStep(int8_t X, int8_t Y, uint8_t L, int8_t *BX, int8_t *BY)
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

uint8_t shoot_DeleteBullets(uint8_t N, int8_t *BX, int8_t *BY)
{
	uint8_t i, k=0;
	for (i=0;i<N;i++)
	{
		if (BY[i]!=-1)
		{
			BX[k]=BX[i]; BY[k]=BY[i];
			k++;
		};
	};
	return k;
}

uint8_t shoot_DeleteTargets(uint8_t N, int8_t *TX, int8_t *TY)
{
	uint8_t i, k=0;
	for (i=0;i<N;i++)
	{
		if (TY[i]!=-1)
		{
			TX[k]=TX[i]; TY[k]=TY[i];
			k++;
		};
	};
	return k;
}


void shoot_Game(void)
{
	pkeys_Unused=0b11010000;

	int8_t v_BulletX[32];//Bullets position X
	int8_t v_BulletY[32];//Bullets position Y
	uint8_t v_BN=0;//Bullets number
	uint8_t v_BulletWait=1;
	int8_t v_TargetX[128];//Targets position X
	int8_t v_TargetY[128];//Targets position Y
	uint8_t v_TN=0;//Targets number
	int8_t v_X=3;//Player X position
	uint8_t v_BulletStart=0;
	uint8_t v_NotEnd=1;//Game continue?
	uint8_t v_Redraw=1;//Redraw?

	uint16_t v_CicleCount=ht0_cnt;
	uint16_t v_BulletCount=ht0_cnt;
	uint16_t v_TargetXCount=ht0_cnt;
	uint16_t v_CicleTime=GameSpeedCount()*2;

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
			if (inbit(pkeys_k4_pin,pkeys_k4_bit)==0)
			{
				pkeys_Value|=0x10;
				v_BulletWait--;
				if (v_BulletWait==0){
					v_BulletStart=1;
					v_BulletWait=2;
					};
			};
			if (pKeySwitch(0x01)==2)
			{//Up
				v_rnd++;
			};
			if (pKeySwitch(0x02)==2)
			{//Left
				if (v_X>0)
				{
					v_X--;
				};
				v_rnd++;
			};
			if (pKeySwitch(0x04)==2)
			{//Down
				v_rnd++;
			};
			if (pKeySwitch(0x08)==2)
			{//Right
				if (v_X<7)
				{
					v_X++;
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
			if ((ht0_cnt-v_BulletCount)>30/ht0_time)
			{//Byllets trajectory
				uint8_t i,j;
				v_BulletCount=ht0_cnt; v_Redraw=1;
				v_BN=shoot_DeleteBullets(v_BN, v_BulletX, v_BulletY);
				if (v_BulletStart>0)
				{//Start new bullets
					if (v_BN<31)
					{
						v_BulletX[v_BN]=v_X;
						v_BulletY[v_BN]=14;
						v_BN++;
					};
					v_BulletStart=0;
				};
				for (i=0;i<v_BN;i++)
				{
					if (v_BulletY[i]>=0)
					{
						v_BulletY[i]--;
					};
				};
				//Hit test
				for (i=0;i<v_BN;i++)
				{
					for (j=0;j<v_TN;j++)
					{
						if ((v_BulletX[i]==v_TargetX[j])&(v_BulletY[i]==v_TargetY[j]))
						{
							v_BulletY[i]=-1;
							v_TargetY[j]=-1;
							v_GamePoints++; UpdateGamePoints();
						};
					};
				};
			};
			
			if ((ht0_cnt-v_CicleCount)>v_CicleTime)
			{
				uint8_t n,i;
				v_CicleCount=ht0_cnt; v_Redraw=1;
				v_rnd++;
				
				//Targets moving
				for (i=0;i<v_TN;i++)
				{
					if (v_TargetY[i]>=0)
					{
						v_TargetY[i]++;
						if (v_TargetY[i]>15)
						{
							v_TargetY[i]=-1;
							v_NotEnd=0;
						};
					};
				};
					
				v_TN=shoot_DeleteTargets(v_TN,v_TargetX,v_TargetY);
				//New targets
				n=v_rnd%9;
				for (i=0;i<n;i++)
				{
					if (v_TN<128)
					{
						v_TargetX[v_TN]=v_rnd%8;
						v_TargetY[v_TN]=0; v_TN++;
						v_rnd++;
					};
				};
			};
			
			if ((ht0_cnt-v_TargetXCount)>30/ht0_time)
			{//Targets moving
				if (v_TN>0)
				{
					uint8_t n=0;
					uint8_t d=v_rnd%2;
					int8_t old;
					v_Redraw=1;
					if (v_TN>15)
					{
						n=v_rnd%16;
					}
					else
					{
						n=v_rnd%v_TN;
					};
					old=v_TargetX[n];
					v_TargetXCount=ht0_cnt;
					v_rnd++;

					if (d==0)
					{
						if (v_TargetX[n]>0)
						{
							v_TargetX[n]--;
						};
					};
					if (d==1)
					{
						if (v_TargetX[n]<7)
						{
							v_TargetX[n]++;
						};
						v_rnd++;
					};
					//Test targets intersection 
					for (d=0;d<v_TN;d++)
					{
						if (d!=n)
						{
							if((v_TargetY[n]>-1)&(v_TargetX[n]==v_TargetX[d])&(v_TargetY[n]==v_TargetY[d]))
							{
								v_TargetX[n]=old;
							};
						};
					};
				};
			};
		};
		
		if (v_Redraw>0)
		{
			g_Clear();
			shoot_DrawShip(v_X);
			shoot_DrawBullets(v_BN,v_BulletX,v_BulletY);
			shoot_DrawTargets(v_TN,v_TargetX,v_TargetY);
			g_Update();
			v_Redraw=0;
		};
	};
	RandomGameOver();
}
