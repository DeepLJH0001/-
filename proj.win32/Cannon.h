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

	CCArray *_cannonSprites ;//�����̨ͼƬ�����顣
	CannonType _type; //���ͣ�������̨
	bool init(CannonType type = k_Cannon_Type_1);
	Cannon(void);//Ĭ�Ϲ��캯����_type = k_Cannon_Invalid;
	~Cannon(void);//����������CC_SAFE_RELEASE(_cannonSprites);
	void setType(CannonType type);//������̨������
	CannonType getType(void);//����_type;
	float getFireRange();
	CCSize getSize();//�����̨�Ŀ��
	static Cannon* create(CannonType type=k_Cannon_Type_1);//Ĭ����̨
	void aimAt(cocos2d::CCPoint target);//��̨����
};
#endif