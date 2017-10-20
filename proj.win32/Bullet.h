#ifndef __BULLET_H__
#define __BULLET_H__
#include "cocos2d.h"

USING_NS_CC;
enum{
	k_Bullet_Action = 0
};
class Bullet 
	:public CCNode {
public :
	CCSprite*  _bulletSprite ;//×Óµ¯µÄÍ¼Æ¬¾«Áé
	bool init();
	float getSpeed(int type);
	void flyTo(CCPoint  targetInWordSpace, int type = 0);
	CREATE_FUNC(Bullet);
	void end();
	CCPoint getCollisionPosion(void);

};
#endif