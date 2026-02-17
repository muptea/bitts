#ifndef _GAME_SOUND_
#define _GAME_SOUND_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void sound_Init(void);
void sound_MenuBeep(void);
void sound_Win(void);
void sound_GameOver(void);
void sound_SimonTone(uint8_t note);

#ifdef __cplusplus
}
#endif

#endif