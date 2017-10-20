#include "BackgroundLayer.h"
#include "StaticData.h"



BackgroundLayer::BackgroundLayer(void){

}
BackgroundLayer::~BackgroundLayer(void){

}
bool BackgroundLayer::init()//ÏÔÊ¾Í¼Æ¬
{
	if(CCLayer::init()==false)
	{
		return false;
	}
	do 
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		
		CCString *bgName_01 = CCString::createWithFormat(STATIC_DATA_STRING("game_background_01"), 1);   
		CCSprite *bgSprite_01 = CCSprite::create(bgName_01->getCString());
		bgSprite_01->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));

		this->addChild(bgSprite_01);
		return true;
	} while (false);
	return false;
}