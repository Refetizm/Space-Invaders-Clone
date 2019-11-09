#include "Enemy.h"

USING_NS_CC;

EnemySprite* EnemySprite::createSprite(int captain)
{
	EnemySprite* sprite = new EnemySprite;
	if (sprite != nullptr)
	{
		sprite->setTag(captain);
		sprite->init();
	}
	return sprite;
}

bool EnemySprite::init()
{
	std::string rsrcFileName;
	if (getTag() == ENEMY_TAG)
	{
		rsrcFileName = StringUtils::format("Enemy.png");
	}
	if (!Sprite::initWithFile(rsrcFileName))
	{
		return false;
	}

	auto enemyBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	enemyBody->setContactTestBitmask(true);
	enemyBody->setCollisionBitmask(ENEMY_TRIGGER_BITMASK);
	this->setPhysicsBody(enemyBody);
	
	return true;

}

void EnemySprite::reset()
{

}