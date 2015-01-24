#include "creditosScene.h"
#include "menuScene.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* creditos::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = creditos::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

//INIT
bool creditos::init()
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

	//creditos Content
	auto menu_item_1 = MenuItemImage::create("CloseNormal.png",
                                           "CloseNormal.png",CC_CALLBACK_1(creditos::goMenu,this));

	menu_item_1->setPosition(Point(limx/2+225,(limy/4)*3-20));

	auto menu = Menu::create(menu_item_1, NULL);
	menu->setPosition(Point(0,0));
	this->addChild(menu,1);

   
    return true;
}

void creditos::goMenu(cocos2d::Ref *pSender)
{
	Scene *s = menu::createScene();
	Director::sharedDirector()->replaceScene(s);
}

