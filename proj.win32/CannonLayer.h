#ifndef _CANNON_LAYER_H_
#define _CANNON_LAYER_H_
#include "cocos2d.h"
#include "Weapon.h"

USING_NS_CC;

class CannonLayer ://用来存放炮台和炮台切换按钮
	public CCLayer
{
public:
	Weapon* _weapon;//指向武器对象；*/
	cocos2d::CCMenuItemSprite* _addItem;//切换炮台的按钮，炮台型号加1。
	cocos2d::CCMenuItemSprite* _subItem;//切换炮台的按钮，炮台型号减1。
	//CC_SYNTHESIZE_READONLY(Weapon*, _weapon, Weapon);//getweapon 会出问题不是public
	CannonLayer(void);
	~CannonLayer(void);
	bool init();
	CREATE_FUNC(CannonLayer);
	void switchCannon(CCObject* sender);//菜单项的回调函数

	void aimAt(CCPoint target);
	void shootTo (CCPoint target);
};

#endif//_CANNON_LAYER_H