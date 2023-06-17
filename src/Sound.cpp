/***********************************************************************
 * File: Sound.cpp
 * Author: Raymin (B11132009)
 * Create Date: 2023--06-14
 * Editor: Raymin (B11132009)
 * Update Date: 2023--06-14
 * Description: music for game
***********************************************************************/

#include "Sound.h"

// play BackgroundMusic
void playBackgroundMusic() {
	PlaySound(TEXT(".\\Sound\\BackgroundMusic.wav"), NULL, SND_ASYNC); // need to change the location
}

// play BattleMusic
void playBattleMusic() {
	PlaySound(TEXT(".\\Sound\\BattleMusic.wav"), NULL, SND_ASYNC); // need to change the location
}

// stop Music playing
void stopMusic() {
	PlaySound(NULL, NULL, SND_ASYNC);
}

