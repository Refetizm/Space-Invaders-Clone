#include "EnemyPool.h"
#include "Enemy.h"

EnemyPool* EnemyPool::poolEnemy = nullptr;

EnemyPool* EnemyPool::getEnemy()
{
	if (poolEnemy == nullptr)
	{
		poolEnemy = new EnemyPool;
	}
	return poolEnemy;
}

EnemySprite* EnemyPool::getEnemySprite(int captain)
{
	if (captain == ENEMY_TAG)
	{
		return EnemySprite::createSprite(captain);
	}
}

void EnemyPool::returnEnemy(EnemySprite* object)
{
	object->reset();
}