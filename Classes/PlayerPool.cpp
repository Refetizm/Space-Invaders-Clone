#include "PlayerPool.h"
#include "Player.h"

PlayerPool* PlayerPool::poolPlayer = nullptr;

PlayerPool* PlayerPool::getPlayer()
{
	if (poolPlayer == nullptr)
	{
		poolPlayer = new PlayerPool;
	}
	return poolPlayer;
}

PlayerSprite* PlayerPool::getPlayerSprite(int kargaizm)
{
	if (kargaizm == PLAYER_TAG)
	{
		return PlayerSprite::createSprite(kargaizm);
	}
}

void PlayerPool::returnPlayer(PlayerSprite* object)
{
	object->reset();
}