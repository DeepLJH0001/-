#include "TouchLayer.h"
#include "GameScene.h"
#include "CannonLayer.h"

USING_NS_CC;
bool TouchLayer::init()
{
	if(!CCLayer::init())
		return false;
	this->setTouchEnabled(true);//���ø���
	this->setTouchPriority(128);
	_gamescene = (GameScene *)this->getParent();
	//CCLog("_gamescene %d",_gamescene);
	//CCLog("guangyan");
	return true;
}

bool TouchLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	//if(this->getGameScene()->is_pause==false){
		this->getGameScene()->cannonAimAt(touch->getLocation());
		//this->getGameScene()->cannonShootTo(touch->getLocation()/*this->locationFromTouch(touch)*/);
	//}
	return true;//return false �������Դ�͸�����¼��������Layer panelLayer�õ���Ӧ
}
void TouchLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	this->getGameScene()->cannonAimAt(touch->getLocation());
}
void TouchLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	this->getGameScene()->cannonShootTo(touch->getLocation()/*this->locationFromTouch(touch)*/);
}

GameScene* TouchLayer::getGameScene()
{
	return (GameScene*)this->getParent();//��ȡ�����ָ��
}


void TouchLayer:: registerWithTouchDispatcher(){
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}