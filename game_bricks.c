//Tetris game

#include <util/delay.h>
#include <Arduino.h>

#include "game_hw.h"
#include "game_draw.h"
#include "game_bricks.h"


static void bricks_LoadFig000(uint8_t *bm)
{
	/*


		#
			 */
	bm[0]=0; bm[1]=0; bm[2]=0; bm[3]=0;
	bm[4]=0; bm[5]=0; bm[6]=0; bm[7]=0;
	bm[8]=0; bm[9]=0; bm[10]=0; bm[11]=0;
	bm[12]=1; bm[13]=0; bm[14]=0; bm[15]=0;
	bm[16]=0; bm[17]=0; bm[18]=0; bm[19]=0;
	bm[20]=0; bm[21]=0; bm[22]=0; bm[23]=0;
	bm[24]=1; bm[25]=0; bm[26]=0; bm[27]=0;
	bm[28]=1; bm[29]=0; bm[30]=0; bm[31]=0;
	bm[32]=0; bm[33]=0; bm[34]=0; bm[35]=0;
	bm[36]=1; bm[37]=0; bm[38]=0; bm[39]=0;
	bm[40]=1; bm[41]=0; bm[42]=0; bm[43]=0;
	bm[44]=1; bm[45]=0; bm[46]=0; bm[47]=0;
	bm[48]=1; bm[49]=0; bm[50]=0; bm[51]=0;
	bm[52]=1; bm[53]=0; bm[54]=0; bm[55]=0;
	bm[56]=1; bm[57]=0; bm[58]=0; bm[59]=0;
	bm[60]=1; bm[61]=0; bm[62]=0; bm[63]=0;
}


static void bricks_LoadFig001(uint8_t *bm)
{
	/*

		 #
		##
			 */
	bm[0]=0; bm[1]=0; bm[2]=0; bm[3]=0;
	bm[4]=0; bm[5]=0; bm[6]=0; bm[7]=0;
	bm[8]=0; bm[9]=1; bm[10]=0; bm[11]=0;
	bm[12]=1; bm[13]=1; bm[14]=0; bm[15]=0;
	bm[16]=0; bm[17]=0; bm[18]=0; bm[19]=0;
	bm[20]=0; bm[21]=0; bm[22]=0; bm[23]=0;
	bm[24]=1; bm[25]=1; bm[26]=0; bm[27]=0;
	bm[28]=0; bm[29]=1; bm[30]=0; bm[31]=0;
	bm[32]=0; bm[33]=0; bm[34]=0; bm[35]=0;
	bm[36]=0; bm[37]=0; bm[38]=0; bm[39]=0;
	bm[40]=1; bm[41]=1; bm[42]=0; bm[43]=0;
	bm[44]=1; bm[45]=0; bm[46]=0; bm[47]=0;
	bm[48]=0; bm[49]=0; bm[50]=0; bm[51]=0;
	bm[52]=0; bm[53]=0; bm[54]=0; bm[55]=0;
	bm[56]=1; bm[57]=0; bm[58]=0; bm[59]=0;
	bm[60]=1; bm[61]=1; bm[62]=0; bm[63]=0;
}

static void bricks_LoadFig002(uint8_t *bm)
{
	/*

		#
		#
			 */
	bm[0]=0; bm[1]=0; bm[2]=0; bm[3]=0;
	bm[4]=0; bm[5]=0; bm[6]=0; bm[7]=0;
	bm[8]=1; bm[9]=0; bm[10]=0; bm[11]=0;
	bm[12]=1; bm[13]=0; bm[14]=0; bm[15]=0;
	bm[16]=0; bm[17]=0; bm[18]=0; bm[19]=0;
	bm[20]=0; bm[21]=0; bm[22]=0; bm[23]=0;
	bm[24]=0; bm[25]=0; bm[26]=0; bm[27]=0;
	bm[28]=1; bm[29]=1; bm[30]=0; bm[31]=0;
	bm[32]=0; bm[33]=0; bm[34]=0; bm[35]=0;
	bm[36]=0; bm[37]=0; bm[38]=0; bm[39]=0;
	bm[40]=1; bm[41]=0; bm[42]=0; bm[43]=0;
	bm[44]=1; bm[45]=0; bm[46]=0; bm[47]=0;
	bm[48]=0; bm[49]=0; bm[50]=0; bm[51]=0;
	bm[52]=0; bm[53]=0; bm[54]=0; bm[55]=0;
	bm[56]=0; bm[57]=0; bm[58]=0; bm[59]=0;
	bm[60]=1; bm[61]=1; bm[62]=0; bm[63]=0;
}

static void bricks_LoadFig003(uint8_t *bm)
{
	/*

		 #
		#
			 */
	bm[0]=0; bm[1]=0; bm[2]=0; bm[3]=0;
	bm[4]=0; bm[5]=0; bm[6]=0; bm[7]=0;
	bm[8]=0; bm[9]=1; bm[10]=0; bm[11]=0;
	bm[12]=1; bm[13]=0; bm[14]=0; bm[15]=0;
	bm[16]=0; bm[17]=0; bm[18]=0; bm[19]=0;
	bm[20]=0; bm[21]=0; bm[22]=0; bm[23]=0;
	bm[24]=1; bm[25]=0; bm[26]=0; bm[27]=0;
	bm[28]=0; bm[29]=1; bm[30]=0; bm[31]=0;
	bm[32]=0; bm[33]=0; bm[34]=0; bm[35]=0;
	bm[36]=0; bm[37]=0; bm[38]=0; bm[39]=0;
	bm[40]=0; bm[41]=1; bm[42]=0; bm[43]=0;
	bm[44]=1; bm[45]=0; bm[46]=0; bm[47]=0;
	bm[48]=0; bm[49]=0; bm[50]=0; bm[51]=0;
	bm[52]=0; bm[53]=0; bm[54]=0; bm[55]=0;
	bm[56]=1; bm[57]=0; bm[58]=0; bm[59]=0;
	bm[60]=0; bm[61]=1; bm[62]=0; bm[63]=0;
}


static void bricks_LoadFig004(uint8_t *bm)
{
	/*
		#
		#
		##
		 */
	bm[0]=0; bm[1]=0; bm[2]=0; bm[3]=0;
	bm[4]=1; bm[5]=0; bm[6]=0; bm[7]=0;
	bm[8]=1; bm[9]=0; bm[10]=0; bm[11]=0;
	bm[12]=1; bm[13]=1; bm[14]=0; bm[15]=0;
	bm[16]=0; bm[17]=0; bm[18]=0; bm[19]=0;
	bm[20]=0; bm[21]=0; bm[22]=0; bm[23]=0;
	bm[24]=0; bm[25]=0; bm[26]=1; bm[27]=0;
	bm[28]=1; bm[29]=1; bm[30]=1; bm[31]=0;
	bm[32]=0; bm[33]=0; bm[34]=0; bm[35]=0;
	bm[36]=1; bm[37]=1; bm[38]=0; bm[39]=0;
	bm[40]=0; bm[41]=1; bm[42]=0; bm[43]=0;
	bm[44]=0; bm[45]=1; bm[46]=0; bm[47]=0;
	bm[48]=0; bm[49]=0; bm[50]=0; bm[51]=0;
	bm[52]=0; bm[53]=0; bm[54]=0; bm[55]=0;
	bm[56]=1; bm[57]=1; bm[58]=1; bm[59]=0;
	bm[60]=1; bm[61]=0; bm[62]=0; bm[63]=0;
}

static void bricks_LoadFig005(uint8_t *bm)
{
	/*
		 #
		 #
		##
			 */
	bm[0]=0; bm[1]=0; bm[2]=0; bm[3]=0;
	bm[4]=0; bm[5]=1; bm[6]=0; bm[7]=0;
	bm[8]=0; bm[9]=1; bm[10]=0; bm[11]=0;
	bm[12]=1; bm[13]=1; bm[14]=0; bm[15]=0;
	bm[16]=0; bm[17]=0; bm[18]=0; bm[19]=0;
	bm[20]=0; bm[21]=0; bm[22]=0; bm[23]=0;
	bm[24]=1; bm[25]=1; bm[26]=1; bm[27]=0;
	bm[28]=0; bm[29]=0; bm[30]=1; bm[31]=0;
	bm[32]=0; bm[33]=0; bm[34]=0; bm[35]=0;
	bm[36]=1; bm[37]=1; bm[38]=0; bm[39]=0;
	bm[40]=1; bm[41]=0; bm[42]=0; bm[43]=0;
	bm[44]=1; bm[45]=0; bm[46]=0; bm[47]=0;
	bm[48]=0; bm[49]=0; bm[50]=0; bm[51]=0;
	bm[52]=0; bm[53]=0; bm[54]=0; bm[55]=0;
	bm[56]=1; bm[57]=0; bm[58]=0; bm[59]=0;
	bm[60]=1; bm[61]=1; bm[62]=1; bm[63]=0;
}

static void bricks_LoadFig006(uint8_t *bm)
{
	/*
		 #
		##
		 #
			 */
	bm[0]=0; bm[1]=0; bm[2]=0; bm[3]=0;
	bm[4]=0; bm[5]=1; bm[6]=0; bm[7]=0;
	bm[8]=1; bm[9]=1; bm[10]=0; bm[11]=0;
	bm[12]=0; bm[13]=1; bm[14]=0; bm[15]=0;
	bm[16]=0; bm[17]=0; bm[18]=0; bm[19]=0;
	bm[20]=0; bm[21]=0; bm[22]=0; bm[23]=0;
	bm[24]=1; bm[25]=1; bm[26]=1; bm[27]=0;
	bm[28]=0; bm[29]=1; bm[30]=0; bm[31]=0;
	bm[32]=0; bm[33]=0; bm[34]=0; bm[35]=0;
	bm[36]=1; bm[37]=0; bm[38]=0; bm[39]=0;
	bm[40]=1; bm[41]=1; bm[42]=0; bm[43]=0;
	bm[44]=1; bm[45]=0; bm[46]=0; bm[47]=0;
	bm[48]=0; bm[49]=0; bm[50]=0; bm[51]=0;
	bm[52]=0; bm[53]=0; bm[54]=0; bm[55]=0;
	bm[56]=0; bm[57]=1; bm[58]=0; bm[59]=0;
	bm[60]=1; bm[61]=1; bm[62]=1; bm[63]=0;
}

static void bricks_LoadFig007(uint8_t *bm)
{
	/*	#
		#
		#
		#
			 */
	bm[0]=1; bm[1]=0; bm[2]=0; bm[3]=0;
	bm[4]=1; bm[5]=0; bm[6]=0; bm[7]=0;
	bm[8]=1; bm[9]=0; bm[10]=0; bm[11]=0;
	bm[12]=1; bm[13]=0; bm[14]=0; bm[15]=0;
	bm[16]=0; bm[17]=0; bm[18]=0; bm[19]=0;
	bm[20]=0; bm[21]=0; bm[22]=0; bm[23]=0;
	bm[24]=0; bm[25]=0; bm[26]=0; bm[27]=0;
	bm[28]=1; bm[29]=1; bm[30]=1; bm[31]=1;
	bm[32]=1; bm[33]=0; bm[34]=0; bm[35]=0;
	bm[36]=1; bm[37]=0; bm[38]=0; bm[39]=0;
	bm[40]=1; bm[41]=0; bm[42]=0; bm[43]=0;
	bm[44]=1; bm[45]=0; bm[46]=0; bm[47]=0;
	bm[48]=0; bm[49]=0; bm[50]=0; bm[51]=0;
	bm[52]=0; bm[53]=0; bm[54]=0; bm[55]=0;
	bm[56]=0; bm[57]=0; bm[58]=0; bm[59]=0;
	bm[60]=1; bm[61]=1; bm[62]=1; bm[63]=1;
}

static void bricks_LoadFig008(uint8_t *bm)
{
	/*

		##
		##
			 */
	bm[0]=0; bm[1]=0; bm[2]=0; bm[3]=0;
	bm[4]=0; bm[5]=0; bm[6]=0; bm[7]=0;
	bm[8]=1; bm[9]=1; bm[10]=0; bm[11]=0;
	bm[12]=1; bm[13]=1; bm[14]=0; bm[15]=0;
	bm[16]=0; bm[17]=0; bm[18]=0; bm[19]=0;
	bm[20]=0; bm[21]=0; bm[22]=0; bm[23]=0;
	bm[24]=1; bm[25]=1; bm[26]=0; bm[27]=0;
	bm[28]=1; bm[29]=1; bm[30]=0; bm[31]=0;
	bm[32]=0; bm[33]=0; bm[34]=0; bm[35]=0;
	bm[36]=0; bm[37]=0; bm[38]=0; bm[39]=0;
	bm[40]=1; bm[41]=1; bm[42]=0; bm[43]=0;
	bm[44]=1; bm[45]=1; bm[46]=0; bm[47]=0;
	bm[48]=0; bm[49]=0; bm[50]=0; bm[51]=0;
	bm[52]=0; bm[53]=0; bm[54]=0; bm[55]=0;
	bm[56]=1; bm[57]=1; bm[58]=0; bm[59]=0;
	bm[60]=1; bm[61]=1; bm[62]=0; bm[63]=0;
}

static void bricks_LoadFig009(uint8_t *bm)
{
	/*
		#
		##
		 #
			 */
	bm[0]=0; bm[1]=0; bm[2]=0; bm[3]=0;
	bm[4]=1; bm[5]=0; bm[6]=0; bm[7]=0;
	bm[8]=1; bm[9]=1; bm[10]=0; bm[11]=0;
	bm[12]=0; bm[13]=1; bm[14]=0; bm[15]=0;
	bm[16]=0; bm[17]=0; bm[18]=0; bm[19]=0;
	bm[20]=0; bm[21]=0; bm[22]=0; bm[23]=0;
	bm[24]=0; bm[25]=1; bm[26]=1; bm[27]=0;
	bm[28]=1; bm[29]=1; bm[30]=0; bm[31]=0;
	bm[32]=0; bm[33]=0; bm[34]=0; bm[35]=0;
	bm[36]=1; bm[37]=0; bm[38]=0; bm[39]=0;
	bm[40]=1; bm[41]=1; bm[42]=0; bm[43]=0;
	bm[44]=0; bm[45]=1; bm[46]=0; bm[47]=0;
	bm[48]=0; bm[49]=0; bm[50]=0; bm[51]=0;
	bm[52]=0; bm[53]=0; bm[54]=0; bm[55]=0;
	bm[56]=0; bm[57]=1; bm[58]=1; bm[59]=0;
	bm[60]=1; bm[61]=1; bm[62]=0; bm[63]=0;
}

static void bricks_LoadFig010(uint8_t *bm)
{
	/*
		 #
		##
		#
			 */
	bm[0]=0; bm[1]=0; bm[2]=0; bm[3]=0;
	bm[4]=0; bm[5]=1; bm[6]=0; bm[7]=0;
	bm[8]=1; bm[9]=1; bm[10]=0; bm[11]=0;
	bm[12]=1; bm[13]=0; bm[14]=0; bm[15]=0;
	bm[16]=0; bm[17]=0; bm[18]=0; bm[19]=0;
	bm[20]=0; bm[21]=0; bm[22]=0; bm[23]=0;
	bm[24]=1; bm[25]=1; bm[26]=0; bm[27]=0;
	bm[28]=0; bm[29]=1; bm[30]=1; bm[31]=0;
	bm[32]=0; bm[33]=0; bm[34]=0; bm[35]=0;
	bm[36]=0; bm[37]=1; bm[38]=0; bm[39]=0;
	bm[40]=1; bm[41]=1; bm[42]=0; bm[43]=0;
	bm[44]=1; bm[45]=0; bm[46]=0; bm[47]=0;
	bm[48]=0; bm[49]=0; bm[50]=0; bm[51]=0;
	bm[52]=0; bm[53]=0; bm[54]=0; bm[55]=0;
	bm[56]=1; bm[57]=1; bm[58]=0; bm[59]=0;
	bm[60]=0; bm[61]=1; bm[62]=1; bm[63]=0;
}

static void bricks_LoadFig011(uint8_t *bm)
{
	/*
		 #
		###
		 #
			 */
	bm[0]=0; bm[1]=0; bm[2]=0; bm[3]=0;
	bm[4]=0; bm[5]=1; bm[6]=0; bm[7]=0;
	bm[8]=1; bm[9]=1; bm[10]=1; bm[11]=0;
	bm[12]=0; bm[13]=1; bm[14]=0; bm[15]=0;
	bm[16]=0; bm[17]=0; bm[18]=0; bm[19]=0;
	bm[20]=0; bm[21]=1; bm[22]=0; bm[23]=0;
	bm[24]=1; bm[25]=1; bm[26]=1; bm[27]=0;
	bm[28]=0; bm[29]=1; bm[30]=0; bm[31]=0;
	bm[32]=0; bm[33]=0; bm[34]=0; bm[35]=0;
	bm[36]=0; bm[37]=1; bm[38]=0; bm[39]=0;
	bm[40]=1; bm[41]=1; bm[42]=1; bm[43]=0;
	bm[44]=0; bm[45]=1; bm[46]=0; bm[47]=0;
	bm[48]=0; bm[49]=0; bm[50]=0; bm[51]=0;
	bm[52]=0; bm[53]=1; bm[54]=0; bm[55]=0;
	bm[56]=1; bm[57]=1; bm[58]=1; bm[59]=0;
	bm[60]=0; bm[61]=1; bm[62]=0; bm[63]=0;
}

static void bricks_LoadFig012(uint8_t *bm)
{
	/*
		###
		 #
		 #
			 */
	bm[0]=0; bm[1]=0; bm[2]=0; bm[3]=0;
	bm[4]=1; bm[5]=1; bm[6]=1; bm[7]=0;
	bm[8]=0; bm[9]=1; bm[10]=0; bm[11]=0;
	bm[12]=0; bm[13]=1; bm[14]=0; bm[15]=0;
	bm[16]=0; bm[17]=0; bm[18]=0; bm[19]=0;
	bm[20]=1; bm[21]=0; bm[22]=0; bm[23]=0;
	bm[24]=1; bm[25]=1; bm[26]=1; bm[27]=0;
	bm[28]=1; bm[29]=0; bm[30]=0; bm[31]=0;
	bm[32]=0; bm[33]=0; bm[34]=0; bm[35]=0;
	bm[36]=0; bm[37]=1; bm[38]=0; bm[39]=0;
	bm[40]=0; bm[41]=1; bm[42]=0; bm[43]=0;
	bm[44]=1; bm[45]=1; bm[46]=1; bm[47]=0;
	bm[48]=0; bm[49]=0; bm[50]=0; bm[51]=0;
	bm[52]=0; bm[53]=0; bm[54]=1; bm[55]=0;
	bm[56]=1; bm[57]=1; bm[58]=1; bm[59]=0;
	bm[60]=0; bm[61]=0; bm[62]=1; bm[63]=0;
}

static void bricks_LoadFig013(uint8_t *bm)
{
	/*
		 ##
		 #
		##
			 */
	bm[0]=0; bm[1]=0; bm[2]=0; bm[3]=0;
	bm[4]=0; bm[5]=1; bm[6]=1; bm[7]=0;
	bm[8]=0; bm[9]=1; bm[10]=0; bm[11]=0;
	bm[12]=1; bm[13]=1; bm[14]=0; bm[15]=0;
	bm[16]=0; bm[17]=0; bm[18]=0; bm[19]=0;
	bm[20]=1; bm[21]=0; bm[22]=0; bm[23]=0;
	bm[24]=1; bm[25]=1; bm[26]=1; bm[27]=0;
	bm[28]=0; bm[29]=0; bm[30]=1; bm[31]=0;
	bm[32]=0; bm[33]=0; bm[34]=0; bm[35]=0;
	bm[36]=0; bm[37]=1; bm[38]=1; bm[39]=0;
	bm[40]=0; bm[41]=1; bm[42]=0; bm[43]=0;
	bm[44]=1; bm[45]=1; bm[46]=0; bm[47]=0;
	bm[48]=0; bm[49]=0; bm[50]=0; bm[51]=0;
	bm[52]=0; bm[53]=0; bm[54]=1; bm[55]=0;
	bm[56]=1; bm[57]=1; bm[58]=1; bm[59]=0;
	bm[60]=1; bm[61]=0; bm[62]=0; bm[63]=0;
}

static void bricks_LoadFig014(uint8_t *bm)
{
	/*
		##
		 #
		 ##
			 */
	bm[0]=0; bm[1]=0; bm[2]=0; bm[3]=0;
	bm[4]=1; bm[5]=1; bm[6]=0; bm[7]=0;
	bm[8]=0; bm[9]=1; bm[10]=0; bm[11]=0;
	bm[12]=0; bm[13]=1; bm[14]=1; bm[15]=0;
	bm[16]=0; bm[17]=0; bm[18]=0; bm[19]=0;
	bm[20]=0; bm[21]=0; bm[22]=1; bm[23]=0;
	bm[24]=1; bm[25]=1; bm[26]=1; bm[27]=0;
	bm[28]=1; bm[29]=0; bm[30]=0; bm[31]=0;
	bm[32]=0; bm[33]=0; bm[34]=0; bm[35]=0;
	bm[36]=1; bm[37]=1; bm[38]=0; bm[39]=0;
	bm[40]=0; bm[41]=1; bm[42]=0; bm[43]=0;
	bm[44]=0; bm[45]=1; bm[46]=1; bm[47]=0;
	bm[48]=0; bm[49]=0; bm[50]=0; bm[51]=0;
	bm[52]=0; bm[53]=0; bm[54]=1; bm[55]=0;
	bm[56]=1; bm[57]=1; bm[58]=1; bm[59]=0;
	bm[60]=1; bm[61]=0; bm[62]=0; bm[63]=0;
}

static void bricks_LoadFig015(uint8_t *bm)
{
	/*
		###
		 #
		###
			 */
	bm[0]=0; bm[1]=0; bm[2]=0; bm[3]=0;
	bm[4]=1; bm[5]=1; bm[6]=1; bm[7]=0;
	bm[8]=0; bm[9]=1; bm[10]=0; bm[11]=0;
	bm[12]=1; bm[13]=1; bm[14]=1; bm[15]=0;
	bm[16]=0; bm[17]=0; bm[18]=0; bm[19]=0;
	bm[20]=1; bm[21]=0; bm[22]=1; bm[23]=0;
	bm[24]=1; bm[25]=1; bm[26]=1; bm[27]=0;
	bm[28]=1; bm[29]=0; bm[30]=1; bm[31]=0;
	bm[32]=0; bm[33]=0; bm[34]=0; bm[35]=0;
	bm[36]=1; bm[37]=1; bm[38]=1; bm[39]=0;
	bm[40]=0; bm[41]=1; bm[42]=0; bm[43]=0;
	bm[44]=1; bm[45]=1; bm[46]=1; bm[47]=0;
	bm[48]=0; bm[49]=0; bm[50]=0; bm[51]=0;
	bm[52]=1; bm[53]=0; bm[54]=1; bm[55]=0;
	bm[56]=1; bm[57]=1; bm[58]=1; bm[59]=0;
	bm[60]=1; bm[61]=0; bm[62]=1; bm[63]=0;
}

static void bricks_LoadFig016(uint8_t *bm)
{
	/*
		###
		###
		###
			 */
	bm[0]=0; bm[1]=0; bm[2]=0; bm[3]=0;
	bm[4]=1; bm[5]=1; bm[6]=1; bm[7]=0;
	bm[8]=1; bm[9]=1; bm[10]=1; bm[11]=0;
	bm[12]=1; bm[13]=1; bm[14]=1; bm[15]=0;
	bm[16]=0; bm[17]=0; bm[18]=0; bm[19]=0;
	bm[20]=1; bm[21]=1; bm[22]=1; bm[23]=0;
	bm[24]=1; bm[25]=1; bm[26]=1; bm[27]=0;
	bm[28]=1; bm[29]=1; bm[30]=1; bm[31]=0;
	bm[32]=0; bm[33]=0; bm[34]=0; bm[35]=0;
	bm[36]=1; bm[37]=1; bm[38]=1; bm[39]=0;
	bm[40]=1; bm[41]=1; bm[42]=1; bm[43]=0;
	bm[44]=1; bm[45]=1; bm[46]=1; bm[47]=0;
	bm[48]=0; bm[49]=0; bm[50]=0; bm[51]=0;
	bm[52]=1; bm[53]=1; bm[54]=1; bm[55]=0;
	bm[56]=1; bm[57]=1; bm[58]=1; bm[59]=0;
	bm[60]=1; bm[61]=1; bm[62]=1; bm[63]=0;
}

static void bricks_LoadFig017(uint8_t *bm)
{
	/*
		#
		#
		###
			 */
	bm[0]=0; bm[1]=0; bm[2]=0; bm[3]=0;
	bm[4]=1; bm[5]=0; bm[6]=0; bm[7]=0;
	bm[8]=1; bm[9]=0; bm[10]=0; bm[11]=0;
	bm[12]=1; bm[13]=1; bm[14]=1; bm[15]=0;
	bm[16]=0; bm[17]=0; bm[18]=0; bm[19]=0;
	bm[20]=0; bm[21]=0; bm[22]=1; bm[23]=0;
	bm[24]=0; bm[25]=0; bm[26]=1; bm[27]=0;
	bm[28]=1; bm[29]=1; bm[30]=1; bm[31]=0;
	bm[32]=0; bm[33]=0; bm[34]=0; bm[35]=0;
	bm[36]=1; bm[37]=1; bm[38]=1; bm[39]=0;
	bm[40]=0; bm[41]=0; bm[42]=1; bm[43]=0;
	bm[44]=0; bm[45]=0; bm[46]=1; bm[47]=0;
	bm[48]=0; bm[49]=0; bm[50]=0; bm[51]=0;
	bm[52]=1; bm[53]=1; bm[54]=1; bm[55]=0;
	bm[56]=1; bm[57]=0; bm[58]=0; bm[59]=0;
	bm[60]=1; bm[61]=0; bm[62]=0; bm[63]=0;
}

static void bricks_LoadFig018(uint8_t *bm)
{
	/*

		# #
		###
			 */
	bm[0]=0; bm[1]=0; bm[2]=0; bm[3]=0;
	bm[4]=0; bm[5]=0; bm[6]=0; bm[7]=0;
	bm[8]=1; bm[9]=0; bm[10]=1; bm[11]=0;
	bm[12]=1; bm[13]=1; bm[14]=1; bm[15]=0;
	bm[16]=0; bm[17]=0; bm[18]=0; bm[19]=0;
	bm[20]=1; bm[21]=1; bm[22]=0; bm[23]=0;
	bm[24]=0; bm[25]=1; bm[26]=0; bm[27]=0;
	bm[28]=1; bm[29]=1; bm[30]=0; bm[31]=0;
	bm[32]=0; bm[33]=0; bm[34]=0; bm[35]=0;
	bm[36]=0; bm[37]=0; bm[38]=0; bm[39]=0;
	bm[40]=1; bm[41]=1; bm[42]=1; bm[43]=0;
	bm[44]=1; bm[45]=0; bm[46]=1; bm[47]=0;
	bm[48]=0; bm[49]=0; bm[50]=0; bm[51]=0;
	bm[52]=1; bm[53]=1; bm[54]=0; bm[55]=0;
	bm[56]=1; bm[57]=0; bm[58]=0; bm[59]=0;
	bm[60]=1; bm[61]=1; bm[62]=0; bm[63]=0;
}

static void bricks_LoadFig019(uint8_t *bm)
{
	/*

		###
		###
			 */
	bm[0]=0; bm[1]=0; bm[2]=0; bm[3]=0;
	bm[4]=0; bm[5]=0; bm[6]=0; bm[7]=0;
	bm[8]=1; bm[9]=1; bm[10]=1; bm[11]=0;
	bm[12]=1; bm[13]=1; bm[14]=1; bm[15]=0;
	bm[16]=0; bm[17]=0; bm[18]=0; bm[19]=0;
	bm[20]=1; bm[21]=1; bm[22]=0; bm[23]=0;
	bm[24]=1; bm[25]=1; bm[26]=0; bm[27]=0;
	bm[28]=1; bm[29]=1; bm[30]=0; bm[31]=0;
	bm[32]=0; bm[33]=0; bm[34]=0; bm[35]=0;
	bm[36]=0; bm[37]=0; bm[38]=0; bm[39]=0;
	bm[40]=1; bm[41]=1; bm[42]=1; bm[43]=0;
	bm[44]=1; bm[45]=1; bm[46]=1; bm[47]=0;
	bm[48]=0; bm[49]=0; bm[50]=0; bm[51]=0;
	bm[52]=1; bm[53]=1; bm[54]=0; bm[55]=0;
	bm[56]=1; bm[57]=1; bm[58]=0; bm[59]=0;
	bm[60]=1; bm[61]=1; bm[62]=0; bm[63]=0;
}

/*static void bricks_LoadFig020(uint8_t *bm){*/
	/*	####
		####
		####
		####
			 */
	/*bm[0]=1; bm[1]=1; bm[2]=1; bm[3]=1;
	bm[4]=1; bm[5]=1; bm[6]=1; bm[7]=1;
	bm[8]=1; bm[9]=1; bm[10]=1; bm[11]=1;
	bm[12]=1; bm[13]=1; bm[14]=1; bm[15]=1;
	bm[16]=1; bm[17]=1; bm[18]=1; bm[19]=1;
	bm[20]=1; bm[21]=1; bm[22]=1; bm[23]=1;
	bm[24]=1; bm[25]=1; bm[26]=1; bm[27]=1;
	bm[28]=1; bm[29]=1; bm[30]=1; bm[31]=1;
	bm[32]=1; bm[33]=1; bm[34]=1; bm[35]=1;
	bm[36]=1; bm[37]=1; bm[38]=1; bm[39]=1;
	bm[40]=1; bm[41]=1; bm[42]=1; bm[43]=1;
	bm[44]=1; bm[45]=1; bm[46]=1; bm[47]=1;
	bm[48]=1; bm[49]=1; bm[50]=1; bm[51]=1;
	bm[52]=1; bm[53]=1; bm[54]=1; bm[55]=1;
	bm[56]=1; bm[57]=1; bm[58]=1; bm[59]=1;
	bm[60]=1; bm[61]=1; bm[62]=1; bm[63]=1;
}*/


void bricks_LoadBlock(uint8_t mode,uint8_t *bm)
{
	uint8_t n;
	if (mode==0)
	{//Very simple bricks
		n=v_rnd%4;
		if (n==0)
		{
			bricks_LoadFig000(bm); return;
		};
		if (n==1)
		{
			bricks_LoadFig001(bm); return;
		};
		if (n==2)
		{
			bricks_LoadFig002(bm); return;
		};
		if (n==3)
		{
			bricks_LoadFig003(bm); v_rnd++; return;
		};
	};
	if (mode==1)
	{//Classic bricks
		n=v_rnd%7;
		if (n==0)
		{
			bricks_LoadFig004(bm); return;
		};
		if (n==1)
		{
			bricks_LoadFig005(bm); v_rnd++; return;
		};
		if (n==2)
		{
			bricks_LoadFig006(bm); return;
		};
		if (n==3)
		{
			bricks_LoadFig007(bm); return;
		};
		if (n==4)
		{
			bricks_LoadFig008(bm); return;
		};
		if (n==5)
		{
			bricks_LoadFig009(bm); v_rnd++; return;
		};
		if (n==6)
		{
			bricks_LoadFig010(bm); return;
		};
	};
	if (mode==2)
	{//Hard bricks
		n=v_rnd%20;
		if (n==0)
		{
			bricks_LoadFig000(bm); return;
		};
		if (n==1)
		{
			bricks_LoadFig001(bm); v_rnd++; return;
		};
		if (n==2)
		{
			bricks_LoadFig002(bm); return;
		};
		if (n==3)
		{
			bricks_LoadFig003(bm); return;
		};
		if (n==4)
		{
			bricks_LoadFig004(bm); v_rnd++; return;
		};
		if (n==5)
		{
			bricks_LoadFig005(bm); return;
		};
		if (n==6)
		{
			bricks_LoadFig006(bm); return;
		};
		if (n==7)
		{
			bricks_LoadFig007(bm); return;
		};
		if (n==8)
		{
			bricks_LoadFig008(bm); return;
		};
		if (n==9)
		{
			bricks_LoadFig009(bm); v_rnd++; return;
		};
		if (n==10)
		{
			bricks_LoadFig010(bm); return;
		};
		if (n==11)
		{
			bricks_LoadFig011(bm); return;
 		};
		if (n==12)
		{
			bricks_LoadFig012(bm); return;
		};
		if (n==13)
		{
			bricks_LoadFig013(bm); return;
		};
		if (n==14)
		{
			bricks_LoadFig014(bm); return;
 		};
		if (n==15)
		{
			bricks_LoadFig015(bm); return;
		};
		if (n==16)
		{
			bricks_LoadFig016(bm); return;
		};
		if (n==17)
		{
			bricks_LoadFig017(bm); v_rnd++; return;
		};
		if (n==18)
		{
			bricks_LoadFig018(bm); return;
		};
		if (n==19)
		{
			bricks_LoadFig019(bm); return;
		};
	};
}

void bricks_DrawBlock(int8_t x, int8_t y, uint8_t r, uint8_t *bm)
{
	int8_t tx=x;
	
	r*=16;
	if (bm[r++]) g_SetPixel(tx,y);
	tx++; if (bm[r++]) g_SetPixel(tx,y);
	tx++; if (bm[r++]) g_SetPixel(tx,y);
	tx++; if (bm[r++]) g_SetPixel(tx,y);
	
	tx=x; y++;
	if (bm[r++]) g_SetPixel(tx,y);
	tx++; if (bm[r++]) g_SetPixel(tx,y);
	tx++; if (bm[r++]) g_SetPixel(tx,y);
	tx++; if (bm[r++]) g_SetPixel(tx,y);
	
	tx=x; y++;
	if (bm[r++]) g_SetPixel(tx,y);
	tx++; if (bm[r++]) g_SetPixel(tx,y);
	tx++; if (bm[r++]) g_SetPixel(tx,y);
	tx++; if (bm[r++]) g_SetPixel(tx,y);
	
	tx=x; y++;
	if (bm[r++]) g_SetPixel(tx,y);
	tx++; if (bm[r++]) g_SetPixel(tx,y);
	tx++; if (bm[r++]) g_SetPixel(tx,y);
	tx++; if (bm[r]) g_SetPixel(tx,y);
}

void bricks_DrawBox(uint8_t *boxm)
{
	uint8_t i,j,n=0;
	for (j=0;j<gd_YSize;j++)
	{
		for (i=0;i<gd_XSize;i++)
		{
			if (boxm[n]) g_SetPixel(i,j);
			n++;
		};
	};
}

uint8_t bricks_CheckBlock(int8_t x, int8_t y, uint8_t r, uint8_t *bm,uint8_t *boxm)
{
	uint8_t n,k,w=0,s;
	if (y<-3) return 1;
	r*=16;

	k=r;
	s=0; if (bm[k++]) s=1; if (bm[k++]) s=2; if (bm[k++]) s=3; if (bm[k++]) s=4; if (s>w) w=s;
	s=0; if (bm[k++]) s=1; if (bm[k++]) s=2; if (bm[k++]) s=3; if (bm[k++]) s=4; if (s>w) w=s;
	s=0; if (bm[k++]) s=1; if (bm[k++]) s=2; if (bm[k++]) s=3; if (bm[k++]) s=4; if (s>w) w=s;
	s=0; if (bm[k++]) s=1; if (bm[k++]) s=2; if (bm[k++]) s=3; if (bm[k++]) s=4; if (s>w) w=s;

	if (s>w) w=s;

	if ((x+w-1)>gd_XSizeM1) return 2;

	if (y>-1)
	{
		n=gd_XSize*y+x;
		if ((bm[r++]>0)&(boxm[n++]>0)) return 1;
		if ((bm[r++]>0)&(boxm[n++]>0)) return 1;
		if ((bm[r++]>0)&(boxm[n++]>0)) return 1;
		if ((bm[r++]>0)&(boxm[n]>0)) return 1;
		} else {
		r+=4;
	};
	
	if (y>-2)
	{
		y++; n=gd_XSize*y+x;
		if ((bm[r++]>0)&(boxm[n++]>0)) return 1;
		if ((bm[r++]>0)&(boxm[n++]>0)) return 1;
		if ((bm[r++]>0)&(boxm[n++]>0)) return 1;
		if ((bm[r++]>0)&(boxm[n]>0)) return 1;
	}
	else
	{
		r+=4;
	};
	
	if (y>-3)
	{
		y++; if (y<0) y=0;
		n=gd_XSize*y+x;
		if ((bm[r++]>0)&(boxm[n++]>0)) return 1;
		if ((bm[r++]>0)&(boxm[n++]>0)) return 1;
		if ((bm[r++]>0)&(boxm[n++]>0)) return 1;
		if ((bm[r++]>0)&(boxm[n]>0)) return 1;
	}
	else
	{
		r+=4;
	};
	
	y++; if (y<0) y=0;
	n=gd_XSize*y+x;
	if ((bm[r++]>0)&(boxm[n++]>0)) return 1;
	if ((bm[r++]>0)&(boxm[n++]>0)) return 1;
	if ((bm[r++]>0)&(boxm[n++]>0)) return 1;
	if ((bm[r++]>0)&(boxm[n]>0)) return 1;
	
	return 0;
}

void bricks_DeleteLine(int8_t y, uint8_t *boxm)
{
	uint8_t i,j,n,k;
	
	if (y>0)
	{
		k=y-1;
		for (j=0;j<k;j++)
		{
			n=(y-j-1)*gd_XSize;
			for (i=0;i<gd_XSize;i++)
			{
				boxm[n+gd_XSize+i]=boxm[n+i];
			};
		};
	};
	
	for (i=0;i<gd_XSize;i++)
	{
		boxm[i]=0;
	};
}

void bricks_LineAnimation(uint8_t *dir, int8_t y)
{
	uint8_t i;
	if (dir[0])
	{
		for (i=0;i<gd_XSize;i++)
		{
			g_ClearPixel(i,y); g_Update();
			delay_ms(30);
		};
		dir[0]=0;
	}
	else
	{
		for (i=0;i<gd_XSize;i++)
		{
			g_ClearPixel(gd_XSizeM1-i,y); g_Update();
			delay_ms(30);
		};
		dir[0]=1;
	};
}

uint8_t bricks_DeleteLines(uint8_t *dir,uint8_t *boxm)
{
	uint8_t i,j,n,k,yt,delnum=0,end=1;
	while (end>0)
	{
		end=0;
		for (j=0;j<gd_YSize;j++)
		{
			k=0;
			yt=gd_YSizeM1-j;
			n=yt*gd_XSize;
			
			for (i=0;i<gd_XSize;i++)
			{
				if (boxm[n++]) k++;
			};
			
			if (k==gd_XSize)
			{
				bricks_LineAnimation(dir,yt);
				bricks_DeleteLine(yt,boxm);
				g_Clear(); bricks_DrawBox(boxm); g_Update();
				delay_ms(30);
				delnum++; end=1;
				v_GamePoints++; UpdateGamePoints();
				break;
			};
		};
	};
	return delnum;
}

void bricks_Connect(int8_t x, int8_t y, uint8_t r, uint8_t *bm, uint8_t *boxm)
{
	int8_t n=gd_XSize*y+x;
	r*=16;
	
	if (bm[r++]>0) boxm[n]=1;
	n++; if (bm[r++]>0) boxm[n]=1;
	n++; if (bm[r++]>0) boxm[n]=1;
	n++; if (bm[r++]>0) boxm[n]=1;
	
	y++; n=gd_XSize*y+x;
	if (bm[r++]>0) boxm[n]=1;
	n++; if (bm[r++]>0) boxm[n]=1;
	n++; if (bm[r++]>0) boxm[n]=1;
	n++; if (bm[r++]>0) boxm[n]=1;
	
	y++; n=gd_XSize*y+x;
	if (bm[r++]>0) boxm[n]=1;
	n++; if (bm[r++]>0) boxm[n]=1;
	n++; if (bm[r++]>0) boxm[n]=1;
	n++; if (bm[r++]>0) boxm[n]=1;
	
	y++; n=gd_XSize*y+x;
	if (bm[r++]>0) boxm[n]=1;
	n++; if (bm[r++]>0) boxm[n]=1;
	n++; if (bm[r++]>0) boxm[n]=1;
	n++; if (bm[r++]>0) boxm[n]=1;
}

uint8_t bricks_MoveDown(int8_t x, int8_t y, uint8_t r, uint8_t *bm, uint8_t *boxm){
	y++;
	if (bricks_CheckBlock(x,y,r,bm,boxm)==1) return 1;
	if ((y+3)>gd_YSizeM1) return 1;
	return 0;
}

uint8_t bricks_CheckEnd(uint8_t *boxm){
	if (boxm[3]) return 1;
	if (boxm[2]) return 1;
	if (boxm[4]) return 1;
	if (boxm[1]) return 1;
	if (boxm[5]) return 1;
	if (boxm[6]) return 1;
	if (boxm[0]) return 1;
	if (boxm[7]) return 1;
	return 0;
}

void bricks_Game(uint8_t GameMode)
{
	uint8_t tetrisv_BlockMem[64];//Current brick
	uint8_t tetrisv_BoxMem[128];//Game bricks buffer 8х16
	uint8_t r=0;//Brick rotate =0, 1, 2, 3
	int8_t x=0,y=0;//Brick position
	uint8_t v_Rotate=0;//Need rotete?
	uint8_t v_NotEnd=1;//Game continue?
	uint8_t v_Redraw=1;//Redraw?
	uint8_t dir[1];//Line delete direction
	uint16_t time_cnt=ht0_cnt;//Для отсчета времени цикла
	uint16_t time_sw=GameSpeedCount(); //Переключатель скорости

	dir[0]=0;
	pkeys_Unused=0b11000000;

	v_GamePoints=0; UpdateGamePoints();
	v_NotEnd=1; v_Redraw=1;
	ArrayFill_U8(0,128,tetrisv_BoxMem);
	g_Clear(); g_Update();
	bricks_LoadBlock(GameMode,tetrisv_BlockMem); r=0; x=3; y=-4;
	while(v_NotEnd)
	{
		wdr(); v_rnd++;

        if (pKeySwitch(0x40) == 2) 
        {
            v_NotEnd = 0; 
            continue;    
        }

		// Buttons ==================
		if (pReadKeys())
		{
			if (pKeySwitch(0x01)==2)
			{//Up
				v_Rotate=1;
				v_Redraw=1; v_rnd++;
			};
			
			if (pKeySwitch(0x02)==2)
			{//Left
				v_Redraw=1; v_rnd++;
				x--;
				if (x<0)
				{
					x++;
				}
				else
				{
					if (bricks_CheckBlock(x,y,r,tetrisv_BlockMem,tetrisv_BoxMem)>0)
					{
						x++;
					};
				};
			};
			
			if (pKeyPressed(0x04)==2)
			{//Down press
				v_Redraw=1; v_rnd++;
				time_sw=0;
			};
			
			if (pKeyPressed(0x04)==3)
			{//Down release
				v_Redraw=1; v_rnd++;
				time_sw=GameSpeedCount();
			};
			
			if (pKeySwitch(0x08)==2)
			{//Right
				v_Redraw=1; v_rnd++;
				x++;
				if (x>gd_XSizeM1)
				{
					x--;
				}
				else
				{
					if (bricks_CheckBlock(x,y,r,tetrisv_BlockMem,tetrisv_BoxMem)>0)
					{
						x--; v_rnd++;
					};
				};
			};
			if (pKeySwitch(0x10)==2)
			{//Rotate
				v_Rotate=1;
				v_Redraw=1; v_rnd++;
			};
			if (pKeySwitch(0x20)==2)
			{//Pause
				GamePause();
				v_Redraw=1; v_rnd++;
			};
		}
		else
		{
			if ((ht0_cnt-time_cnt)>time_sw)
			{
				time_cnt=ht0_cnt; v_Redraw=2; v_rnd++;
				if (bricks_MoveDown(x,y,r,tetrisv_BlockMem,tetrisv_BoxMem))
				{
					bricks_Connect(x,y,r,tetrisv_BlockMem,tetrisv_BoxMem);
					time_sw=GameSpeedCount();
					bricks_LoadBlock(GameMode,tetrisv_BlockMem); r=0; x=3; y=-4;
					if (bricks_CheckEnd(tetrisv_BoxMem))
					{
						v_NotEnd=0;
					};
				}
				else
				{
					y++;
				};
			};
		};
		//Drawings======================
		if (v_Rotate>0)
		{
			uint8_t rt=r;
			int8_t xt=x;
			r++; if (r==4) r=0;
			if (bricks_CheckBlock(x,y,r,tetrisv_BlockMem,tetrisv_BoxMem)>0)
			{
				if (x>0) x--;
				if (bricks_CheckBlock(x,y,r,tetrisv_BlockMem,tetrisv_BoxMem)>0)
				{
					if (x>0) x--;
					if (bricks_CheckBlock(x,y,r,tetrisv_BlockMem,tetrisv_BoxMem)>0)
					{
						if (x>0) x--;
						if (bricks_CheckBlock(x,y,r,tetrisv_BlockMem,tetrisv_BoxMem)>0)
						{
							x=xt; r=rt;
						};
					};
				};
			};
			v_Rotate=0;
		};

		if (v_Redraw)
		{
			g_Clear();
			bricks_DrawBox(tetrisv_BoxMem);
			bricks_DrawBlock(x,y,r,tetrisv_BlockMem);
			g_Update();
			
			if (v_Redraw==2)
			{
				if (bricks_DeleteLines(dir,tetrisv_BoxMem))
				{
					v_Redraw=1;
				}
				else
				{
				v_Redraw=0;
				};
			}
			else
			{
			v_Redraw=0;
			};
		};
	};
	RandomGameOver();
};
