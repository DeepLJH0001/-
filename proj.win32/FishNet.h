#ifndef __FISHNET_H__
#define __FISHNET_H__
#include "cocos2d.h"

USING_NS_CC;
class FishNet : public CCNode{
	public:	
		CCSprite*  _fishNetSprite ;//ÓæÍøµÄÍ¼Æ¬¾«Áé
		bool init();
		CREATE_FUNC(FishNet);
		CCRect getCollisionArea();
		void showAt(CCPoint pos,int type /*= 0*/);
};
#endif