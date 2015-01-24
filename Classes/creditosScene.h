#ifndef __CREDITOS_SCENE_H__
#define __CREDITOS_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class creditos : public cocos2d::Layer
{
public:

    static Scene* createScene();
	virtual bool init();
    //Limites
	float limx;
	float limy;

	//Sprites
	Sprite *background;

	//Buttons
	void goMenu(Ref *pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(creditos);
};

#endif // __CREDITOS_SCENE_H__
