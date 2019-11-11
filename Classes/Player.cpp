#include "Player.h"

USING_NS_CC;

PlayerSprite* PlayerSprite::createSprite(int playerIdTag)
{
	PlayerSprite* sprite = new PlayerSprite;
	if (sprite != nullptr)
	{
		sprite->setTag(playerIdTag);																	//We set every PlayerSprite's tag.
		sprite->init();
	}
	return sprite;
}

bool PlayerSprite::init()
{
	//----------ADDING PLAYER SPRITE----------//
	std::string rsrcFileName;
	if (getTag() == PLAYER_ID_TAG)
	{
		rsrcFileName = StringUtils::format("Player.png");												//If our tag is equal to the 'PLAYER_ID_TAG', call "Player.png".
	}
	if (!Sprite::initWithFile(rsrcFileName))
	{
		return false;
	}

	//----------ADDING PHYSICSBODY TO PLAYER SPRITE----------//
	auto playerBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);		//We create an Physics Body in the width and height of our Sprite.
	playerBody->setCollisionBitmask(PLAYER_TRIGGER_BITMASK);
	playerBody->setContactTestBitmask(true);															//If true, our Sprite interacts with other physical objects.
	this->setPhysicsBody(playerBody);

	return true;

}

void PlayerSprite::reset()
{

}