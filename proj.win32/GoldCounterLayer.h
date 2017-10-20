#ifndef __GOLDCOUNTERLAYER_H__
#define __GOLDCOUNTERLAYER_H__

#include "cocos2d.h"
#include "Counter.h"

USING_NS_CC;

class GoldCounterLayer : public CCNode//��������ǲ�
{
public:
		int _number;//��ǰ�����
		GoldCounterLayer();
		~GoldCounterLayer();
		static GoldCounterLayer* create(int number);
		bool init(int number);
		void setNumber(int number, int ceiling=999999);
};
#endif