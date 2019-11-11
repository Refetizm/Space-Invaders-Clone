#include "EnemyPool.h"
#include "Enemy.h"

EnemyPool* EnemyPool::enemyInstance = nullptr;									//In the begining our pool is empty.

//----------GENERATING POOL----------//
EnemyPool* EnemyPool::getEnemy()
{
	if (enemyInstance == nullptr)
	{
		enemyInstance = new EnemyPool;											//if the pool is empty, generate a new pool.
	}
	return enemyInstance;
}

//----------GENERATING SPRITE IN THE POOL----------//
EnemySprite* EnemyPool::getEnemySprite(int enemyIdTag)
{
	if (enemyIdTag == ENEMY_ID_TAG)
	{
		return EnemySprite::createSprite(enemyIdTag);							//if the 'enemyIdTag' equals to 'ENEMY_ID_TAG', generate new Enemy sprite in the EnemyPool.
	}
}

//----------RETURN UNUSED OBJECTS----------//
void EnemyPool::returnEnemy(EnemySprite* enemyObject)
{
	enemyObject->reset();														//This function is used to return unused sprites(removed, destroyed etc.) from GameScene to the pool.
}