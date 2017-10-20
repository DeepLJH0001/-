#include "MenuScene.h"
#include"StaticData.h"
#include"GameMenuLayer.h"
#include "PersonalAudioEngine.h"
using namespace cocos2d;
MenuScene::MenuScene(){


}

MenuScene::~MenuScene(){


}
bool MenuScene::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCScene::init());
		GameMenuLayer* _GameMenuLayer = GameMenuLayer::create();
		_GameMenuLayer->setAnchorPoint(ccp(0.5,0.5));
		this->addChild(_GameMenuLayer);
		PersonalAudioEngine::sharedEngine()->playBackgroundMusic(kEffectBK2);
        bRet = true;
    } while (0);

    return bRet;
}