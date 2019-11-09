#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Player.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	virtual void update(float dt);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	bool onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	bool onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	bool onPlayerContactBegin(cocos2d::PhysicsContact& playerContact);
	bool onBulletContactBegin(cocos2d::PhysicsContact& bulletContact);



    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	void generateBullets(float dt = 0.f);
	void generateEnemies(float dt = 0.f);
	void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { _sceneWorld = world; };
private:

	bool isTouchBegan;
	float touchXPosition;
	float _elapsed;
	float _bulletElapsed;
	int _level;
	cocos2d::PhysicsWorld* _sceneWorld;
};

#endif // __HELLOWORLD_SCENE_H__
