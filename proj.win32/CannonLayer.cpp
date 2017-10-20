#include "CannonLayer.h"
#include "StaticData.h"
#include "Cannon.h"
#include "Weapon.h"
CannonLayer::CannonLayer(void)
{
}


CannonLayer::~CannonLayer(void)
{
}

bool CannonLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	
	do 
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		
		_weapon = Weapon::create();
		//CCLog("%d",this->_weapon->getCannon()->_type);
		//CCLog("%d",this->_weapon->getCannon()->getPosition());
		//_weapon->setAnchorPoint(ccp(0.5,0));
		_weapon->setPosition(ccp(1024,30));
		


		
		CCSprite *addNormalSprite = CCSprite::create(STATIC_DATA_STRING("button_add"));
		//CCLog(STATIC_DATA_STRING("button_add"));
		//CCSprite *addNormalSprite = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING("button_add"));
		CCSprite *addSelectedSprite = CCSprite::create(STATIC_DATA_STRING("button_add"));
	    //CCLog(STATIC_DATA_STRING("button_sub"));
		CCSprite *subNormalSprite = CCSprite::create(STATIC_DATA_STRING("button_sub"));
		CCSprite *subSelectedSprite = CCSprite::create(STATIC_DATA_STRING("button_sub"));
		

		_addItem = CCMenuItemSprite::create(addNormalSprite,addSelectedSprite,this,menu_selector(CannonLayer::switchCannon));
		_subItem = CCMenuItemSprite::create(subNormalSprite,subSelectedSprite,this,menu_selector(CannonLayer::switchCannon));

		
		CCMenu* menu = CCMenu::create(_subItem,_addItem,NULL);
		this->addChild(menu);
		

		//Cannon* cannon = Cannon::create((CannonType)5);//
		//cannon->setPosition(ccp(winSize.width*0.25,30));
		//this->addChild(cannon);

		menu->alignItemsHorizontallyWithPadding(120);//中间的距离
		menu->setPosition(ccp(winSize.width*0.25,35));
		////
		this->addChild(_weapon,15);

		//_weapon->changeCannon(k_Cannon_Operate_Up);
		//_weapon->changeCannon(k_Cannon_Operate_Down);
		return true;
	} while (0);
	
/*
	Cannon *cannon = Cannon::create((CannonType)6);
	cannon->setPosition(ccp(winSize.width*0.5,30));
	this->addChild(cannon);*/

	return false;

}

void CannonLayer::switchCannon(cocos2d::CCObject *sender)//sender传进来是引用对象
{
	if(sender==_addItem){
	_weapon->changeCannon(k_Cannon_Operate_Up);
		//this->aimAt(ccp(100,100));
		//this->aimAt(ccp(1800,200));
	}
	else{
		_weapon->changeCannon(k_Cannon_Operate_Down);
		//this->aimAt(ccp(0,0));
	}
}

void CannonLayer::aimAt(CCPoint target){
	_weapon->aimAt(target);
}
void CannonLayer:: shootTo (CCPoint target){
	_weapon->shootTo(target);
}