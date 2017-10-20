#include "PauseMenu.h"
#include "GameScene.h"
;
bool PauseMenu ::init(){
	
	do{
		CC_BREAK_IF(!CCLayer::init());	
		Widget *widget=GUIReader::shareReader()->widgetFromBinaryFile("NewUi_2.csb");
		TouchGroup *touchGrounp=TouchGroup::create();
		touchGrounp->addWidget(widget);
		touchGrounp->setTouchPriority(-128);//最高权限
		addChild(touchGrounp,1);
		Button *btnPause=(Button*) UIHelper::seekWidgetByName(widget,"resume");
		if(btnPause==NULL){
		    return false;
		}
		
		btnPause->addTouchEventListener(this,toucheventselector(PauseMenu::pauseCallback));

		//Button *btnBack=(Button*) UIHelper::seekWidgetByName(widget,"Back");
	}while(0);
	return true;
}
void PauseMenu::pauseCallback(CCObject* obj,TouchEventType type){
	if(type==TOUCH_EVENT_ENDED){
		GameScene* _gamescene = (GameScene*)this->getParent();
		_gamescene->resume();
		_gamescene->is_pause = false;
	}
}