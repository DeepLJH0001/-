#ifndef _BACK_GROUND_LAYER_H_
#define _BACK_GROUND_LAYER_H_

#include "cocos2d.h"
USING_NS_CC;
//显示游戏主场景中的背景图片
class BackgroundLayer:public CCLayer
{
public:
	BackgroundLayer(void);
	~BackgroundLayer(void);
	virtual bool init();
	CREATE_FUNC(BackgroundLayer);


};

#endif//_BACK_GROUND_LAYER_H_
