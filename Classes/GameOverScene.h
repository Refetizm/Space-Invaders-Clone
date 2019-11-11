#ifndef __GAME_OVER_SCENE_H__
#define __GAME_OVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(unsigned int tempScore);
	virtual bool init();
private:
	void GoToGameScene(cocos2d::Ref* psender);						//Function for to go to Game Scene.
	void GoToMainMenuScene(cocos2d::Ref* psender);					//Function for to go to Main Menu Scene.
	void GoToExit(cocos2d::Ref* psender);							//Function for close the Game.

	unsigned int highScore;											//This variable is to show High Score in the game scene.

	CREATE_FUNC(GameOverScene);
};
#endif // !__GAME_OVER_SCENE_H__
