#ifndef __CANNO_H_
#define __CANNO_H_
#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"
#include "StaticData.h"
USING_NS_CC;
typedef enum{
	k_Cannon_Type_1 = 0,
	k_Cannon_Type_2,
k_Cannon_Type_3,
k_Cannon_Type_4,
k_Cannon_Type_5,
k_Cannon_Type_6,
k_Cannon_Type_7,
	k_Cannon_Count,
	k_Cannon_Invalid
}CannonType;
typedef enum{
	k_Cannon_Operate_Up = 1,
	k_Cannon_Operate_Down = -1
}CannonOperate;

class Cannon : public CCNode{
public:

	CCArray *_cannonSprites ;//存放炮台图片的数组。
	CannonType _type; //类型，是哪炮台
	bool init(CannonType type = k_Cannon_Type_1);
	Cannon(void);//默认构造函数，_type = k_Cannon_Invalid;
	~Cannon(void);//析构函数，CC_SAFE_RELEASE(_cannonSprites);
	void setType(CannonType type);//设置炮台的类型
	CannonType getType(void);//返回_type;
	float getFireRange();
	CCSize getSize();//获得炮台的宽高
	static Cannon* create(CannonType type=k_Cannon_Type_1);//默认炮台
	void aimAt(cocos2d::CCPoint target);//炮台朝向
};
#endif