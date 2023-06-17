/***********************************************************************
 * File: Sound.h
 * Author: Raymin
 * Create Date: 2023/06/04
 * Editor: Raymin
 * Update Date: 2023/06/14
 * Description: header of sound.cpp
***********************************************************************/

#pragma once
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

void playBackgroundMusic();
void playBattleMusic();
void stopMusic();
