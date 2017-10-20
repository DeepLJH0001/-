#ifndef __COUNTER_H__
#define __COUNTER_H__
#include "cocos2d.h"
USING_NS_CC;

enum{
	k_Counter_Action = 0
};
class Counter :public CCNode{
public:
		int _digit;//现在需要显示的数字0~9。
		cocos2d::CCNode* _presenters; //存放数字图片的节点，用于显示
		Counter();
		~Counter();
		static Counter * create(CCArray* presenters, int digit=0);
		bool init(CCArray* presenters, int digit);
		void setDigit(int digit);
		int getDigit();
		void animation(int digit);
		void visit();
};
#endif