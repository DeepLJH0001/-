#ifndef __PANELLAYER_H__
#define __PANELLAYER_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GoldCounterLayer.h"
#include "ScheduleCountDown.h"

USING_NS_CC;
using namespace cocos2d::extension;
class PanelLayer : public CCLayer
					,public ScheduleCounterDelegate 		
{
	public:	
		PanelLayer(void);
		~PanelLayer(void);
		virtual bool init();
		CREATE_FUNC(PanelLayer);
	    void pauseCallback(CCObject* obj/*,ui::TouchEventType type*/);
	    void MusicCallback(CCObject* obj/*,ui::TouchEventType type*/);
		CC_SYNTHESIZE_READONLY(GoldCounterLayer*,_goldCounterLayer,GoldCounterLayer);
protected:
	  virtual void scheduleTimeUp();
	  virtual void setScheduleNumber(int number);
	  ScheduleCountDown *_countDown;
	  CCLabelAtlas *_label;
};
#endif