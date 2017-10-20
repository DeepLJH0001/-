#include "FishNet.h"
#include "StaticData.h"
bool FishNet::init(){
		CCString *fileName = CCString::createWithFormat(STATIC_DATA_STRING("net_frame_format"),1);
        _fishNetSprite = CCSprite::createWithSpriteFrameName(fileName->getCString());
		addChild(_fishNetSprite);
		return true;
}
CCRect FishNet::getCollisionArea()
{
	CCPoint origin = this->getParent()->convertToWorldSpace(this->getPosition());
	CCSize defaultSize = _fishNetSprite->getContentSize();
    float scale = this->getScale();
    CCSize size = CCSizeMake(defaultSize.width*scale, defaultSize.height*scale);
    return CCRectMake(origin.x-size.width*0.5, origin.y-size.height*0.5, size.width, size.height);
}
void FishNet::showAt(CCPoint pos,int type /*= 0*/){
	
	this->setPosition(pos);
	this->setVisible(true);
	//改变的渔网图片
	CCString *spriteName=CCString::createWithFormat(STATIC_DATA_STRING("net_frame_format"),type+1);
	CCSpriteFrame *spriteFrame=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteName->getCString());
	_fishNetSprite->setDisplayFrame(spriteFrame);
	
	//粒子
	CCParticleSystemQuad *_particle=(CCParticleSystemQuad*)this->getUserObject();
	_particle->setPosition(pos);
	_particle->resetSystem();//重设粒子系统

	this->stopAllActions();

	

	CCDelayTime *delayTime= CCDelayTime::create(1.0);
	CCRotateBy* rotate = CCRotateBy::create(1,360);//actionWithDuration(1, 360);
	CCBlink *b = CCBlink::create(1.0,2);
	CCHide *hide= CCHide::create();
	CCSequence *s = CCSequence::create(delayTime,hide,NULL);
	CCSequence *sequence= CCSequence::create(delayTime,s,NULL);
	/*CCActionInterval* ripple = CCRipple3D::create(5, CCSize(100, 100), this->getPosition(), 240, 4, 160); 
	CCActionInterval* shatteredTiles = CCShatteredTiles3D::create(15, CCSize(10, 10), 50, true); 
    runAction(shatteredTiles); */
	runAction(s);

}