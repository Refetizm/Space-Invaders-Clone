#ifndef __CREDITS_SCENE_H__
#define __CREDITS_SCENE_H__

#include "cocos2d.h"

class CreditsScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void GoToMainMenu(cocos2d::Ref* psender);						//Function for to go to Main Menu Scene.

	CREATE_FUNC(CreditsScene);
};
#endif // !__CREDITS_SCENE_H__
