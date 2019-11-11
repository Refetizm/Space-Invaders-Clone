#ifndef __ENEMY_POOL_H__
#define __ENEMY_POOL_H__

#include "Definitions.h"
#include <list>

class EnemySprite;

class EnemyPool
{
private:
	EnemyPool() {}
public:
	static EnemyPool* getEnemy();
	EnemySprite* getEnemySprite(int);
	void returnEnemy(EnemySprite*);
private:
	static EnemyPool* enemyInstance;
};
#endif // !__ENEMY_POOL_H__
