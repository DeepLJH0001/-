#include "GoldCounterLayer.h"
#define NUM_COUNTER 7

GoldCounterLayer::GoldCounterLayer(){
	_number =0;
}
GoldCounterLayer::~GoldCounterLayer(){

}
GoldCounterLayer* GoldCounterLayer::create(int number){
	GoldCounterLayer *gold = new GoldCounterLayer();
	if(gold && gold->init(number)){
		gold->autorelease();
		return gold;
	}
	else{
		CC_SAFE_DELETE(gold);
		return NULL;
	}
	
}
bool GoldCounterLayer::init(int number){
	if(!CCNode::init()){
		return false;
	}
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("ui_text_01-ipadhd.png");
	CCSize size = texture->getContentSize();
	for (int i = 0;i<NUM_COUNTER;i++)
	{
		float width = size.width/10;
		CCArray *presenters = CCArray::createWithCapacity(10);
		for(int j=0;j<10;j++){
			CCSprite *sprite = CCSprite::createWithTexture(texture,
								CCRectMake(j*width,0,width,size.height));
								presenters->addObject(sprite);
								
		}
		Counter *counter = Counter::create(presenters);
		this->addChild(counter,0,i);
		counter->setTag(i);
		//counter->setChildTag(i);
		counter->setPosition(ccp(i*35,0));
	}
	setNumber(number);
	return true;
}
void GoldCounterLayer::setNumber(int number, int ceiling/*=9999999*/){
	number = MIN(number,ceiling);
	number = MAX(number,0);
	for(int i=NUM_COUNTER-1 ;i>=0;i--){
		Counter *counter = (Counter *)this->getChildByTag(i);
		//获取到的counter是空的记得settag
		//CCLog("number = %d",counter->getDigit());
		counter->setDigit(number%10);
		number/=10;
		//CCLog("number = %d",number);
	}
}