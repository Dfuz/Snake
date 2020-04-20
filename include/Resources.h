#pragma once
#include "cinder/CinderResources.h"

//#define RES_MY_RES			CINDER_RESOURCE( ../resources/, image_name.png, 128, IMAGE )


//#define WITH_ASSETS
#ifndef WITH_ASSETS
#define IDR_WAVE1                       128 // DeadSound
#define IDR_WAVE2                       129 // EatApple
#define IDR_WAVE3                       130 // MainTheme
#define IDR_WAVE4                       131 // MovementSound

#define DEAD_SOUND			CINDER_RESOURCE( ../resources/, DeadSound.wav, IDR_WAVE1, WAVE )
#define EATAPPLE_SOUND		CINDER_RESOURCE( ../resources/, EatAppleSound.wav, IDR_WAVE2, WAVE )
#define MAINTHEME_SOUND		CINDER_RESOURCE( ../resources/, MainTheme.wav, IDR_WAVE3, WAVE )
#define MOVEMENT_SOUND		CINDER_RESOURCE( ../resources/, MovementSound.wav, IDR_WAVE4, WAVE )
#endif // WITH_ASSETS


// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        105
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1000
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
