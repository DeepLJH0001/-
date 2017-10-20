#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

#include "PanelLayer.h"

#include "PauseMenu.h"

#include"BackgroundLayer.h"
#include"Fish.h"
#include"FishLayer.h"
#include"CannonLayer.h"
#include "TouchLayer.h"
#include "Bullet.h"
#include "AppDelegate.h"

typedef enum{
    k_Operate_Pause = 0,
    k_Operate_Resume
}OperateFlag;
class GameScene : public cocos2d::CCScene
				,public ScheduleCounterDelegate
{
public:
	PanelLayer* _panelayer;
	PauseMenu* _pausemenu;
	BackgroundLayer* background;
	FishLayer* _fishLayer;
	CannonLayer* _cannonLayer;
	TouchLayer* _touchlayer;
	int gold ;
	bool is_music ;
	CCLabelAtlas *_label;
	ScheduleCountDown *_countDown;
	bool is_pause;
	GameScene(void);
	~GameScene(void);
	 bool init();  
	

    CREATE_FUNC(GameScene); 
	
	void preloadResources(void);
	void menuCloseCallback(CCObject* pSender);

	void pause();
	void resume();

	void operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag);

	void cannonAimAt(CCPoint point);
	void cannonShootTo(CCPoint point);

	bool checkOutCollisionBetweenFishesAndBullet(Bullet *bullet);//≈–∂œ”„∫Õ◊”µØ «∑Ò≈ˆ◊≤
	void checkOutCollisionBetweenFishesAndFishingNet(Bullet *bullet);//≈–∂œ”ÊÕ¯∫Õ”„ «∑Ò≈ˆ◊≤
	void checkOutCollision();
	void update(float delta);
	void fishWillBeCaught(Fish* fish);

	void alterGold(int delta);

	void resume_callFunc();
	virtual void scheduleTimeUp();
	virtual void setScheduleNumber(int number);
	const char* gb23122utf8(const char* gb2312);
	void NameMove();
	void NameEnd();
	void NameFade();
};

#endif