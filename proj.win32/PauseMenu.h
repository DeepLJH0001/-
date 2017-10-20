#ifndef __PAUSEMENU_H__
#define __PAUSEMENU_H__
#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocos2d::extension;
class PauseMenu :public CCLayer{
public:
	virtual bool init();
	CREATE_FUNC(PauseMenu);
	void pauseCallback(CCObject* obj,TouchEventType type);
};
#endif __PAUSEMENU_H__