#ifndef _BACK_GROUND_LAYER_H_
#define _BACK_GROUND_LAYER_H_

#include "cocos2d.h"
USING_NS_CC;
//��ʾ��Ϸ�������еı���ͼƬ
class BackgroundLayer:public CCLayer
{
public:
	BackgroundLayer(void);
	~BackgroundLayer(void);
	virtual bool init();
	CREATE_FUNC(BackgroundLayer);


};

#endif//_BACK_GROUND_LAYER_H_
