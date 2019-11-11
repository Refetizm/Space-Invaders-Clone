#include "Bullet.h"

USING_NS_CC;

BulletSprite* BulletSprite::createSprite(int bulletIdTag)
{
	BulletSprite* sprite = new BulletSprite;
	if (sprite != nullptr)
	{
		sprite->setTag(bulletIdTag);																	//We set every BulletSprite's tag.
		sprite->init();
	}
	return sprite;
}

bool BulletSprite::init()
{
	//----------ADDING BULLET SPRITE----------//
	std::string rsrcFileName;
	if (getTag() == BULLET_ID_TAG)
	{
		rsrcFileName = StringUtils::format("Bullet.png");												//If our tag is equal to the 'BULLET_ID_TAG', call "Bullet.png".
	}
	if (!Sprite::initWithFile(rsrcFileName))
	{
		return false;
	}

	//----------ADDING PHYSICSBODY TO BULLET SPRITE----------//
	auto bulletBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);		//We create an Physics Body in the width and height of our Sprite.
	bulletBody->setContactTestBitmask(true);															//If true, our Sprite interacts with other physical objects.
	this->setPhysicsBody(bulletBody);

	return true;

}

void BulletSprite::reset()
{

}