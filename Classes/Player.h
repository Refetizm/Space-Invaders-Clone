#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Definitions.h"

class PlayerSprite : public cocos2d::Sprite
{
public:
	static PlayerSprite* createSprite(int);							//We use 'int' for give tag to sprites.
	virtual bool init();
	void reset();
};
#endif // !__PLAYER_H__
