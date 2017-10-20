#ifndef __FISH_H__
#define __FISH_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;
typedef enum{
k_Fish_Type_SmallFish = 0,
	    k_Fish_Type_Croaker,
	    //k_Fish_Type_Count,//鱼的数量，可以根据测试的需要调整位置，在这里值是2
	    k_Fish_Type_AngleFish,
		k_Fish_Type_Amphiprion,	//小丑鱼
		k_Fish_Type_PufferS,	//刺豚
		k_Fish_Type_Bream,		//蓝色
		k_Fish_Type_Progy,		//红色
		k_Fish_Type_Chelonian,	//乌龟
		k_Fish_Type_Lantern,	//灯笼鱼
		k_Fish_Type_Ray,		//魔鬼鱼
		k_Fish_Type_Shark,		//蓝色鲨鱼
		k_Fish_Type_GoldenTrout,
		k_Fish_Type_GShark,		//金色鲨鱼
		k_Fish_Type_GMarlineFish,
		k_Fish_Type_GrouperFish,
		k_Fish_Type_JadePerch,	//宝石鱼
		k_Fish_Type_MarlineFish,
		k_Fish_Type_PufferB,	//刺豚受到攻击
		k_Fish_Type_Count
}FishType;

enum{
	k_Action_Animate = 0,
	k_Action_MoveTo,
	k_Action_Blink,
	k_Fish_Free,
	k_Fish_Caught,
	life,
	dead,
	k_Action_updatedirect
};
enum{
	k_Direction_Left = 0,
	k_Direction_Right,
	k_Direction_Count
};
class Fish:public CCNode{
	
public:
	bool _beCaught;
	int direction;
	CCPoint Fish_lastPoint;
	CC_SYNTHESIZE_READONLY(FishType,_type,FishType);
	CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*,_fishSprite,FishSprite);
	//CCSprite *_fishSprite ;//鱼对应的精灵（图片）。
	//FishType _type; //类型，是哪种鱼
	bool init(FishType type = k_Fish_Type_SmallFish);
	static Fish* create(FishType type = k_Fish_Type_SmallFish);
	int getScore();
	int getSpeed();
	CCRect getCollisionArea();
	void beCaught();
	void beCaught_CallFunc();

	void moveTo(CCPoint destination);
	void moveEnd();

	////void reset();
	CCSize getSize();

	void updateActionDirection();
};

#endif