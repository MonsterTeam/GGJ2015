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
	scene->getPhysicsWorld()->setSpeed(2.5);
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

    //BackGround
    background = Sprite::create("lvls/baseB.png");
    background->setPosition(Vec2(10*limx/2, limy/2));
    this->addChild(background, 0);
	// LEVEL
    MyBodyParser::getInstance()->parseJsonFile( "lvls/lvl0.json" );
    auto backgroundPhy = MyBodyParser::getInstance()->bodyFormJson(background, "lvl", PhysicsMaterial( 999, 0, 0 ) );
    if ( backgroundPhy != nullptr )
    {
        backgroundPhy->setDynamic( true );
        background->setPhysicsBody( backgroundPhy );
    }
	backgroundPhy->setCollisionBitmask(2);
	backgroundPhy->setContactTestBitmask(true);
    backgroundPhy->setVelocity(Vect(-250, 0));
	backgroundPhy->setRotationEnable(false);

	//ANIMATIONS
	megaman=Armature::create("megaman");
	megaman->getAnimation()->playByIndex(0);
	megaman->setPosition(Vec2(limx/4, limy/2));
	megaman->setScale(0.5);
	addChild(megaman,1);

	// Create general Edge Body
	auto edgeBody = PhysicsBody::createEdgeBox( Size(limx*100,limy), PHYSICSBODY_MATERIAL_DEFAULT, 3 );
    auto edgeNode = Node::create();
    edgeNode ->setPosition( Point( limx/2, limy/2 ) );
    edgeNode->setPhysicsBody( edgeBody );
    this->addChild( edgeNode );
		//Collision edgeBody
	edgeBody->setCollisionBitmask(1);
	edgeBody->setContactTestBitmask(true);
	
    //Physic Bodys
	megamanPhy = PhysicsBody::createBox( Size(megaman->getContentSize( ).width / 3,megaman->getContentSize( ).height/3), PhysicsMaterial( 0, 0, 0 ) );
    megaman->setPhysicsBody( megamanPhy );
		//Collision edgeBody
	megamanPhy->setCollisionBitmask(7);
	megamanPhy->setContactTestBitmask(true);
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
}

bool lvl1::onTouchBegan(Touch* touch, Event* event) {
	if(canJump)	{
	canJump=false;
	megamanPhy->setVelocity(Vec2(0,250));
    
	}
	return true;
}

bool lvl1::onContactBegin(cocos2d::PhysicsContact &contact)
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    
    // Border with dude
    if ( ( 1 == a->getCollisionBitmask() && 7 == b->getCollisionBitmask() ) || (7 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask() ) )
    {
	Scene *s = lvl1::createScene();
	Director::sharedDirector()->replaceScene(s);
    }
    // Dude with scenario movil
    if ( ( 2 == a->getCollisionBitmask() && 7 == b->getCollisionBitmask() ) || (7 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask() ) )
    {
		canJump=true;
    }
    return true;
}