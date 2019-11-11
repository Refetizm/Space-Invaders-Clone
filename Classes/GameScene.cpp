#include "GameScene.h"
#include "GameOverScene.h"
#include "Player.h"
#include "PlayerPool.h"
#include "Bullet.h"
#include "BulletPool.h"
#include "Enemy.h"
#include "EnemyPool.h"
#include "AudioEngine.h"
#include "Definitions.h"

USING_NS_CC;

unsigned int highScore;

using namespace cocos2d::experimental;

Scene* GameScene::createScene(unsigned int tempScoreGame)
{
	highScore = tempScoreGame;														//For showing High Score on Game Scene.
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	scene->getPhysicsWorld()->setGravity(Vec2(0.0, 0.0));
	auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//----------ADDING BACKGROUND----------//
	auto backgroundSprite = Sprite::create("Background.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite, 0);

	//----------ADDING PLAYER----------//
	auto playerSprite = PlayerPool::getPlayer()->getPlayerSprite(PLAYER_ID_TAG);				//We're pulling the Player Sprite from the pool.
	if (playerSprite == nullptr)
	{
		CCLOG("PLAYER LOADING ERROR!");
	}
	else
	{
		playerSprite->setPosition(Point(visibleSize.width / 2 + origin.x, playerSprite->getContentSize().height * 2 + origin.y));			//Positioning the Player Sprite.
		this->addChild(playerSprite, 1);
	}

	//----------DEFINITIONS----------//
	isTouchBegan = false;						//Touch action hasn't started yet.
	bulletElapsedTime = 0.f;					//Time between two Bullet's spawn.
	score = 0;									//

	//----------TOUCH EVENTS----------//
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);

	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);								//While the touch begins.
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);								//While the touch continue.
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);								//While the touch ends.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//----------PHYSICS EVENTS----------//
	auto playerContactListener = EventListenerPhysicsContact::create();										//Player contact with another physical objects.
	playerContactListener->onContactBegin = CC_CALLBACK_1(GameScene::onPlayerContactBegin, this);			
	_eventDispatcher->addEventListenerWithSceneGraphPriority(playerContactListener, this);

	auto bulletContactListener = EventListenerPhysicsContact::create();										//Bullets contact with another physical objects.
	bulletContactListener->onContactBegin = CC_CALLBACK_1(GameScene::onBulletContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(bulletContactListener, this);

	//----------SCORE LABELS----------//
	//#1__SCORE-LABEL__
	__String* tempScore = __String::createWithFormat("SCORE: %i", score);
	scoreLabel = Label::createWithTTF(tempScore->getCString(), "fonts/PressStart2P.ttf", visibleSize.height * SCORE_FONT_SIZE);
	scoreLabel->setColor(Color3B::WHITE);
	scoreLabel->setAnchorPoint(Vec2(0.0, 0.0));
	scoreLabel->setPosition(Point(scoreLabel->getContentSize().height, visibleSize.height - scoreLabel->getContentSize().height * 2));
	this->addChild(scoreLabel, 1000);

	//#2__HIGH-SCORE-LABEL__
	UserDefault* def = UserDefault::getInstance();
	auto highScore = def->getIntegerForKey("HIGHSCORE", 0);
	if (score > highScore)
	{
		highScore = score;
		__String* tempHighScore = __String::createWithFormat("HIGHSCORE: %i", score);
		highScoreLabel->setString(tempHighScore->getCString());
	}

	def->flush();

	__String* tempHighScore = __String::createWithFormat("HIGHSCORE: %i", highScore);
	highScoreLabel = Label::createWithTTF(tempHighScore->getCString(), "fonts/PressStart2P.ttf", visibleSize.height * SCORE_FONT_SIZE);
	highScoreLabel->setColor(Color3B::WHITE);
	highScoreLabel->setAnchorPoint(Vec2(1.0, 0.0));
	highScoreLabel->setPosition(Point(visibleSize.width - highScoreLabel->getContentSize().height, visibleSize.height - highScoreLabel->getContentSize().height * 2));
	this->addChild(highScoreLabel, 1000);

	//----------GENERATE BULLETS----------//
	schedule(schedule_selector(GameScene::generateBullets), BULLET_SPAWN_SPEED);
	scheduleUpdate();

	return true;

}

//----------TOUCH FUNCTIONS----------//
//#1__TOUCH-BEGIN__
bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	isTouchBegan = true;											//Touch action has started.
	touchXPosition = touch->getLocation().x;						//We get X coordinate of the point where we touch the screen.
	return true;
}

//#2__TOUCH-MOVED__
bool GameScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	touchXPosition = touch->getLocation().x;
	return true;
}

//#3__TOUCH-ENDED__
bool GameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	isTouchBegan = false;											//Touch action has ended.
	return true;
}

//----------CONTACT FUNCTIONS----------//
//#1__PLAYER-CONTACT__
bool GameScene::onPlayerContactBegin(cocos2d::PhysicsContact& playerContact)
{
	PhysicsBody* a = playerContact.getShapeA()->getBody();
	PhysicsBody* b = playerContact.getShapeB()->getBody();
	//if player and enemy crash
	if ((PLAYER_TRIGGER_BITMASK == a->getCollisionBitmask() && ENEMY_TRIGGER_BITMASK == b->getCollisionBitmask()) || (PLAYER_TRIGGER_BITMASK == b->getCollisionBitmask() && ENEMY_TRIGGER_BITMASK == a->getCollisionBitmask()))
	{
		auto gameOverEffect = experimental::AudioEngine::play2d("Audio/gameOver.mp3");					//Every time we hit the enemy, the sound file 'gameOver.mp3' will play.
		experimental::AudioEngine::setVolume(gameOverEffect, 0.5);										//Sound effect volume value.
		auto scene = GameOverScene::createScene(score);													//Generating Game Over Scene and we take the score value with us.
		Director::getInstance()->replaceScene(TransitionFlipX::create(TRANSITION_TIME, scene));			//Replacing Game Over Scene with the Game Scene.
	}
	return true;
}

//#2__BULLET-CONTACT__
bool GameScene::onBulletContactBegin(cocos2d::PhysicsContact& bulletContact)
{
	Node* a = bulletContact.getShapeA()->getBody()->getNode();											//We use 'Node' to destroy the object we hit.
	Node* b = bulletContact.getShapeB()->getBody()->getNode();
	//if bullet and enemy crash.
	if (a->getTag() == BULLET_ID_TAG && b->getTag() == ENEMY_ID_TAG || a->getTag() == ENEMY_ID_TAG && b->getTag() == BULLET_ID_TAG)
	{
		auto explosionEffect = experimental::AudioEngine::play2d("Audio/explosion.mp3");				//Every time the bullets hit the enemies, the sound file 'explosion.mp3' will play.
		experimental::AudioEngine::setVolume(explosionEffect, 0.5);										//Sound effect volume value.

		//----------UPDATING SCORE----------//
		score = score + 25;																				//Everytime we hit the enemies with bullets, we gain 25 points.
		__String* tempScore = __String::createWithFormat("SCORE: %i", score);
		scoreLabel->setString(tempScore->getCString());													//Update the score on label.

		//----------UPDATING HIGHSCORE----------//
		UserDefault* def = UserDefault::getInstance();
		auto highScore = def->getIntegerForKey("HIGHSCORE", 0);
		if (score > highScore)
		{
			highScore = score;
			__String* tempHighScore = __String::createWithFormat("HIGHSCORE: %i", score);
			highScoreLabel->setString(tempHighScore->getCString());
		}
		def->flush();

		//----------REMOVING OBJECTS----------//
		if (a->getTag() == BULLET_ID_TAG)
		{
			this->removeChild(a);														//Remove object 'a'.
			BulletPool::getBullets()->returnBullet((BulletSprite*)a);					//In fact, we don't delete objects, we get them back to the pool we created.
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

//----------GENERATE BULLETS----------//
void GameScene::generateBullets(float dt)
{
	auto bulletSprite = BulletPool::getBullets()->getSprite(BULLET_ID_TAG);										//We don't create Bullets from scratch. We pull Bullet Sprites from the Bullet Bool that are already loaded in memory.
	if (bulletSprite == nullptr)
	{
		CCLOG("BULLET LOADING PROBLEM!");
	}
	else
	{
		auto playerNode = getChildByTag(PLAYER_ID_TAG);															//We pull Player as a 'Node'. Because we need Player's position.
		if (playerNode != nullptr)
		{
			bulletSprite->setPositionX(playerNode->getPositionX());
			bulletSprite->setPositionY(playerNode->getPositionY() + playerNode->getContentSize().height);
			this->addChild(bulletSprite, 1);
			auto bulletEffect = experimental::AudioEngine::play2d("Audio/bullet.mp3");							//Every time the bullets spawned, the sound file 'bullet.mp3' will play.				
			experimental::AudioEngine::setVolume(bulletEffect, 0.1);											//Sound effect volume value.
		}
	}
}

//----------GENERATE ENEMIES----------//
void GameScene::generateEnemies(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int enemyColumn = ENEMY_NUMBER;
	int enemyRow = std::min(++enemyLevel + 1, 5);																//'enemyRow' is equal to 2 to 5 consecutive numbers.
	#define SHIP_DISTANCE_Y			enemySprite->getContentSize().height * 2									//Vertical distance between Enemy Sprites. In other words, the distance between Rows.

	for (int j = 0; j < enemyRow; j++)																			//For 0 to 'enemyRow' values.
	{
		for (int i = 1; i < enemyColumn; i++)																	//For 1 to 'enemyColumn' values.
		{
			auto enemySprite = EnemyPool::getEnemy()->getEnemySprite(ENEMY_ID_TAG);								//We're pulling the Enemy Sprite from the pool.
			if (enemySprite == nullptr)
			{
				CCLOG("ENEMY LOADING PROBLEM!");
			}
			else
			{
				enemySprite->setPosition(Point(visibleSize.width / ENEMY_NUMBER * i, visibleSize.height + origin.y + SHIP_DISTANCE_Y * j));		//Positioning the Enemy Sprites.
				this->addChild(enemySprite, 1);
			}
		}

	}
}

//----------UPDATING THE SCENE----------//
void GameScene::update(float dt)
{
	bulletElapsedTime += dt;											//'bulletElapsedTime' increases with time.
	if (bulletElapsedTime >= BULLET_SPAWN_SPEED)
	{
		bulletElapsedTime = 0.f;										//if the 'bulletElapsedTime' value bigger than 'BULLET_SPAWN_SPEED', reset the 'bulletElapsedTime' and start 'generateBullets()' function.
		generateBullets();
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	bool enemyExist = false;											//We will use this value to see if there are Enemies left in the Game Scene.

	cocos2d::Vector<Node*> children = this->getChildren();				//We create child Nodes in Vector format.
	for each (Node * child in children)									
	{
		if (child->getTag() != BULLET_ID_TAG && child->getTag() != PLAYER_ID_TAG && child->getTag() != ENEMY_ID_TAG)
		{
			continue;													//No update for other objects.
		}
		//----------PLAYER SPRITE MOVEMENT----------//
		PlayerSprite* spritePlayer = (PlayerSprite*)child;
		if (spritePlayer->getTag() == PLAYER_ID_TAG)
		{
			if (!isTouchBegan)
			{
				continue;												//If the touch action hasn't started yet, do nothing.
			}
			float currentXPosition = spritePlayer->getPositionX();		//Pulling the current X Position of the Player Sprite.
			/****************************************************************************************************************
			//Here we divide the screen in half. If the point we touch is on the left half of the screen,
			//Player Sprite will move to the left. If the point we touch is on the right half of the screen, Player Sprite will move to the right.
			****************************************************************************************************************/
			if (touchXPosition <= visibleSize.width / 2 + origin.x && currentXPosition >= spritePlayer->getContentSize().width / 2)
			{
				spritePlayer->setPositionX(currentXPosition - PLAYER_MOVEMENT_SPEED);				//Move to Left.
			}
			else if (touchXPosition >= visibleSize.width / 2 + origin.x && currentXPosition <= visibleSize.width - spritePlayer->getContentSize().width / 2)
			{
				spritePlayer->setPositionX(currentXPosition + PLAYER_MOVEMENT_SPEED);				//Move to Right.
			}
		}

		//----------BULLET SPRITE MOVEMENT----------//
		BulletSprite* spriteBullet = (BulletSprite*)child;
		if (spriteBullet->getTag() == BULLET_ID_TAG)
		{
			spriteBullet->setPositionY(spriteBullet->getPositionY() + BULLET_MOVEMENT_SPEED);		//Move to Up.
			if (spriteBullet->getPositionY() > visibleSize.height + origin.y)							//If the Bullets left the Game Scene.
			{
				this->removeChild(spriteBullet);
				BulletPool::getBullets()->returnBullet(spriteBullet);								//Bullets leaving the Game Scene will return to the pool.
			}
		}

		//----------ENEMY SPRITE MOVEMENT----------//
		EnemySprite* spriteEnemy = (EnemySprite*)child;
		if (spriteEnemy->getTag() == ENEMY_ID_TAG)
		{
			spriteEnemy->setPositionY(spriteEnemy->getPositionY() - ENEMY_MOVEMENT_SPEED);			//Move to Down.
			if (spriteEnemy->getPositionY() < origin.y - 40.f)										//If the Enemies left the Game Scene.
			{
				this->removeChild(spriteEnemy);
				EnemyPool::getEnemy()->returnEnemy(spriteEnemy);									//Enemies leaving the Game Scene will return to the pool.
			}
			else
			{
				enemyExist = true;
			}
		}

	}
	if (!enemyExist)
	{
		generateEnemies();																			//If there is no more Enemy on the Game Scene, run the 'generateEnemies()' function.
	}
}