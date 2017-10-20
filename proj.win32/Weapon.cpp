#include "Weapon.h"
#include "StaticData.h"
#include "FishNet.h"
#include "Bullet.h"
#include "PersonalAudioEngine.h"
#define BULLET_COUNTS 10
Weapon::Weapon(void)
{
}


Weapon::~Weapon(void)
{
}

Weapon* Weapon::create(CannonType type /*= k_Cannon_Type_1*/)
{
	Weapon* weapon = new Weapon();
	weapon->autorelease();
	weapon->init(type);
	return weapon;
}

bool Weapon::init(CannonType type /*= k_Cannon_Type_1*/)
{
	this->setTag(changeyes);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_cannon = Cannon::create(type);

	_cannon->setPosition(ccp(-512,0));

	this->addChild(_cannon,0);

	_fishNets = CCArray::createWithCapacity(BULLET_COUNTS);
	CC_SAFE_RETAIN(_fishNets);
	_bullets = CCArray::createWithCapacity(BULLET_COUNTS);
	
		//初始化粒子
	_particles = CCArray::createWithCapacity(BULLET_COUNTS);
	CC_SAFE_RETAIN(_particles);

	_bullets = CCArray::createWithCapacity(BULLET_COUNTS);

	CC_SAFE_RETAIN(_bullets);

	for(int i = 0;i<BULLET_COUNTS;i++)
	{
		CCParticleSystemQuad* particle_1 = CCParticleSystemQuad::create("growingFlare.plist");
		CCParticleSystemQuad* particle_2 = CCParticleExplosion::create();//CCParticleSystemQuad::create("blastWave.plist");
		//CCParticleSystem* particle = CCParticleExplosion::create();  //爆炸效果cocos自带12种
		particle_2->setTexture(CCTextureCache::sharedTextureCache()->addImage("particle.png")); 
		particle_1->setTexture(CCTextureCache::sharedTextureCache()->addImage("particle.png"));//blastWave
		particle_1 ->stopSystem();
		particle_2 ->stopSystem();
		addChild(particle_1);
		addChild(particle_2);
		_particles->addObject(particle_1);
		_particles->addObject(particle_2);
////		
//
 		FishNet* fishNet = FishNet::create();
		fishNet->setUserObject(particle_2);
		//fishNet->setUserObject(particle_1);
		_fishNets->addObject(fishNet);
		fishNet->setVisible(false);

		Bullet* bullet = Bullet::create();
		addChild(bullet,2);
		addChild(fishNet,4);
		_bullets->addObject(bullet);
		bullet->setVisible(false);
		bullet->setUserObject(fishNet);
		


	}


	return true;

}

void Weapon::changeCannon(CannonOperate operate)
{
	PersonalAudioEngine::sharedEngine()->playEffect(kEffectSwitchCannon);
	CannonType type = getCannon()->getType();
	if(operate==k_Cannon_Operate_Up)
	{
		type = (CannonType)((int)type+1);
		
	}
	else if(operate==k_Cannon_Operate_Down)
	{
		type = (CannonType)((int)type-1);
	}
	CCLog("type = %d",type);
	getCannon()->setType(type);

}
int Weapon::getCannonType(){
	return _cannon->getType();
}
CCSize Weapon::getCannonSize()
{
	
	CCSprite* sprite = (CCSprite*)getCannon()->_cannonSprites->objectAtIndex(_cannon->getType());

	return sprite->getContentSize();
}

void Weapon::aimAt(CCPoint target){//瞄准
	_cannon->aimAt(target);//旋转炮台
}
Bullet *Weapon::getBulletToShoot(){
	CCObject *object = NULL;
	CCARRAY_FOREACH(_bullets,object){//子弹的个数
		Bullet *bullet = (Bullet *)object;
		if (bullet->isVisible() == false)
		{
			return bullet;
		}
	}
	return NULL;


}



void Weapon:: shootTo (CCPoint target){

	Bullet *bullet = getBulletToShoot();
	if (bullet == NULL)
	{
		return;
	}
	PersonalAudioEngine::sharedEngine()->playEffect(kEffectShoot);
	float distance = 360 * (_cannon->getType()+1);
	CCPoint start = getParent()->convertToWorldSpace(ccp(getPosition().x/2,getPosition().y));//?
	if(distance < ccpDistance(target,start)){
		CCPoint nomalize = ccpNormalize(ccpSub(target,start));
	
		target = ccpAdd(start,ccpMult(nomalize,distance));
	}
	bullet->flyTo(target,_cannon->getType());
}


void Weapon::end(Bullet *bullet)
{

	CCPoint pos = bullet->getPosition();
	bullet->end();
	FishNet *fishNet = (FishNet *)bullet->getUserObject();
//	int type = this->getCannon()->getType();
//	fishNet->showAt(pos,type);
//	fishNet->setVisible(true);
//	CCParticleSystemQuad* _particles = (CCParticleSystemQuad *)fishNet->getUserObject();
//	_particles->resetSystem();
		//粒子作用
//	CCParticleSystemQuad *_particle=(CCParticleSystemQuad*)fishNet->getUserObject();
	/*_particle->setPosition(pos);
	_particle->resetSystem();*/
	
	
}

CCRect Weapon::getCollisionArea(Bullet *bullet){
	FishNet *fishNet = (FishNet *)bullet->getUserObject();
	if(fishNet -> isVisible()){
		return fishNet->getCollisionArea();
	}
	return CCRectZero;
}