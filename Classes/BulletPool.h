#ifndef __BULLET_POOL_H_
#define __BULLET_POOL_H_


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
	static BulletPool* _pBullets;
	std::list<BulletSprite*> _theEnemyVec;
	std::list<BulletSprite*> _theBulletVec;
};















#endif // !__BULLET_POOL_H_
