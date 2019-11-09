#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "Definitions.h"

class EnemySprite : public cocos2d::Sprite
{
public:
	static EnemySprite* createSprite(int);
	virtual bool init();
	void reset();
};


#endif // !__ENEMY_H__