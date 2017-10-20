#include "LoadingLayer.h"
#include "StaticData.h"
#include "GameScene.h"
#include "FishJoyData.h"
USING_NS_CC;

LoadingLayer::LoadingLayer()
{
	_progressBar = NULL;
	_progressFg = NULL;

	_numSp = 11;//加载到内存总数量
	_loadedSp=0;
}
bool LoadingLayer::init()
{
	if(CCLayer::init()){
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		CCLayerColor* colorBackground  = CCLayerColor::create(ccc4(0,0,0,255));
	    this->addChild(colorBackground );

		this->initProgressBar();
		this->scheduleOnce(schedule_selector(LoadingLayer::cacheInit),0.5f);

        CCSprite* loadingTitle = CCSprite::create("loading_1-ipadhd.png");
		loadingTitle->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.7));
	    this->addChild(loadingTitle);
		
		return true;
	}
	return false;
}
void LoadingLayer::initProgressBar()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite* progressBg = CCSprite::create("loading_4-ipadhd.png");
	_progressFg = CCLabelTTF::create("0/100", "Thonburi", 50);
	_progressFg->setColor(ccc3(0, 0, 0));

	_progressBar = ProgressBar::create(this, CCSprite::create("loading_5-ipadhd.png"));
	_progressBar->setBackground(progressBg);
	_progressBar->setForeground(_progressFg);
	_progressBar->setPosition(CCPointMake(winSize.width*0.5, winSize.height*0.35));
	_progressBar->setSpeed(100.0);
	this->addChild(_progressBar);	
}
void LoadingLayer::progressPercentageSetter(float percent)
{
	CCString *str = CCString::createWithFormat("%d/100",(int)percent);
	_progressFg->setString(str->getCString());
}
void LoadingLayer::loadingFinished()
{
	

	CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	frameCache->addSpriteFramesWithFile(STATIC_DATA_STRING("cannon_plist"));
	frameCache->addSpriteFramesWithFile(STATIC_DATA_STRING("bullet_plist"));
	frameCache->addSpriteFramesWithFile("UI_GameMenuLayer-ipadhd.plist");
	//

	for(int i=1;i<6;i++){
		CCString *s = CCString::createWithFormat(STATIC_DATA_STRING("fish_plist_format"),i) ;
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(STATIC_DATA_STRING(s->getCString()));
		CCLog(STATIC_DATA_STRING(s->getCString()));
	}
	
	char str[][50] = {"SmallFish","Croaker","AngelFish","Amphiprion","PufferS",	
					  "Bream","Porgy","Chelonian","Lantern","Ray","Shark","GoldenTrout",
					  "GShark","GMarlinsFish","GrouperFish","JadePerch","MarlinsFish","PufferB"};

	for(int k = 0;k<18;k++){
		//CCRandom_O_1
		
		CCArray *fish_frame_Array = CCArray::createWithCapacity(STATIC_DATA_INT("fish_frame_count"));//用来储存鱼游动的精灵帧
		CCLog(STATIC_DATA_STRING("fish_frame_count"));
		for(int j=0;j<STATIC_DATA_INT("fish_frame_count");j++){
			CCString *name = CCString::createWithFormat("%s_actor_%03d.png",str[k],j+1);
			CCLog(name->getCString());
			CCSpriteFrame* fish = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString());//每一张小图为精灵帧
			CC_BREAK_IF(!fish);
			fish_frame_Array->addObject(fish);
		}
		CCAnimation *_fish_swing = CCAnimation::createWithSpriteFrames(fish_frame_Array);//内循环精灵帧产生的动画赋值
		_fish_swing->setDelayPerUnit(STATIC_DATA_FLOAT("fish_frame_delay"));//精灵帧延时
		CCString* animationName = CCString::createWithFormat(STATIC_DATA_STRING("fish_animation_format"), k);
		CCAnimationCache::sharedAnimationCache()->addAnimation(_fish_swing,animationName->getCString());
	}
	CCScene *startGameScene = CCTransitionZoomFlipAngular::create(1.0f,GameScene::create());
    CCDirector::sharedDirector()->pushScene(startGameScene);
}
void LoadingLayer::cacheInit(float dt)
{
	CCTextureCache *textureCache = CCTextureCache::sharedTextureCache();
	textureCache->addImageAsync("particle.png",this, callfuncO_selector(LoadingLayer::loading));
	textureCache->addImageAsync(STATIC_DATA_STRING("button_sub"),this,callfuncO_selector(LoadingLayer::loading));
	textureCache->addImageAsync(STATIC_DATA_STRING("button_add"),this, callfuncO_selector(LoadingLayer::loading));
	textureCache->addImageAsync("Item-chaojiwuqi-ipadhd.png",this, callfuncO_selector(LoadingLayer::loading));
	textureCache->addImageAsync("UI_GameMenuLayer-ipadhd.png",this, callfuncO_selector(LoadingLayer::loading));
	textureCache->addImageAsync("FishActor-Large-ipadhd.png",this, callfuncO_selector(LoadingLayer::loading));
	textureCache->addImageAsync("FishActor-Marlin-ipadhd.png",this, callfuncO_selector(LoadingLayer::loading));
	textureCache->addImageAsync("FishActor-Mid-ipadhd.png",this, callfuncO_selector(LoadingLayer::loading));
	textureCache->addImageAsync("FishActor-Shark-ipadhd.png",this, callfuncO_selector(LoadingLayer::loading));
	textureCache->addImageAsync("cannon-ipadhd.png",this, callfuncO_selector(LoadingLayer::loading));
	textureCache->addImageAsync("FishActor-Small-ipadhd.png",this, callfuncO_selector(LoadingLayer::loading));
	textureCache->addImageAsync("ui_button_music_1-ipadhd.png",this, callfuncO_selector(LoadingLayer::loading));
}
void LoadingLayer::loadingPList(CCObject *sender)
{
	CCTexture2D *texture2d =  (CCTexture2D *) sender;
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("",texture2d);
}
void LoadingLayer::loading(CCObject *sender)
{
	_loadedSp++;
	float progress = 100.0 * _loadedSp / _numSp ;
	_progressBar->progressTo(progress);
}