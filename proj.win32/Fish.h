#ifndef __FISH_H__
#define __FISH_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;
typedef enum{
k_Fish_Type_SmallFish = 0,
	    k_Fish_Type_Croaker,
	    //k_Fish_Type_Count,//������������Ը��ݲ��Ե���Ҫ����λ�ã�������ֵ��2
	    k_Fish_Type_AngleFish,
		k_Fish_Type_Amphiprion,	//С����
		k_Fish_Type_PufferS,	//����
		k_Fish_Type_Bream,		//��ɫ
		k_Fish_Type_Progy,		//��ɫ
		k_Fish_Type_Chelonian,	//�ڹ�
		k_Fish_Type_Lantern,	//������
		k_Fish_Type_Ray,		//ħ����
		k_Fish_Type_Shark,		//��ɫ����
		k_Fish_Type_GoldenTrout,
		k_Fish_Type_GShark,		//��ɫ����
		k_Fish_Type_GMarlineFish,
		k_Fish_Type_GrouperFish,
		k_Fish_Type_JadePerch,	//��ʯ��
		k_Fish_Type_MarlineFish,
		k_Fish_Type_PufferB,	//�����ܵ�����
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
	//CCSprite *_fishSprite ;//���Ӧ�ľ��飨ͼƬ����
	//FishType _type; //���ͣ���������
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