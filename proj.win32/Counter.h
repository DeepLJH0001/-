#ifndef __COUNTER_H__
#define __COUNTER_H__
#include "cocos2d.h"
USING_NS_CC;

enum{
	k_Counter_Action = 0
};
class Counter :public CCNode{
public:
		int _digit;//������Ҫ��ʾ������0~9��
		cocos2d::CCNode* _presenters; //�������ͼƬ�Ľڵ㣬������ʾ
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