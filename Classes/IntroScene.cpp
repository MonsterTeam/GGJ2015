#include "IntroScene.h"
#include "menuScene.h"
#include "cocostudio/CocoStudio.h"

#include "lvl1Scene.h"

USING_NS_CC;
using namespace cocostudio;

Scene* Intro::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Intro::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

//INIT
bool Intro::init()
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

   //Logo Background
    spritelog = Sprite::create("logocolor.png");
    spritelog->setPosition(Vec2(limx/2 + origin.x, limy/2 + origin.y));
	spritelog->setScale(0.8);
    this->addChild(spritelog, 0);
    

    //UPDATE
	this->schedule( schedule_selector(Intro::loadingsStep), 1.0f);
	stepCount=0;
    return true;
}

void Intro::loadingsStep(float dt)
{	
	//Time=1sec
    switch (stepCount)
   {
	case 0:
	// Loading Sprites
	break;
	case 1:
	// Loading Animations
	//ArmatureDataManager::getInstance()->addArmatureFileInfo("armature/bear.ExportJson");

	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("animations/megaman/megaman0.png","animations/megaman/megaman0.plist","animations/megaman/megaman.ExportJson");
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("animations/megaman/megaman1.png","animations/megaman/megaman1.plist","animations/megaman/megaman.ExportJson");
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("animations/megaman/megaman2.png","animations/megaman/megaman2.plist","animations/megaman/megaman.ExportJson");
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("animations/megaman/megaman3.png","animations/megaman/megaman3.plist","animations/megaman/megaman.ExportJson");
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("animations/megaman/megaman4.png","animations/megaman/megaman4.plist","animations/megaman/megaman.ExportJson");
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("animations/megaman/megaman5.png","animations/megaman/megaman5.plist","animations/megaman/megaman.ExportJson");
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("animations/megaman/megaman6.png","animations/megaman/megaman6.plist","animations/megaman/megaman.ExportJson");
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("animations/megaman/megaman7.png","animations/megaman/megaman7.plist","animations/megaman/megaman.ExportJson");
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("animations/megaman/megaman8.png","animations/megaman/megaman8.plist","animations/megaman/megaman.ExportJson");
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("animations/megaman/megaman9.png","animations/megaman/megaman9.plist","animations/megaman/megaman.ExportJson");
	ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("animations/megaman/megaman10.png","animations/megaman/megaman10.plist","animations/megaman/megaman.ExportJson");
	break;		
	case 2:
	// Loading Images
	//CCTextureCache::sharedTextureCache()->addImage("catr.png");
	//Scene *s = menu::createScene();
	Scene *s = lvl1::createScene();
	Director::sharedDirector()->replaceScene(s);
	break;
		
	}
	stepCount++;
}
