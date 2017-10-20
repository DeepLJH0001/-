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
{//�����ӵ���
	
	//�����ʼλ��

	Weapon *weapon = (Weapon*)this->getParent();
	float cannonHeight = 30;//weapon->getCannonSize().height-0;//��ȥ���ڳ���,

	CCPoint oldStartWorld = weapon->getPosition();
	//getParent()�õ�weapon��weapon����getposition�õ��������������cannonlayer�ģ�Ҳ������������
	//CCLog("target world = %f,%f\nold world = %f,%f\n,ccpsub = %f,%f\n",targetInWordSpace.x,targetInWordSpace.y,oldStartWorld.x,oldStartWorld.y,ccpSub(targetInWordSpace,oldStartWorld).x,ccpSub(targetInWordSpace,oldStartWorld).y);
	
	//ʹ��weapon����shoot to�ķ���
	CCPoint normalize = ccpNormalize(ccpSub(targetInWordSpace,oldStartWorld));//ccpNormalize�õ���������
	CCPoint startWorldSpace = ccpAdd(oldStartWorld,ccpMult(normalize,cannonHeight));//oldStartNode+vector
	CCPoint startNodeSpace = getParent()->convertToNodeSpace(startWorldSpace);// weapon�������������õ�
	CCPoint targetNodeSpace = getParent()->convertToNodeSpace(targetInWordSpace);//ת���������
	
	//�ӵ���ת
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
	
	_bulletSprite->setDisplayFrame(spriteFrame);//�����ӵ�ͼƬ
	
	setVisible(true);

	float speed = getSpeed(type);	
	
	
	CCMoveTo *moveTo = CCMoveTo::create(ccpDistance(targetInWordSpace,startWorldSpace)/speed,targetNodeSpace);//���ʱ�䣬����/�ٶ�
	
	CCCallFunc *callFunc = CCCallFunc::create(this,callfunc_selector(Bullet::end));
	CCSequence *sequence = CCSequence::create(moveTo,callFunc,NULL);
	sequence->setTag(k_Bullet_Action);//��sequence�ı�ǩ

	
	runAction(sequence);


}
void Bullet::end(){
	stopActionByTag(k_Bullet_Action);//���ж���ͣ��
	if(this -> isVisible()){

		setVisible(false);//���ò��ɼ�

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