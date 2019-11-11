#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Definitions.h"

class BulletSprite : public cocos2d::Sprite
{
public:
	static BulletSprite* createSprite(int);										//We use 'int' for give tag to sprites.
	virtual bool init();
	void reset();
};
#endif // !__BULLET_H__
