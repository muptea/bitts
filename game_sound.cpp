#include <Arduino.h>
#include "game_sound.h"

#define SOUND_PIN 2

extern "C" void sound_Init(void) {
    pinMode(SOUND_PIN, OUTPUT);
    digitalWrite(SOUND_PIN, LOW);
}

void playTone(unsigned int freq, unsigned long duration_ms) {
    if (freq == 0) {
        delay(duration_ms);
        return;
    }

    // Рассчитываем период в микросекундах
    unsigned long period_us = 1000000ULL / freq;
    // Сколько циклов нужно прогнать для указанной длительности
    unsigned long cycles = (freq * duration_ms) / 1000;

    for (unsigned long i = 0; i < cycles; i++) {
        digitalWrite(SOUND_PIN, HIGH);
        delayMicroseconds(period_us / 2);
        digitalWrite(SOUND_PIN, LOW);
        delayMicroseconds(period_us / 2);
    }
}

extern "C" void sound_MenuBeep(void) {
    playTone(900, 50); 
}

extern "C" void sound_Win(void) {
    playTone(1200, 80);
    playTone(1500, 120);
}

extern "C" void sound_GameOver(void) {
    playTone(300, 200);
    playTone(150, 400);
}

extern "C" void sound_SimonTone(uint8_t note) {
    unsigned int freqs[] = {440, 523, 659, 784}; 
    if (note < 4) playTone(freqs[note], 250);
}