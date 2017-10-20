#include"Cannon.h"

Cannon::Cannon(void ){

}
Cannon::~Cannon(void){
	CC_SAFE_RELEASE_NULL(_cannonSprites);
}
bool Cannon::init(CannonType type /*= k_Cannon_Type_1*/){

	//CC_BREAK_IF
	if(!CCNode::init())
		return false;
	
	_cannonSprites = CCArray::createWithCapacity(k_Cannon_Count);
	CC_SAFE_RETAIN(_cannonSprites);
	CCPoint anchroPoint = CCPoint(0.5,0.5);
	for(int i=0;i<k_Cannon_Count;i++){
		CCString* Cannon_frame_name = CCString::createWithFormat(STATIC_DATA_STRING("cannon_frame_format"),i+1);
		CCSprite* Cannon_Sprite = CCSprite::createWithSpriteFrameName(Cannon_frame_name->getCString());
		Cannon_Sprite->setTag(i);
		CC_BREAK_IF(!Cannon_Sprite);
		Cannon_Sprite->setAnchorPoint(anchroPoint);
		_cannonSprites->addObject(Cannon_Sprite);
	}
	setType(type);
	//CCAnimation* cannon_animation = CCAnimation::createWithSpriteFrames(_cannonSprites);
	//cannon_animation->setDelayPerUnit(1.5);
	CC_SAFE_RETAIN(_cannonSprites);
	//CCAnimationCache::sharedAnimationCache()->addAnimation
	return true;
}
void Cannon::setType(CannonType type){
	if(type==_type){
		return;
	}
	if(type<k_Cannon_Type_1){
		type = k_Cannon_Type_7;
	}
	else if(type>k_Cannon_Type_7){
		type = k_Cannon_Type_1;
	}
	CCSprite* sprite = (CCSprite*)_cannonSprites->objectAtIndex(type);
	this->removeChildByTag(_type);
	this->addChild(sprite);
	_type = type;
}
CannonType Cannon::getType()
{
	//在weapon中创建cannon时new cannon而不是用_cannon，导致后面weapon->_cannon为空，在这里报错
	return _type;
}
 Cannon* Cannon::create(CannonType type/*=k_Cannon_Type_1*/){
	Cannon* cannon = new Cannon();
	cannon->init(type);
	cannon->autorelease();
	return cannon;
}
float Cannon::getFireRange(){
	return 300*(_type+1);
}
CCSize Cannon::getSize(){
	CCSprite* sprite =  (CCSprite*)_cannonSprites->objectAtIndex(_type);

	return sprite->getContentSize();
}
void Cannon::aimAt(cocos2d::CCPoint target){
	CCPoint cannonPosition = getParent()->convertToWorldSpace(getPosition());//获得炮台的坐标
	float angle = ccpAngleSigned(ccpSub(target,cannonPosition),ccp(0,1));//算得弧度

	if (angle > 1.5 || angle < -1.5)
	{
		return;
	}

	this->setRotation(CC_RADIANS_TO_DEGREES(angle));//弧度变成角度

}