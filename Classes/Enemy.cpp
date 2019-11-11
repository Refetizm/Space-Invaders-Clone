#include "Enemy.h"

USING_NS_CC;

EnemySprite* EnemySprite::createSprite(int enemyIdTag)
{
	EnemySprite* sprite = new EnemySprite;
	if (sprite != nullptr)
	{
		sprite->setTag(enemyIdTag);																		//We set every EnemySprite's tag.
		sprite->init();
	}
	return sprite;
}

bool EnemySprite::init()
{
	//----------ADDING ENEMY SPRITE----------//
	std::string rsrcFileName;
	if (getTag() == ENEMY_ID_TAG)
	{
		rsrcFileName = StringUtils::format("Enemy.png");												//If our tag is equal to the 'ENEMY_ID_TAG', call "Enemy.png".
	}
	if (!Sprite::initWithFile(rsrcFileName))
	{
		return false;
	}

	//----------ADDING PHYSICSBODY TO ENEMY SPRITE----------//
	auto enemyBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);		//We create an Physics Body in the width and height of our Sprite.
	enemyBody->setCollisionBitmask(ENEMY_TRIGGER_BITMASK);
	enemyBody->setContactTestBitmask(true);																//If true, our Sprite interacts with other physical objects.
	this->setPhysicsBody(enemyBody);

	return true;

}

void EnemySprite::reset()
{

}