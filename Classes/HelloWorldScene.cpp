#include "HelloWorldScene.h"
#include "Bullet.h"
#include "BulletPool.h"
#include "Player.h"
#include "PlayerPool.h"
#include "Enemy.h"
#include "EnemyPool.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0.0, 0.0));
	auto layer = HelloWorld::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

	auto backgroundSprite = Sprite::create("Background.png");
	backgroundSprite->setAnchorPoint(Vec2(0.0, 0.0));
	backgroundSprite->setPosition(Point(0, 0));
	this->addChild(backgroundSprite, 0);

	
	
	
    /////////////////////////////
    // 3. add your codes below...

	auto playerSprite = PlayerPool::getPlayer()->getPlayerSprite(PLAYER_TAG);
	if (playerSprite == nullptr)
	{
		CCLOG("PLAYER ERROR!");
	}
	else
	{
		playerSprite->setPosition(Point(visibleSize.width / 2 + origin.x, playerSprite->getContentSize().height * 4 + origin.y));
		this->addChild(playerSprite, 1);
	}



	isTouchBegan = false;
	_elapsed = 0.f;
	_bulletElapsed = 0.f;
	

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto playerContactListener = EventListenerPhysicsContact::create();
	playerContactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onPlayerContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(playerContactListener, this);

	auto bulletContactListener = EventListenerPhysicsContact::create();
	bulletContactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onBulletContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(bulletContactListener, this);


	schedule(schedule_selector(HelloWorld::generateBullets), NORMAL_SPEED);
	scheduleUpdate();
    // add a label shows "Hello World"
    // create and initialize a label

    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	isTouchBegan = true;
	touchXPosition = touch->getLocation().x;
	return true;
}

bool HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	touchXPosition = touch->getLocation().x;
	return true;
}

bool HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	isTouchBegan = false;
	return true;
}

bool HelloWorld::onPlayerContactBegin(cocos2d::PhysicsContact& playerContact)
{
	PhysicsBody* a = playerContact.getShapeA()->getBody();
	PhysicsBody* b = playerContact.getShapeB()->getBody();
	if ((PLAYER_TRIGGER_BITMASK == a->getCollisionBitmask() && ENEMY_TRIGGER_BITMASK == b->getCollisionBitmask()) || (PLAYER_TRIGGER_BITMASK == b->getCollisionBitmask() && ENEMY_TRIGGER_BITMASK == a->getCollisionBitmask()))
	{
		CCLOG("GAME OVER!");
	}
	return true;
}

bool HelloWorld::onBulletContactBegin(cocos2d::PhysicsContact& bulletContact)
{
	Node* a = bulletContact.getShapeA()->getBody()->getNode();
	Node* b = bulletContact.getShapeB()->getBody()->getNode();
	if (a->getTag() == BULLET_TAG && b->getTag() == ENEMY_TAG || a->getTag() == ENEMY_TAG && b->getTag() == BULLET_TAG)
	{
		if (a->getTag() == BULLET_TAG)
		{
			this->removeChild(a);
			BulletPool::getBullets()->returnBullet((BulletSprite*)a);
			this->removeChild(b);
			EnemyPool::getEnemy()->returnEnemy((EnemySprite*)b);
		}
		else
		{
			this->removeChild(b);
			BulletPool::getBullets()->returnBullet((BulletSprite*)b);
			this->removeChild(a);
			EnemyPool::getEnemy()->returnEnemy((EnemySprite*)a);
		}
	}
	return true;
}




void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::generateBullets(float dt)
{
	auto bulletSprite = BulletPool::getBullets()->getSprite(BULLET_TAG);

	if (bulletSprite == nullptr)
	{
		CCLOG("BULLET PROBLEM!!");
	}
	else
	{
		auto playerNode = getChildByTag(PLAYER_TAG);
		if (playerNode != nullptr)
		{
			bulletSprite->setPositionX(playerNode->getPositionX());
			bulletSprite->setPositionY(playerNode->getPositionY() + playerNode->getContentSize().height);
			this->addChild(bulletSprite, 1);
		}
	}

}

void HelloWorld::generateEnemies(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

#define SHIP_OCCU_WIDTH			SHIP_WIDTH * 3.f / 2.f
#define SHIP_OCCU_HEIGHT		SHIP_HEIGHT * 3.f / 2.f
#define MARGIN_X				SHIP_WIDTH / 2.f
#define SHIPPER					enemySprite->getContentSize().height * 2
	float occu_width = SHIP_OCCU_WIDTH;
	float delta_val = visibleSize.width - MARGIN_X * 2.f;
	int col_cnt = delta_val / occu_width + 1;
	int columnNew = OBJECT_NUMBER;
	int row_cnt = std::min(++_level + 1, 5);

	for (int j = 0; j < row_cnt; j++)
	{
		for (int i = 1; i < columnNew; i++)
		{
			auto enemySprite = EnemyPool::getEnemy()->getEnemySprite(ENEMY_TAG);
			if (enemySprite == nullptr)
			{
				CCLOG("ENEMY PROBLEM APPEARED!!!");
			}
			else
			{
				//enemySprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
				enemySprite->setPosition(Point(visibleSize.width / OBJECT_NUMBER * i, visibleSize.height + origin.y + SHIPPER * j));
				this->addChild(enemySprite, 1);
			}
		}
	}
}

void HelloWorld::update(float dt)
{

	_bulletElapsed += dt;
	if (_bulletElapsed >= NORMAL_SPEED)
	{
		_bulletElapsed = 0.f;
		generateBullets();
	}
	

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	bool enemyExist = false;

	cocos2d::Vector<Node*> children = this->getChildren();
	for each (Node* child in children)
	{
		if (child->getTag() != BULLET_TAG && child->getTag() != PLAYER_TAG && child->getTag() != ENEMY_TAG)
		{
			continue;
		}

		BulletSprite* deneme = (BulletSprite*)child;
		if (deneme->getTag() == BULLET_TAG)
		{
			deneme->setPositionY(deneme->getPositionY() + BULLET_DELTA_Y);
			if (deneme->getPositionY() > 900)
			{
				this->removeChild(deneme);
				BulletPool::getBullets()->returnBullet(deneme);
				//CCLOG("End is near");
			}
		}
		PlayerSprite* denemePlayer = (PlayerSprite*)child;
		if (denemePlayer->getTag() == PLAYER_TAG)
		{
			if (!isTouchBegan)
			{
				continue;
			}
			float currentXPosition = denemePlayer->getPositionX();
			if (touchXPosition <= visibleSize.width / 2 + origin.x && currentXPosition >= denemePlayer->getContentSize().width / 2)
			{
				denemePlayer->setPositionX(currentXPosition - SHIP_DELTA_X);
				
			}
			else if (touchXPosition >= visibleSize.width / 2 + origin.x && currentXPosition <= visibleSize.width - denemePlayer->getContentSize().width / 2)
			{
				denemePlayer->setPositionX(currentXPosition + SHIP_DELTA_X);
			}
			
		}
		EnemySprite* enemyPlayer = (EnemySprite*)child;
		if (enemyPlayer->getTag() == ENEMY_TAG)
		{
			enemyPlayer->setPositionY(enemyPlayer->getPositionY() - SHIP_DELTA_Y);
			if (enemyPlayer->getPositionY() < origin.y - 40.f)
			{
				this->removeChild(enemyPlayer);
				EnemyPool::getEnemy()->returnEnemy(enemyPlayer);
			}
			else
			{
				enemyExist = true;
			}
		}

	}
	if (!enemyExist)
	{
		generateEnemies();
	}
	
}