/**************************************************************************************************
->IF YOU USE A VALUE MORE THAN ONE PLACE, YOU CAN DEFINE IT IN THIS HEADER FILE.
->THANKS TO THIS HEADER FILE...
->FIRST OF ALL, YOU DON'T HAVE TO KEEP IN MIND VALUES YOU USE.
->SECOND AND FOREMOST, IF YOU WANT TO UPDATE THE VALUE YOU GIVE, JUST UPDATE THE DEFINITION HERE.
->THIS WILL AUTOMATICALLY UPDATE THE VALUES YOU USE ON OTHER FILES.
**************************************************************************************************/
#pragma once

#define TRANSITION_TIME					0.3f					//Transition effect duration.

#define SCORE_FONT_SIZE					0.03					//Font size of score texts.
#define BULLET_SPAWN_SPEED				.5f						//Spawn speed for Bullets.

#define PLAYER_ID_TAG					1001					//Player's Tag number.
#define BULLET_ID_TAG					1002					//Bullet's Tag number.
#define ENEMY_ID_TAG					1003					//Ememy's Tag number.

#define PLAYER_TRIGGER_BITMASK			0x000001				//Player trigger bitmask value for physics contacts.
#define BULLET_TRIGGER_BITMASK			0x000002				//Bullet trigger bitmask value for physics contacts.
#define ENEMY_TRIGGER_BITMASK			0x000003				//Enemy trigger bitmask value for physics contacts.

#define ENEMY_NUMBER					15						//The value of how many enemies will be in a row.

#define PLAYER_MOVEMENT_SPEED			20.f
#define BULLET_MOVEMENT_SPEED			14.f
#define ENEMY_MOVEMENT_SPEED			.5f