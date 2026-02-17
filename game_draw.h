#ifndef _GAME_DRAW_
#define _GAME_DRAW_

#define d_AllGamesNum	8

#define gd_XSize	8
#define gd_XSizeM1	(gd_XSize-1)
#define gd_YSize	16
#define gd_YSizeM1	(gd_YSize-1)

#define gd_Bytes	gd_XSize*gd_YSize/8

#ifdef __cplusplus
extern "C" {
#endif
extern uint8_t gv_Buffer[gd_Bytes];

void g_SetPixel(int8_t x,int8_t y);
void g_ClearPixel(int8_t x,int8_t y);
void g_Clear(void);
void g_FillAll(uint8_t v);
void g_Update(void);
void RandomGameOver(void);
void UpdateGamePoints(void);
void GameMenu(void);

#ifdef __cplusplus
};
#endif

#endif
