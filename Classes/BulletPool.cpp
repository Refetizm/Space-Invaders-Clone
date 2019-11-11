#include "BulletPool.h"
#include "Bullet.h"

BulletPool* BulletPool::bulletInstance = nullptr;											//In the begining our pool is empty.

//----------GENERATING POOL----------//
BulletPool* BulletPool::getBullets()
{
	if (bulletInstance == nullptr)
	{
		bulletInstance = new BulletPool;													//if the pool is empty, generate a new pool.
	}
	return bulletInstance;
}

//----------GENERATING SPRITE IN THE POOL----------//
BulletSprite* BulletPool::getSprite(int bulletIdTag)
{
	if (bulletIdTag == BULLET_ID_TAG)
	{
		return BulletSprite::createSprite(bulletIdTag);										//if the 'bulletIdTag' equals to 'BULLET_ID_TAG', generate new Player sprite in the PlayerPool.
	}
}

//----------RETURN UNUSED OBJECTS----------//
void BulletPool::returnBullet(BulletSprite* bulletObject)
{
	bulletObject->reset();																	//This function is used to return unused sprites(removed, destroyed etc.) from GameScene to the pool.
}