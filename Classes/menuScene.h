#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class menu : public cocos2d::Layer
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
	void Play(Ref *pSender);
	void Cred(Ref *pSender);
	void Quit(Ref *pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(menu);
};

#endif // __MENU_SCENE_H__
