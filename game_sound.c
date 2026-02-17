#include <Arduino.h>
#include <util/delay.h>
#include "game_sound.h"
#include "game_hw.h" 

#define SOUND_PIN 2 

void sound_Init(void) {
    pinMode(SOUND_PIN, OUTPUT);
    digitalWrite(SOUND_PIN, LOW);
}

void playTone(unsigned int freq, unsigned long duration_ms) {
    if (freq == 0) {
        unsigned long start = millis();
        while (millis() - start < duration_ms) {
        }
        return;
    }

    unsigned long period_us = 1000000UL / freq;
    unsigned long half_period = period_us / 2;
    unsigned long cycles = (freq * duration_ms) / 1000;

    for (unsigned long i = 0; i < cycles; i++) {
        digitalWrite(SOUND_PIN, HIGH);
        delayMicroseconds(half_period);
        digitalWrite(SOUND_PIN, LOW);
        delayMicroseconds(half_period);
    }
}

void sound_MenuBeep(void) {
    playTone(900, 20); 
}

void sound_Win(void) {
    playTone(1000, 100);
    delay(50);
    playTone(1500, 100);
    delay(50);
    playTone(2000, 200);
}

void sound_GameOver(void) {
    playTone(500, 200);
    playTone(250, 400);
}

void sound_SimonTone(uint8_t note) {
    unsigned int freqs[] = {261, 329, 392, 523}; 
    if (note < 4) {
        playTone(freqs[note], 300);
    } else {
        playTone(100, 500);
    }
}