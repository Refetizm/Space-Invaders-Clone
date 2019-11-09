#include "Bullet.h"

USING_NS_CC;

BulletSprite* BulletSprite::createSprite(int refetizm)
{
	BulletSprite* sprite = new BulletSprite;
	if (sprite != nullptr)
	{
		sprite->setTag(refetizm);
		sprite->init();
	}
	return sprite;
}

bool BulletSprite::init()
{
	std::string rsrcFileName;
	if (getTag() == BULLET_TAG)
	{
		rsrcFileName = StringUtils::format("Bullet.png");
	}
	if (!Sprite::initWithFile(rsrcFileName))
	{
		return false;
	}



	auto bulletBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	bulletBody->setContactTestBitmask(true);
	bulletBody->setCollisionBitmask(BULLET_TRIGGER_BITMASK);
	this->setPhysicsBody(bulletBody);
	return true;
}

void BulletSprite::reset()
{

}