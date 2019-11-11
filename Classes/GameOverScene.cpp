#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenu.h"
#include "Definitions.h"

USING_NS_CC;

unsigned int score;

Scene* GameOverScene::createScene(unsigned int tempScore)
{
	score = tempScore;
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameOverScene.cpp\n");
}

bool GameOverScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//----------ADDING BACKGROUND----------//
	auto backgroundSprite = Sprite::create("MenuBackground.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite, 1);

	//----------ADDING GAME OVER LOGO----------//
	auto gameOverSprite = Sprite::create("GameOver.png");
	gameOverSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 3 + origin.y));
	this->addChild(gameOverSprite, 2);

	//----------ADDING MENU ITEMS----------//
	//#1__RETRY__
	auto retryItem = MenuItemImage::create("Retry.png", "Retry.png", CC_CALLBACK_1(GameOverScene::GoToGameScene, this));
	retryItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 1.5 + origin.y));

	//#2__MAIN-MENU__
	auto mainMenuItem = MenuItemImage::create("MainMenu.png", "MainMenu.png", CC_CALLBACK_1(GameOverScene::GoToMainMenuScene, this));
	mainMenuItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 1.2 + origin.y));

	//#3__EXIT__
	auto exitItem = MenuItemImage::create("Exit.png", "Exit.png", CC_CALLBACK_1(GameOverScene::GoToExit, this));
	exitItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 0.9 + origin.y));

	//----------GENERATE MENU----------//
	auto menu = Menu::create(retryItem, mainMenuItem, exitItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 100);

	//----------SCORE LABELS----------//
	//#1__SCORE-LABEL__
	__String* tempScore = __String::createWithFormat("YOUR SCORE: %i", score);
	auto currentScore = Label::createWithTTF(tempScore->getCString(), "fonts/PressStart2P.ttf", visibleSize.height * SCORE_FONT_SIZE);
	currentScore->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 2.2 + origin.y));
	this->addChild(currentScore, 1000);

	//#2__HIGH-SCORE-LABEL__
	UserDefault* def = UserDefault::getInstance();
	auto highScore = def->getIntegerForKey("HIGHSCORE", 0);
	if (score > highScore)
	{
		highScore = score;
		def->setIntegerForKey("HIGHSCORE", highScore);
	}

	def->flush();

	__String* tempHighScore = __String::createWithFormat("HIGHSCORE: %i", highScore);
	auto highScoreLabel = Label::createWithTTF(tempHighScore->getCString(), "fonts/PressStart2P.ttf", visibleSize.height * SCORE_FONT_SIZE);
	highScoreLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 2 + origin.y));
	this->addChild(highScoreLabel, 1000);

	return true;
}

void GameOverScene::GoToGameScene(cocos2d::Ref* psender)
{
	auto scene = GameScene::createScene(highScore);
	Director::getInstance()->replaceScene(TransitionFlipX::create(TRANSITION_TIME, scene));
}

void GameOverScene::GoToMainMenuScene(cocos2d::Ref* psender)
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFlipX::create(TRANSITION_TIME, scene));
}

void GameOverScene::GoToExit(cocos2d::Ref* psender)
{
	Director::getInstance()->end();
}