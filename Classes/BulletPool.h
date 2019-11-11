#ifndef __BULLET_POOL_H__
#define __BULLET_POOL_H__

#include "Definitions.h"
#include <list>

class BulletSprite;

class BulletPool
{
private:
	BulletPool(){}
public:
	static BulletPool* getBullets();
	BulletSprite* getSprite(int);
	void returnBullet(BulletSprite*);
private:
	static BulletPool* bulletInstance;
};
#endif // !__BULLET_POOL_H__
