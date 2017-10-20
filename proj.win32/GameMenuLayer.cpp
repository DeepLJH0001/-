#include"GameMenuLayer.h"
#include"StaticData.h"
#include"GameScene.h"
#include"GameMenuText.h"
#include"PersonalAudioEngine.h"
//#define STATIC_DATA_STRING(key) StaticData::sharedStaticData()->stringFromKey(key);
using namespace cocos2d;

CCScene* GameMenuLayer::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        GameMenuLayer *layer = GameMenuLayer::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}
bool GameMenuLayer::init(){
	 bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
       

        // 2. Add a label shows "Hello World".

        // Create a label and initialize with string "Hello World".
        //CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
        //CC_BREAK_IF(! pLabel);

        // Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        //pLabel->setPosition(ccp(size.width / 2, size.height - 50));

        // Add the label to HelloWorld layer as a child layer.
        //this->addChild(pLabel, 1);

        // 3. Add add a splash screen, show the cocos2d splash image.
        CCSprite* BK = CCSprite::create("ui_background_normal-ipadhd.png");
        CC_BREAK_IF(! BK);

        // Place the sprite on the center of the screen
        BK->setPosition(ccp(size.width/2, size.height/2));
		BK->setScaleX(size.width/BK->getContentSize().width);
		BK->setScaleY(size.height/BK->getContentSize().height);
        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(BK, 0);

		CCSprite* title = CCSprite::create("main_ui_title_cn-ipadhd.png");
        CC_BREAK_IF(! title);

        title->setPosition(ccp(size.width/2, size.height*3/4));
		title->setScaleX(size.width/title->getContentSize().width*0.60);
		title->setScaleY(size.height/title->getContentSize().height*0.35);
        
        this->addChild(title, 0);
		createMenu();
        bRet = true;
    } while (0);

    return bRet;
}
void GameMenuLayer::createMenu(void){
	do{
		 CCSize size = CCDirector::sharedDirector()->getWinSize();
		 CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(STATIC_DATA_STRING("game_menu_text"));
		 CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(STATIC_DATA_STRING("game_menu_ui"));
		 
		
		 GameMenuText* _GameMenuText_start = GameMenuText::create();
		  
		 _GameMenuText_start->createWithSpriteFrameName("game_menu_start_normal","game_menu_start_selected","game_menu_start_text",0.5,0.6);
		 
		 CCMenuItemSprite *start_Menu_Item = CCMenuItemSprite::create(
			 _GameMenuText_start->Normal,
			 _GameMenuText_start->Select,
			 this,
			 menu_selector(GameMenuLayer::menuCallbackStartGame)
			 );
		  CC_BREAK_IF(! start_Menu_Item);


		 GameMenuText* _GameMenuText_selece_scene = GameMenuText::create();
		 _GameMenuText_selece_scene->createWithSpriteFrameName("game_menu_scene_normal","game_menu_scene_selected","game_menu_scene_text",0.5,0.5);
		 CCMenuItemSprite *sence_Menu_Item = CCMenuItemSprite::create(
			 _GameMenuText_selece_scene->Normal,
			 _GameMenuText_selece_scene->Select,
			 this,
			 menu_selector(GameMenuLayer::menuCallbackSelectScene)
			 );
		  CC_BREAK_IF(! sence_Menu_Item);

		  CCMenu *start_Menu = CCMenu::create(start_Menu_Item,sence_Menu_Item,NULL);
		  ;
		  start_Menu->setPosition(ccp(size.width/2,size.height/4));
		  
		  start_Menu->alignItemsVerticallyWithPadding(start_Menu_Item->getContentSize().height/4);
		  this->addChild(start_Menu,1);



		 CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(GameMenuLayer::menuCallbackSelectScene));
        CC_BREAK_IF(! pCloseItem);

        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

      
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);
		this->addChild(pMenu, 1);
	}while(0);
        // Add the menu to HelloWorld layer as a child layer.
     
}
void GameMenuLayer::menuCallbackSelectScene(CCObject* pSender)
{
    // "close" menu item clicked
	
	PersonalAudioEngine::sharedEngine()->playEffect(kEffectSwitchCannon);
}
void GameMenuLayer::menuCallbackStartGame(CCObject* pSender)
{
    // "close" menu item clicked
	PersonalAudioEngine::sharedEngine()->playEffect(kEffectSwitchCannon);
	_loadingLayer = LoadingLayer::create(); 
	this->addChild(_loadingLayer,99);
	//CCScene *startGameScene = CCTransitionZoomFlipAngular::create(1.0f,GameScene::create());
   // CCDirector::sharedDirector()->pushScene(startGameScene);
}