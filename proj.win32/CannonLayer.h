#ifndef _CANNON_LAYER_H_
#define _CANNON_LAYER_H_
#include "cocos2d.h"
#include "Weapon.h"

USING_NS_CC;

class CannonLayer ://���������̨����̨�л���ť
	public CCLayer
{
public:
	Weapon* _weapon;//ָ����������*/
	cocos2d::CCMenuItemSprite* _addItem;//�л���̨�İ�ť����̨�ͺż�1��
	cocos2d::CCMenuItemSprite* _subItem;//�л���̨�İ�ť����̨�ͺż�1��
	//CC_SYNTHESIZE_READONLY(Weapon*, _weapon, Weapon);//getweapon ������ⲻ��public
	CannonLayer(void);
	~CannonLayer(void);
	bool init();
	CREATE_FUNC(CannonLayer);
	void switchCannon(CCObject* sender);//�˵���Ļص�����

	void aimAt(CCPoint target);
	void shootTo (CCPoint target);
};

#endif//_CANNON_LAYER_H