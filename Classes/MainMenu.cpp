#include "MainMenu.h"
#include "GameScene.h"
#include "CreditsScene.h"
#include "GameOverScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
	return MainMenuScene::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MainMenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//----------ADDING BACKGROUND----------//
	auto backgroundSprite = Sprite::create("MenuBackground.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite, 1);

	//----------ADDING GAME LOGO----------//
	auto logoSprite = Sprite::create("GameLogo.png");
	logoSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 3 + origin.y));
	this->addChild(logoSprite, 2);

	//----------ADDING MENU ITEMS----------//
	//#1__START__
	auto startItem = MenuItemImage::create("Start.png", "Start.png", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));			//When clicked, start the GoToGameScene function.
	startItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 2.1 + origin.y));

	//#2__CREDITS__
	auto creditsItem = MenuItemImage::create("Credits.png", "Credits.png", CC_CALLBACK_1(MainMenuScene::GoToCreditsScene, this));	//When clicked, start the GoToCreditsScene function.
	creditsItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 1.8 + origin.y));

	//#3__EXIT__
	auto exitItem = MenuItemImage::create("Exit.png", "Exit.png", CC_CALLBACK_1(MainMenuScene::GoToExit, this));					//When clicked, start the GoToExit function.
	exitItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 1.5 + origin.y));

	//#4__GITHUB__
	auto gitHubItem = MenuItemImage::create("GitHub.png", "GitHub.png", CC_CALLBACK_1(MainMenuScene::GoToGitHub, this));			//When clicked, start the GoToGitHub function.
	gitHubItem->setPosition(Point(gitHubItem->getContentSize().width / 2 + origin.x, gitHubItem->getContentSize().height + origin.y));

	//----------GENERATE MENU----------//
	auto menu = Menu::create(startItem, creditsItem, exitItem, gitHubItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

	return true;
}

void MainMenuScene::GoToGameScene(cocos2d::Ref* psender)
{
	auto scene = GameScene::createScene(highScore);																//Generating Game Scene and transferring highScore value.
	Director::getInstance()->replaceScene(TransitionFlipX::create(TRANSITION_TIME, scene));						//Replacing Game Scene with Main Menu Scene.
}

void MainMenuScene::GoToCreditsScene(cocos2d::Ref* psender)
{
	auto scene = CreditsScene::createScene();																	//Generating Game Scene.
	Director::getInstance()->replaceScene(TransitionFlipX::create(TRANSITION_TIME, scene));						//Replacing Credits Scene with Main Menu Scene.
}

void MainMenuScene::GoToGitHub(cocos2d::Ref* psender)
{
	Application::getInstance()->openURL("https://github.com/Refetizm/Space-Invaders-Clone");					//The URL address opens in the default browser.
}

void MainMenuScene::GoToExit(cocos2d::Ref* psender)
{
	Director::getInstance()->end();																				//Closing the Game.
}