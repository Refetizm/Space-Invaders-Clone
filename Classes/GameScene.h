#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameOverScene.h"

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene(unsigned int tempScoreGame);						//'tempScoreGame' is for pull the High Score.
	virtual bool init();
	virtual void update(float dt);														//For update our functions.

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);					//While the touch begins.
	bool onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);					//While the touch continue.
	bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);					//While the touch ends.

	bool onPlayerContactBegin(cocos2d::PhysicsContact& playerContact);					//While the player contact with another physical object.
	bool onBulletContactBegin(cocos2d::PhysicsContact& bulletContact);					//While the bullets contact with another physical object.

	CREATE_FUNC(GameScene);

private:
	void generateBullets(float dt = 0.f);												//Function for generating bullets.
	void generateEnemies(float dt = 0.f);												//Function for generating enemies.
	void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };			//Function for activate the physical activities in our scene.
	void GoToGameOverScene(cocos2d::Ref* psender);										//Function for to go to Game Over Scene.
private:
	cocos2d::PhysicsWorld* sceneWorld;

	bool isTouchBegan;																	//For control to touch action begin or not.

	float touchXPosition;																//X coordinate of the point where we touch the screen.
	float bulletElapsedTime;															//Time between two Bullet's spawn.

	int enemyLevel;																		//Level system for enemies.
	unsigned int score;																	//Score value.

	cocos2d::Label* scoreLabel;															//Label to print the Score on the screen.
	cocos2d::Label* highScoreLabel;														//Label to print the High Score on the screen.

};
#endif // !__GAME_SCENE_H__
