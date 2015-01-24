#include "menuScene.h"
#include "creditosScene.h"
#include "lvl1Scene.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* menu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = menu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

//INIT
bool menu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//Limites
    limx=visibleSize.width;
    limy=visibleSize.height;
	//Music - Brackground
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("theme.3ga",true);

    //BackGround
    background = Sprite::create("HelloWorld.png");
    background->setPosition(Vec2(limx/2 + origin.x, limy/2 + origin.y));
    this->addChild(background, 0);

	//Menu Content
	auto menu_item_1 = MenuItemImage::create("CloseNormal.png",
                                           "CloseNormal.png",CC_CALLBACK_1(menu::Play,this));
	auto menu_item_2 = MenuItemImage::create("CloseNormal.png",
                                           "CloseNormal.png",CC_CALLBACK_1(menu::Cred,this));
	auto menu_item_3 = MenuItemImage::create("CloseNormal.png",
                                           "CloseNormal.png",CC_CALLBACK_1(menu::Quit,this));

	menu_item_1->setPosition(Point(limx/2+225,(limy/4)*3-20));
	menu_item_2->setPosition(Point(limx/2+225,(limy/4)*2-20));
	menu_item_3->setPosition(Point(limx/2+225,(limy/4)*1-20));

	auto menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, NULL);
	menu->setPosition(Point(0,0));
	this->addChild(menu,1);

   
    return true;
}

void menu::Play(cocos2d::Ref *pSender)
{
	Scene *s = lvl1::createScene();
	Director::sharedDirector()->replaceScene(s);
}

void menu::Cred(cocos2d::Ref *pSender)
{
	Scene *s = creditos::createScene();
	Director::sharedDirector()->replaceScene(s);
}

void menu::Quit(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
