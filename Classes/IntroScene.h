#ifndef __INTRO_SCENE_H__
#define __INTRO_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class Intro : public cocos2d::Layer
{
public:

    static Scene* createScene();
	virtual bool init();
    //Limites
	float limx;
	float limy;
	
	//Global Variables
	int stepCount;

    //SPRITES
	Sprite *spritelog;

    //Update
	void loadingsStep(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(Intro);
};

#endif // __INTRO_SCENE_H__
