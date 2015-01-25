#ifndef __LVL1_SCENE_H__
#define __LVL1_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;

class lvl1 : public cocos2d::Layer
{
public:
	//Constructor and Destructor
	lvl1();
	~lvl1();
	//Scene
    static Scene* createScene();
	virtual bool init();
    //Limites
	float limx;
	float limy;
	//UPDATE
	void update(float dt);
	//TOUCH
	bool onTouchBegan(Touch* touch, Event* event);
	//void onTouchMoved(Touch* touch, Event* event);

	//Global Variables
	int stepCount;
	bool canJump;
	// VAR POWERS
	bool isEarth;
	bool isWind;
	bool isWater;
	bool isFire;
	//POWERS
	void earth(Ref *pSender);
	void wind(Ref *pSender);
	void water(Ref *pSender);
	void fire(Ref *pSender);
	//SPRITES
	Sprite *background;
	PhysicsBody *backgroundPhy;
	Sprite *background2;
	PhysicsBody *backgroundPhy2;
	Sprite *power1;
	Sprite *power2;
	Sprite *power3;
	Sprite *power4;

	//PHYSICS BODYS
	PhysicsBody *megamanPhy;
	//ANIMATIONS
	Armature *megaman;

    // implement the "static create()" method manually
    CREATE_FUNC(lvl1);
private:
	cocos2d::PhysicsWorld *sceneWorld;
	void SetPhysicsWorld( cocos2d::PhysicsWorld *world ) { sceneWorld = world; };
	bool onContactBegin( cocos2d::PhysicsContact &contact );
};

#endif // __LVL1_SCENE_H__
