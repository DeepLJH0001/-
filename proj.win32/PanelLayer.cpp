#include "PanelLayer.h"
#include "GameScene.h"
#include "GoldCounterLayer.h"
#include "PersonalAudioEngine.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocos2d::extension;
PanelLayer::PanelLayer(){
		   
}
PanelLayer::~PanelLayer(){
		   
}
bool PanelLayer::init(){
      bool bRet = false;
	  
	  do{
		//加载菜单  
		CC_BREAK_IF(!CCLayer::init());
		Widget *widget=GUIReader::shareReader()->widgetFromBinaryFile("NewUi_1.csb");
		TouchGroup *touchGrounp=TouchGroup::create();
		touchGrounp->addWidget(widget);
		addChild(touchGrounp,1);
		//touchGrounp->setTouchPriority(-128);//提高权限越小越大
		//this->mTouchPriporty 
		Button *btnPause_ui=(Button*) UIHelper::seekWidgetByName(widget,"btnPause");
		
		CCSprite *btnPause1 = CCSprite::createWithSpriteFrameName("ui_button_01.png");//CCmeunitem的方法提高权限
		CCSprite *btnPause2 = CCSprite::createWithSpriteFrameName("ui_button_02.png");
		CCMenuItemSprite *sence_Menu_Item = CCMenuItemSprite::create(
			 btnPause1,
			 btnPause2,
			 this,
			 menu_selector(PanelLayer::pauseCallback)
			 );
		CCMenu *Pause_Menu = CCMenu::create(sence_Menu_Item,NULL);
		Pause_Menu->setPosition(btnPause_ui->getPosition());
		this->addChild(Pause_Menu);
		//btnPause->setTouchPriority(0);
		//btnPause->mTouchPriporty  
		if(btnPause_ui==NULL){
		    return false;
		}
		 CCMenuItemImage *sence_Menu_Item_Music = CCMenuItemImage::create(
            "ui_button_music_1-ipadhd.png",
            "ui_button_music_1-ipadhd.png",
            this,
            menu_selector(PanelLayer::MusicCallback));
        CC_BREAK_IF(! sence_Menu_Item_Music);

        // Place the menu item bottom-right conner.
		sence_Menu_Item_Music->setPosition(ccp(btnPause_ui->getPosition().x+195,btnPause_ui->getPosition().y));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(sence_Menu_Item_Music, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

       
		//CCSprite *btnMusic1 = CCSprite::create("ui_button_music_1-ipadhd.png");//CCmeunitem的方法提高权限
		//CCSprite *btnMusic2 = CCSprite::create("ui_button_music_1-ipadhd.png");
		//CCMenuItemImage *sence_Menu_Item_Music = CCMenuItemImage::create(
		//	 "ui_button_music_1-ipadhd.png",
		//	 "ui_button_music_1-ipadhd.png",
		//	 this,
		//	 menu_selector(PanelLayer::pauseCallback)
		//	 );
		//CCMenu *Pause_Menu_Music = CCMenu::create(sence_Menu_Item_Music,NULL);
		//Pause_Menu_Music->setPosition(ccp(1024,1024));
		//this->addChild(sence_Menu_Item_Music);
		//btnPause->setTouchPriority(0);
		//btnPause->mTouchPriporty  
		if(btnPause_ui==NULL){
		    return false;
		}
		
		//btnPause->addTouchEventListener(this,toucheventselector(PanelLayer::pauseCallback));
		GoldCounterLayer *gold = GoldCounterLayer::create(0000000);
		this->addChild(gold,99,1);//tag=1
		gold->setPosition(585,40);

		//CCSize size = CCDirector::sharedDirector()->getWinSize();
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("baoshiyu_shuzi_02-ipadhd.png");
     	CCSize size = texture->getContentSize();
		float width = texture->getContentSize().width/10;

		_label = CCLabelAtlas::create("10","baoshiyu_shuzi_02-ipadhd.png",width,size.height,'0');
		addChild(_label,99);
		_label->setPosition(ccp(200,1300));
		_countDown = ScheduleCountDown::create(this,60,true); 
		addChild(_countDown,99);
		_countDown->setPosition(ccp(500,500));
	  }while(0);
	  return true;
}

void PanelLayer::pauseCallback(CCObject* obj/*,TouchEventType type*/){

	
	GameScene* _gamescene = (GameScene*)this->getParent();
	_gamescene->is_pause = true;	
		_gamescene->pause();
	
}
void PanelLayer::MusicCallback(CCObject* obj/*,TouchEventType type*/){
	PersonalAudioEngine::sharedEngine()->playEffect(kEffectSwitchCannon);
	GameScene* _gamescene = (GameScene*)this->getParent();
	if(_gamescene->is_music){
		PersonalAudioEngine::sharedEngine()->pauseBackgroundMusic();
	    _gamescene->is_music = false;
	}
	else{
		PersonalAudioEngine::sharedEngine()->resumeBackgroundMusic();
		_gamescene->is_music = true;
	}
	
}

void PanelLayer::scheduleTimeUp(){
	CCLog("time up");
	if(_countDown->getLoop()==false){
		removeChild(_countDown);
	}
}

void PanelLayer::setScheduleNumber(int number){
	CCString *str = CCString::createWithFormat("%d",number);
	_label->setString(str->getCString());
}