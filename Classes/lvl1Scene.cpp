#include "lvl1Scene.h"
#include "creditosScene.h"

#include "cocostudio/CocoStudio.h"
#include "MyBodyParser.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace cocostudio;

lvl1::lvl1()	{
	//TOUCH
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(lvl1::onTouchBegan, this);
	//listener->onTouchMoved = CC_CALLBACK_2(lvl1::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

lvl1::~lvl1()	{
}

Scene* lvl1::createScene()
{
// 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f, -300.0f));
	scene->getPhysicsWorld()->setSpeed(2.2);
    // 'layer' is an autorelease object
    auto layer = lvl1::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld() );

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

//INIT
bool lvl1::init()
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
	//UPDATE
	this->schedule(schedule_selector(lvl1::update));
	//TOUCH
	this->setTouchEnabled(true);
	// EVENT COLLISION
	auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(lvl1::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	// CAN JUMP
	canJump=false;

	//Music - Brackground
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("theme.3ga",true);

    //BACKGROUND
    background = Sprite::create("lvls/baseB.png");
    background->setPosition(Vec2(10*limx/2, limy/2));
    this->addChild(background, 0);
	// LEVEL
    MyBodyParser::getInstance()->parseJsonFile( "lvls/lvl0.json" );
    backgroundPhy = MyBodyParser::getInstance()->bodyFormJson(background, "lvl", PhysicsMaterial( 1, 0, 0 ) );
    if ( backgroundPhy != nullptr )
    {
        backgroundPhy->setDynamic( true );
        background->setPhysicsBody( backgroundPhy );
    }
	backgroundPhy->setCollisionBitmask(2);
	backgroundPhy->setContactTestBitmask(1);
    backgroundPhy->setVelocity(Vect(-250, 0));
	backgroundPhy->setRotationEnable(false);
	backgroundPhy->setGravityEnable(false);
	backgroundPhy->setGroup(0);
	 //BACKOBJ
    background2 = Sprite::create("lvls/baseB.png");
    background2->setPosition(Vec2(10*limx/2, limy/2));
	background2->setVisible(false);
    this->addChild(background2, 0);

	MyBodyParser::getInstance()->parseJsonFile( "lvls/lvl0.json" );
    backgroundPhy2 = MyBodyParser::getInstance()->bodyFormJson(background2, "obj", PhysicsMaterial( 1, 0, 0 ) );
    if ( backgroundPhy2 != nullptr )
    {
        backgroundPhy2->setDynamic( true );
        background2->setPhysicsBody( backgroundPhy2 );
    }
	backgroundPhy2->setCollisionBitmask(3);
	backgroundPhy2->setContactTestBitmask(1);
    backgroundPhy2->setVelocity(Vect(-250, 0));
	backgroundPhy2->setRotationEnable(false);
	backgroundPhy2->setGravityEnable(false);
	backgroundPhy2->setGroup(0);

	// Create general Edge Body
	auto edgeBody = PhysicsBody::createEdgeBox( Size(limx*100,limy+10), PHYSICSBODY_MATERIAL_DEFAULT, 3 );
    auto edgeNode = Node::create();
    edgeNode ->setPosition( Point( limx/2, limy/2 ) );
    edgeNode->setPhysicsBody( edgeBody );
    this->addChild( edgeNode );
		//Collision edgeBody
	edgeBody->setCollisionBitmask(1);
	edgeBody->setContactTestBitmask(0);

	//POWERS MENU
	auto earthB = MenuItemImage::create("elementales/eTierra.jpg",
                                           "elementales/eTierra.jpg",CC_CALLBACK_1(lvl1::earth,this));
	auto windB = MenuItemImage::create("elementales/eViento.jpg",
                                           "elementales/eViento.jpg",CC_CALLBACK_1(lvl1::wind,this));
	auto waterB = MenuItemImage::create("elementales/eAgua.jpg",
                                           "elementales/eAgua.jpg",CC_CALLBACK_1(lvl1::water,this));
	auto fireB = MenuItemImage::create("elementales/eFuego.jpg",
                                           "elementales/eFuego.jpg",CC_CALLBACK_1(lvl1::fire,this));

	earthB->setPosition(Point(limx/10,9*limy/10));
	earthB->setScale(0.1);
	windB->setPosition(Point(limx/10,7*limy/10));
	windB->setScale(0.1);
	waterB->setPosition(Point(limx/10,5*limy/10));
	waterB->setScale(0.1);
	fireB->setPosition(Point(limx/10,3*limy/10));
	fireB->setScale(0.1);

	auto menu = Menu::create(earthB, windB, waterB, fireB,NULL);
	menu->setPosition(Point(0,0));
	this->addChild(menu,1);
	//VAR POWERS
	isEarth=false;
	isWind=false;
	isWater=false;
	isFire=false;

	//ANIMATIONS
	megaman=Armature::create("megaman");
	megaman->getAnimation()->playByIndex(0);
	megaman->setPosition(Vec2(limx/4, limy/2));
	megaman->setScale(0.3);
	addChild(megaman,1);

	
    //Physic Bodys
	megamanPhy = PhysicsBody::createBox( Size(megaman->getContentSize( ).width /4.2,megaman->getContentSize( ).height/4.2), PhysicsMaterial( 0, 0, 0 ) );
    megaman->setPhysicsBody( megamanPhy );
		//Collision edgeBody
	megamanPhy->setCollisionBitmask(7);
	megamanPhy->setContactTestBitmask(1);
	megamanPhy->setRotationEnable(false);
	megamanPhy->setVelocityLimit(350);
    return true;
}

void lvl1::update(float dt)	{
	float megaDieX = megaman->getPositionX();
	if(megaDieX < limx/4.5 )	{
	Scene *s = lvl1::createScene();
	Director::sharedDirector()->replaceScene(s);
	} /*else if (megaDieX > limx/3.5)	{
		megaman->runAction(MoveTo::create(0.05,Vec2(limx/4,megaman->getPositionY())));
	}*/
	// RESCALE SIZE WIND - WATER
	if (isWind==false && isWater==false)	{
	megaman->setScale(0.3);
	}
	//SET OBJ
	if (isEarth==false)	{
	backgroundPhy2->setEnable(true);
	}
}

bool lvl1::onTouchBegan(Touch* touch, Event* event) {
	if(canJump)	{
	if(isWind==false)	{
	canJump=false;
	}
	if(isEarth==true)	{
	megamanPhy->setVelocity(Vec2(0,150));
	}	else if (isWind==true)	{
	megamanPhy->setVelocity(Vec2(0,110));
	} else if (isWater==true)	{
	megamanPhy->setVelocity(Vec2(0,300));
	}else	{
	megamanPhy->setVelocity(Vec2(0,220));
	}
	}
	return true;
}

bool lvl1::onContactBegin(cocos2d::PhysicsContact &contact)
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    
    // Dude with scenario movil
    if ( ( 2 == a->getCollisionBitmask() && 7 == b->getCollisionBitmask() ) || (7 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask() ) )
    {
		canJump=true;
    }
	// Border with dude
    if ( ( 1 == a->getCollisionBitmask() && 7 == b->getCollisionBitmask() ) || (7 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask() ) )
    {
	Scene *s = lvl1::createScene();
	Director::sharedDirector()->replaceScene(s);
    }
	// OBJ with dude EARTH POWER
	if(isEarth==false)	{
    if ( ( 3 == a->getCollisionBitmask() && 7 == b->getCollisionBitmask() ) || (7 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask() ) )
    {
	Scene *s = lvl1::createScene();
	Director::sharedDirector()->replaceScene(s);
    }
	}
    return true;
}

void lvl1::earth(cocos2d::Ref *pSender)
{
	isEarth=true;
	isWind=false;
	isWater=false;
	isFire=false;

	// AVOID OBJ
	megaman->getAnimation()->playByIndex(1);
}

void lvl1::wind(cocos2d::Ref *pSender)
{
	isWind=true;
	isEarth=false;
	isWater=false;
	isFire=false;
	// FLY!
	canJump=true;
	megaman->setScale(0.5);
	megaman->getAnimation()->playByIndex(2);
}
void lvl1::water(cocos2d::Ref *pSender)
{
	isWater=true;	
	isWind=false;
	isEarth=false;
	isFire=false;
	//WAAAATER
	megaman->setScale(0.15);
}
void lvl1::fire(cocos2d::Ref *pSender)
{
	isFire=true;
	isWater=false;	
	isWind=false;
	isEarth=false;
}
