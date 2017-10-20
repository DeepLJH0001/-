#ifndef _WEAPON_H_
#define _WEAPON_H_
#include "cocos2d.h"
#include "Cannon.h"
#include "Bullet.h"
USING_NS_CC;
typedef enum{
	changeyes = 0,
	changenot

}Switchtype;
class Weapon : public CCNode
{
	//CC_SYNTHESIZE(Cannon*,_cannon,Cannon);
public:
	Weapon(void);
	~Weapon(void);
	CC_SYNTHESIZE(Cannon*,_cannon,Cannon);
	//Cannon* _cannon;
/*	CC_SYNTHESIZE(Bullet*,_bullets,Bullets);*/
	CCArray* _bullets;
	CCArray* _fishNets;

	CCArray* _particles;

	static Weapon* create(CannonType type = k_Cannon_Type_1);
	bool init(CannonType type = k_Cannon_Type_1);
	void changeCannon(CannonOperate operate);
	CCSize getCannonSize();
	int getCannonType();

	void aimAt(CCPoint target);
	void shootTo (CCPoint target);
	CCRect getCollisionArea(Bullet *bullet);

	void end(Bullet *bullet);
protected:
	Bullet* getBulletToShoot();
};
#endif//_WEAPON_H_
