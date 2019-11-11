#include "CreditsScene.h"
#include "MainMenu.h"
#include "Definitions.h"

USING_NS_CC;

Scene* CreditsScene::createScene()
{
	return CreditsScene::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool CreditsScene::init()
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

	//----------ADDING CREDITS----------//
	auto creditsSprite = Sprite::create("CreditsText.png");
	creditsSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(creditsSprite, 2);

	//----------ADDING MENU ITEMS----------//
	//#1__MAIN_MENU__
	auto mainMenuItem = MenuItemImage::create("MainMenu.png", "MainMenu.png", CC_CALLBACK_1(CreditsScene::GoToMainMenu, this));
	mainMenuItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 4 + origin.y));

	//----------GENERATE MENU----------//
	auto menu = Menu::create(mainMenuItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 5);
	
	return true;

}

void CreditsScene::GoToMainMenu(cocos2d::Ref* psender)
{
	auto scene = MainMenuScene::createScene();															//Generating Main Menu Scene.
	Director::getInstance()->replaceScene(TransitionFlipX::create(TRANSITION_TIME, scene));				//Replacing Main Menu Scene with Credits Scene.
}