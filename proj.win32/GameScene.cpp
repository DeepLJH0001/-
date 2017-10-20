#include"GameScene.h"
#include"StaticData.h"
#include"BackgroundLayer.h"
#include"Fish.h"
#include"FishNet.h"
#include"FishLayer.h"
#include"CannonLayer.h"
#include "FishJoyData.h"
#include "cocos-ext.h"
#include "PersonalAudioEngine.h"

using namespace cocos2d;
using namespace cocos2d::ui;
USING_NS_CC_EXT;
static CCLabelTTF* pLabel;
GameScene::GameScene(){
	PersonalAudioEngine::sharedEngine()->pauseAllEffects();
	//PersonalAudioEngine::sharedEngine()->pauseBackgroundMusic();
	//PersonalAudioEngine::sharedEngine()->playBackgroundMusic(kEffectBK);;//完成音效资源的预加载；
}
GameScene::~GameScene(){
	CC_SAFE_RELEASE(_pausemenu);
}


bool GameScene::init(){
	 bool bRet = false;
    do 
    {
      

        CC_BREAK_IF(! CCScene::init());

		gold = 0;
		is_music = true;
        CCSize size = CCDirector::sharedDirector()->getWinSize();
      
		

	    background = BackgroundLayer::create();
		CC_BREAK_IF(!background);
		addChild(background,0);

		//preloadResources();

		/*Fish* fish = Fish::create();
		fish->setPosition(ccp(300,300));
		this->addChild(fish);*/
		 _fishLayer = FishLayer::create();
		this->addChild(_fishLayer);
	    

		//下面是读取cocostudio场景
		_panelayer = PanelLayer::create();
		this->addChild(_panelayer);

		

		/*Widget *widget=GUIReader::shareReader()->widgetFromBinaryFile("NewUi_1.csb");
		TouchGroup *touchGrounp=TouchGroup::create();
		touchGrounp->addWidget(widget);
		addChild(touchGrounp,1);
		Button *btnPause=(Button*) UIHelper::seekWidgetByName(widget,"btnPause");
		if(btnPause==NULL){
		    return false;
		}*/
		
		//btnPause->addTouchEventListener(this,toucheventselector(PanelLayer::pauseCallback));

		
		_cannonLayer = CannonLayer::create();
		_cannonLayer->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/4,50));
		this->addChild(_cannonLayer,10);
		_touchlayer = TouchLayer::create();
		_touchlayer->setTouchPriority(-128);
		addChild(_touchlayer);
		_pausemenu = PauseMenu::create();//CCTransitionSlideInL::create(1.0,PauseMenu::create());
		CC_SAFE_RETAIN(_pausemenu);

		int goldNum = FishJoyData::sharedFishJoyData()->getGold();
		CCLog("data from XML %d\n",goldNum);
		//_panelayer->getGoldCounterLayer()->setNumber(goldNum);
		this->gold = goldNum;
		GoldCounterLayer *gold_counter = (GoldCounterLayer *)this->_panelayer->getChildByTag(1);
		gold_counter->setNumber(goldNum);

		scheduleUpdate();
		pLabel = CCLabelTTF::create(gb23122utf8("******"), "Marker Felt", 80);
		pLabel->setColor(ccc3(0,255,0));
	    pLabel->setPosition(ccp(2548,700));
	    //this->addChild(pLabel, 200);
		ccBezierConfig cfg;
		//-512.000000 554.501526 -1536.000000 -554.501526 -2048.000000 17.489624
		cfg.controlPoint_1 = ccp(512.000000,554.501526);
		cfg.controlPoint_2 = ccp(-1536.000000,-554.501526);
		cfg.endPosition = ccp(-2048.000000,209);
		float time = 10.0f;
		CCBezierBy* bezierForward = CCBezierBy::create(time, cfg);
		CCSequence* seq =  CCSequence::create(bezierForward, 
		CCCallFunc::create(this,callfunc_selector(GameScene::NameMove)),
		NULL);
		pLabel->runAction(seq);
		//CCMoveTo move_no = CCMoveTo(1024/200,);
        bRet = true;
    } while (0);
	
    return bRet;
}
void GameScene::preloadResources(void){
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("static_data.plist");
	
	
	CCTextureCache *textureCache = CCTextureCache::sharedTextureCache();
	textureCache->addImage(STATIC_DATA_STRING("button_add"));
	textureCache->addImage(STATIC_DATA_STRING("button_sub"));


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
}
void GameScene::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
	CCDirector::sharedDirector()->popScene();
}

void GameScene::pause(){

	PersonalAudioEngine::sharedEngine()->pauseAllEffects();
	PersonalAudioEngine::sharedEngine()->pauseBackgroundMusic();
	//PersonalAudioEngine::sharedEngine()->playEffect(kEffectPause);
	this->operateAllSchedulerAndActions(this, k_Operate_Pause);
	CCPageTurn3D *_3d = CCPageTurn3D::create(1.0f,CCDirector::sharedDirector()->getWinSize());
	//runAction(_3d);
	CCFadeOutUpTiles *fade = CCFadeOutUpTiles::create(1.0f,_pausemenu->getContentSize());
	CCDelayTime *delay = CCDelayTime::create(1.0f);
	CCSequence *seq = CCSequence::create(delay,fade,NULL);
	//_pausemenu->runAction(seq);
	
	this->addChild(_pausemenu,20);
	//_pausemenu->runAction(seq);
}
void GameScene::resume(){
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("baoshiyu_shuzi_02-ipadhd.png");
	CCSize size = texture->getContentSize();
	float width = size.width/10;

	_label = CCLabelAtlas::create("3","baoshiyu_shuzi_02-ipadhd.png",width,size.height,'0');
	_label->setAnchorPoint(ccp(0.5,0.5));
	_label->setScale(6.0f);
	addChild(_label,99);
	//_label->setPosition(ccp(1024,768));
	_countDown = ScheduleCountDown::create(this,2,false); 
	//addChild(_countDown,99);

	CCDelayTime *delaytime = CCDelayTime::create(3.0f);
	CCSequence  *seq = CCSequence::create(CCCallFunc::create(this,callfunc_selector(GameScene::resume_callFunc)),NULL);
	runAction(seq);
	this->removeChild(_pausemenu);

	
    
}
void GameScene::resume_callFunc(){

	this->operateAllSchedulerAndActions(this, k_Operate_Resume);
	
	this->_label->setVisible(false);
	if(this->is_music == true){
	PersonalAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	//PersonalAudioEngine::sharedEngine()->resumeBackgroundMusic();
	//PersonalAudioEngine::sharedEngine()->resumeBackgroundMusic();
	//PersonalAudioEngine::sharedEngine()->resumeAllEffects();
}
void GameScene::operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag)
{
    if(node->isRunning()){
        switch (flag) {
            case k_Operate_Pause:
                node->pauseSchedulerAndActions();//node类的暂停Actions操作
                break;
            case k_Operate_Resume:
                node->resumeSchedulerAndActions();//node类的恢复Actions操作
                break;
            default:
                break;
        }
        CCArray* array = node->getChildren();//递归遍历他的子节点
        if(array != NULL && array->count()>0){//当为空的时候跳出，不为空进入遍历子节点
            CCObject* iterator;
            CCARRAY_FOREACH(array, iterator){
                CCNode* child = (CCNode*)iterator;
                this->operateAllSchedulerAndActions(child, flag);
            }
        }
    }
}

void GameScene::cannonAimAt(CCPoint point){
	_cannonLayer->aimAt(point);
}
void GameScene::cannonShootTo(CCPoint point){
	_cannonLayer->shootTo(point);
	PersonalAudioEngine::sharedEngine()->playEffect(kEffectShoot);
}

bool GameScene::checkOutCollisionBetweenFishesAndBullet(Bullet *bullet){
	
	CCPoint collosionpoint = bullet->getCollisionPosion();
	CCObject *object = NULL;
	CCArray *fishArray = _fishLayer->getFishes();
	//FishNet *FishNet = (FishNet *)bullet->getUserData(); 
	CCARRAY_FOREACH(fishArray,object){
		Fish *fish = (Fish *)object;
		
		if (fish->isRunning())//鱼要先判断是否在鱼层中
		{
			CCRect rect = fish->getCollisionArea();
				if(rect.containsPoint(collosionpoint)){
					bullet->end();
					return true;
				}
		}
	}
	return false;
}


void GameScene::fishWillBeCaught(Fish *fish){
	PersonalAudioEngine::sharedEngine()->playEffect(kEffectFishNet);

	int type = _cannonLayer->_weapon->getCannonType();
	CCString *weaponPerFormat = CCString::createWithFormat(STATIC_DATA_STRING("weapon_percentage_format"),type);
	float weaponPer = STATIC_DATA_FLOAT(weaponPerFormat->getCString());
	//读不出来老师文档的plist少一个空格 CCString *fishPerFormat = CCString::createWithFormat(STATIC_DATA_STRING(" fish _percentage_format"),(int)fish->getFishType());
	CCString *fishPerFormat = CCString::createWithFormat(" fish _percentage_%d",(int)fish->getFishType()/3+1);//一共18种鱼，而概率只有6种，果断除3 且不为0，加1
	float fishPer = STATIC_DATA_FLOAT(fishPerFormat->getCString());
	CCLog("武器概率:%f 鱼的概率:%f fish type:%d fishPerFormat%s",weaponPer,fishPer,fish->getFishType(),fishPerFormat);
	if(fishPer * weaponPer >CCRANDOM_0_1() && fish->_beCaught==false){ //武器和鱼的乘积大于1
		fish->beCaught();
		int fishtype = fish->getFishType();
		CCString *fish = CCString::createWithFormat(STATIC_DATA_STRING("reward_format"),fishtype);
		int reward = STATIC_DATA_INT(fish->getCString());//?没有plist
		int score = 5*fishtype;//5倍鱼type金币奖励
		alterGold(score);
	}
}

void GameScene::checkOutCollisionBetweenFishesAndFishingNet(Bullet *bullet){
	CCObject *object = NULL;
	CCArray *fishArray = _fishLayer->getFishes();
	//FishNet *FishNet = (FishNet *)bullet->getUserData(); 
	CCARRAY_FOREACH(fishArray,object){
		Fish *fish = (Fish *)object;
		
		if (fish->isRunning())//鱼要先判断是否在鱼层中
		{
			if (fish->getCollisionArea().intersectsRect(_cannonLayer->_weapon->getCollisionArea(bullet)))
			{		
				CCLOG("fishWillBeCaught");
				fishWillBeCaught(fish);
			}
		}
	}
}
void GameScene::checkOutCollision(){

	CCArray *bulletArray = _cannonLayer->_weapon->_bullets;
	CCObject *object = NULL;
	CCARRAY_FOREACH(bulletArray,object){
		Bullet *bullet =  (Bullet *)object;
		if(bullet->isVisible()){
			if (checkOutCollisionBetweenFishesAndBullet(bullet))//判断子弹和鱼发生了碰撞之后。马上处理渔网和鱼的碰撞
			{
				checkOutCollisionBetweenFishesAndFishingNet(bullet);
			}
		}

	}

}
void GameScene::update(float delta){
	checkOutCollision();
}
void GameScene::alterGold(int delta){
	//_panelayer->removeChildByTag(1);
	GoldCounterLayer *gold_counter = (GoldCounterLayer *)this->_panelayer->getChildByTag(1);
	this->gold+=delta;
	CCLog("当前金币值=%d",this->gold);
	//GoldCounterLayer *gold_counter = GoldCounterLayer::create(this->gold);
	gold_counter->setNumber(this->gold);
	gold_counter->setPosition(585,40);
//	this->_panelayer->addChild(gold_counter,99,1);
	//setGold
}

void GameScene::scheduleTimeUp(){
	CCLog("time up");
	if(_countDown->getLoop()==false){
		removeChild(_countDown);
	}
}

void GameScene::setScheduleNumber(int number){
	CCString *str = CCString::createWithFormat("%d",number);
	_label->setString(str->getCString());
}

const char* GameScene::gb23122utf8(const char* gb2312)      
{    
    int len = MultiByteToWideChar(0, 0, gb2312, -1, NULL, 0);      
    wchar_t* wstr = new wchar_t[len+1];      
    memset(wstr, 0, len+1);      
    MultiByteToWideChar(0, 0, gb2312, -1, wstr, len);      
    len = WideCharToMultiByte(65001, 0, wstr, -1, NULL, 0, NULL, NULL);      
    char* str = new char[len+1];  
    memset(str, 0, len+1);      
    WideCharToMultiByte(65001, 0, wstr, -1, str, len, NULL, NULL);      
    if(wstr) delete[] wstr;      
    return str;  
}    

void GameScene::NameMove(){
	pLabel->setString(gb23122utf8("贝塞尔曲线 "));
	CCHide *hide = CCHide::create();
	CCDelayTime *delayTime = CCDelayTime::create(1.0);
	CCBlink *blink = CCBlink::create(1.0,5);
	CCSequence *seq = CCSequence::create(delayTime, blink, 
		CCCallFunc::create(this,callfunc_selector(GameScene::NameEnd)),delayTime,NULL);
	pLabel->runAction(seq);
	
}
void GameScene::NameEnd(){
	pLabel->setString(gb23122utf8("实现中文gbk到Utf-8"));
	//removeChild(pLabel);
	CCSequence *seq = CCSequence::create(CCDelayTime::create(1.0f),CCCallFunc::create(this,callfunc_selector(GameScene::NameFade)),NULL);
	pLabel->runAction(seq);
}
void GameScene::NameFade(){
	removeChild(pLabel);
}