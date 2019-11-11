#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(MainMenuScene);
private:
	void GoToGameScene(cocos2d::Ref* psender);				//Function for to go to Game Scene.
	void GoToCreditsScene(cocos2d::Ref* psender);			//Function for to go to Credits Scene.
	void GoToExit(cocos2d::Ref* psender);					//Function for close the game.
	void GoToGitHub(cocos2d::Ref* psender);					//Function for to go to GitHub page.

	unsigned int highScore;									//This variable is to show High Score in the game scene.
};
#endif // !__MAIN_MENU_H__
