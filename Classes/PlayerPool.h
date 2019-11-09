#ifndef __PLAYER_POOL_H__
#define __PLAYER_POOL_H__

#include "Definitions.h"
#include <list>


class PlayerSprite;

class PlayerPool
{
private:
	PlayerPool(){}
public:
	static PlayerPool* getPlayer();
	PlayerSprite* getPlayerSprite(int);
	void returnPlayer(PlayerSprite*);
private:
	static PlayerPool* poolPlayer;
	std::list<PlayerSprite*> _theEnemyVec;
	std::list<PlayerSprite*> _theEbeninVec;
};
#endif // !__PLAYER_POOL_H__
