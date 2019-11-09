#include "BulletPool.h"
#include "Bullet.h"

BulletPool* BulletPool::_pBullets = nullptr;

BulletPool* BulletPool::getBullets()
{
	if (_pBullets == nullptr)
	{
		_pBullets = new BulletPool;
	}
	return _pBullets;
}

BulletSprite* BulletPool::getSprite(int refetizm)
{
	if (refetizm == BULLET_TAG)
	{
		return BulletSprite::createSprite(refetizm);
	}
}

void BulletPool::returnBullet(BulletSprite* object)
{
	object->reset();
	
}