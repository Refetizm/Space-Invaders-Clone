#include "PlayerPool.h"
#include "Player.h"

PlayerPool* PlayerPool::playerInstance = nullptr;								//In the begining our pool is empty.

//----------GENERATING POOL----------//
PlayerPool* PlayerPool::getPlayer()
{
	if (playerInstance == nullptr)
	{
		playerInstance = new PlayerPool;										//if the pool is empty, generate a new pool.
	}
	return playerInstance;
}

//----------GENERATING SPRITE IN THE POOL----------//
PlayerSprite* PlayerPool::getPlayerSprite(int playerIdTag)
{
	if (playerIdTag == PLAYER_ID_TAG)
	{
		return PlayerSprite::createSprite(playerIdTag);						//if the 'playerIdTag' equals to 'PLAYER_ID_TAG', generate new Player sprite in the PlayerPool.
	}
}

//----------RETURN UNUSED OBJECTS----------//
void PlayerPool::returnPlayer(PlayerSprite* playerObject)
{
	playerObject->reset();													//This function is used to return unused sprites(removed, destroyed etc.) from GameScene to the pool.
}