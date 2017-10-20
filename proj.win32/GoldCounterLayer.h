#ifndef __GOLDCOUNTERLAYER_H__
#define __GOLDCOUNTERLAYER_H__

#include "cocos2d.h"
#include "Counter.h"

USING_NS_CC;

class GoldCounterLayer : public CCNode//这个并不是层
{
public:
		int _number;//当前金币数
		GoldCounterLayer();
		~GoldCounterLayer();
		static GoldCounterLayer* create(int number);
		bool init(int number);
		void setNumber(int number, int ceiling=999999);
};
#endif