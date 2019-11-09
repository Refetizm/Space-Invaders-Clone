#include "Player.h"


USING_NS_CC;

PlayerSprite* PlayerSprite::createSprite(int kargaizm)
{
	PlayerSprite* sprite = new PlayerSprite;
	if (sprite != nullptr)
	{
		sprite->setTag(kargaizm);
		sprite->init();
	}
	return sprite;
}

bool PlayerSprite::init()
{
	std::string rsrcFileName;
	if (getTag() == PLAYER_TAG)
	{
		rsrcFileName = StringUtils::format("Player.png");
	}
	if (!Sprite::initWithFile(rsrcFileName))
	{
		return false;
	}

	auto playerBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	playerBody->setContactTestBitmask(true);
	playerBody->setCollisionBitmask(PLAYER_TRIGGER_BITMASK);
	this->setPhysicsBody(playerBody);

	return true;
}

void PlayerSprite::reset()
{

}