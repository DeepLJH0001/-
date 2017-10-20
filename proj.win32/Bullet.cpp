#include "Bullet.h"
#include "StaticData.h"
#include "Weapon.h"
#include "FishNet.h"

bool Bullet::init(){
	CCPoint mysize = CCDirector::sharedDirector()->getVisibleSize();

	CCString* Bullet = CCString::createWithFormat(STATIC_DATA_STRING("bullet_frame_format"),5);
	_bulletSprite = CCSprite::createWithSpriteFrameName(Bullet->getCString());
	_bulletSprite->setAnchorPoint(ccp(0.5,0.0));
	addChild(_bulletSprite);
	return true;
}
float Bullet::getSpeed(int type){
	/*switch (type)
	{
	case 0: 
		return 640;
		break;
	case 1: 
		return 640;
		break;
	case 2:
		return 460;
		break;
	case 3:
		return 440;
		break;
	case 4:
		return 420;
		break;
	case 5:
		return 410;
		break;
	case 6:
		return 390;
		break;
	default:
		return 640;
	}*/
	return 1000;	
}
void Bullet::flyTo(CCPoint targetInWordSpace, int type/* = 0*/)
{//发射子弹类
	
	//计算初始位置

	Weapon *weapon = (Weapon*)this->getParent();
	float cannonHeight = 30;//weapon->getCannonSize().height-0;//减去大炮长度,

	CCPoint oldStartWorld = weapon->getPosition();
	//getParent()得到weapon，weapon调用getposition得到的坐标是相对于cannonlayer的，也就是世界坐标
	//CCLog("target world = %f,%f\nold world = %f,%f\n,ccpsub = %f,%f\n",targetInWordSpace.x,targetInWordSpace.y,oldStartWorld.x,oldStartWorld.y,ccpSub(targetInWordSpace,oldStartWorld).x,ccpSub(targetInWordSpace,oldStartWorld).y);
	
	//使用weapon里面shoot to的方法
	CCPoint normalize = ccpNormalize(ccpSub(targetInWordSpace,oldStartWorld));//ccpNormalize得到方向向量
	CCPoint startWorldSpace = ccpAdd(oldStartWorld,ccpMult(normalize,cannonHeight));//oldStartNode+vector
	CCPoint startNodeSpace = getParent()->convertToNodeSpace(startWorldSpace);// weapon坐标从世界坐标得到
	CCPoint targetNodeSpace = getParent()->convertToNodeSpace(targetInWordSpace);//转成相对坐标
	
	//子弹旋转
	float angle = ccpAngleSigned(ccpSub(targetInWordSpace,startWorldSpace),ccp(0,1));
	if(angle>3.14/2 || angle<-3.14/2)
	{
		return;
	}

		setRotation(CC_RADIANS_TO_DEGREES(angle));
	

	this->setPosition(startNodeSpace);
	CCLog("%f,%f",this->getParent()->convertToWorldSpace(startNodeSpace).x,this->getParent()->convertToWorldSpace(startNodeSpace).y);

	CCString *spriteName = CCString::createWithFormat(STATIC_DATA_STRING("bullet_frame_format"),type+1);
	CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteName->getCString());
	
	CCLog(spriteName->getCString());
	
	_bulletSprite->setDisplayFrame(spriteFrame);//更新子弹图片
	
	setVisible(true);

	float speed = getSpeed(type);	
	
	
	CCMoveTo *moveTo = CCMoveTo::create(ccpDistance(targetInWordSpace,startWorldSpace)/speed,targetNodeSpace);//间隔时间，距离/速度
	
	CCCallFunc *callFunc = CCCallFunc::create(this,callfunc_selector(Bullet::end));
	CCSequence *sequence = CCSequence::create(moveTo,callFunc,NULL);
	sequence->setTag(k_Bullet_Action);//设sequence的标签

	
	runAction(sequence);


}
void Bullet::end(){
	stopActionByTag(k_Bullet_Action);//飞行动作停掉
	if(this -> isVisible()){

		setVisible(false);//设置不可见

		CCPoint pos = this->getPosition();
		FishNet *fishNet = (FishNet *)this->getUserObject();
		Weapon *weapon = (Weapon *)this->getParent();
	    fishNet->showAt(pos,weapon->getCannon()->getType());
		fishNet->setVisible(true);
		CCRotateBy* rotate = CCRotateBy::create(1,360);//actionWithDuration(1, 360);
		CCRepeatForever* repeatRotate = CCRepeatForever::create(rotate);
		/*CCSequence* seq =  CCSequence::create(rotate, 
		CCCallFunc::create(this,callfunc_selector(Fish::moveEnd)),
		NULL);*/
	//	CCParticleSystemQuad* _particles = (CCParticleSystemQuad *)fishNet->getUserObject();
	//	_particles->resetSystem();
	/*	stopAction();*/
	}
	

}
CCPoint Bullet::getCollisionPosion(){
	return getParent()->convertToWorldSpace(getPosition());
}