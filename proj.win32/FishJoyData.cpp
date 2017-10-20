#include "FishJoyData.h"
#include "StaticData.h"
USING_NS_CC;
static FishJoyData* _sharedFishingJoyData = NULL;
FishJoyData* FishJoyData::sharedFishJoyData()
{
    if(_sharedFishingJoyData==NULL){
        _sharedFishingJoyData = new FishJoyData();
        _sharedFishingJoyData->init();
    }
    return _sharedFishingJoyData;
}
void FishJoyData::purge()
{
    CC_SAFE_RELEASE_NULL(_sharedFishingJoyData);
}
FishJoyData::FishJoyData()
{
    
}
FishJoyData::~FishJoyData()
{
    this->flush();
}
bool FishJoyData::init()
{
    _isBeginner = CCUserDefault::sharedUserDefault()->getBoolForKey("beginner",true);

    if(_isBeginner == true){//第一次玩
        this->reset();
        this->flush();
        this->setIsBeginner(false);
    }else{
        _isBeginner = CCUserDefault::sharedUserDefault()->getBoolForKey("beginner");
        CCUserDefault *userDefault = CCUserDefault::sharedUserDefault();
		_isSound = userDefault -> getBoolForKey("sound");
        _isMusic = userDefault -> getBoolForKey("music");
        _gold = STATIC_DATA_INT("default_gold");
		//_multiple = userDefault ->getIntegerForKey("multiple");

    }
	/*	 this->reset();*/
    return true;
}
void FishJoyData::reset()
{
    int gold = STATIC_DATA_INT("default_gold");
	CCLog("default_gold = %d",gold);
    this->setGold(gold);
    this->setIsBeginner(false);
    this->setisMusic(1);
    this->setisSound(1);
	//this->setMultiple(0);
	//this->setCannonType(0);

}

void FishJoyData::flush()
{
	//将数据成员的值保存到xml文件里
	CCUserDefault *userDefault = CCUserDefault::sharedUserDefault();
    userDefault->setBoolForKey("sound", this->getisSound());
    userDefault->setBoolForKey("beginner", this->getIsBeginner());
    userDefault->setIntegerForKey("gold", this->getGold());
    userDefault->setFloatForKey("music", this->getisMusic());
//	userDefault->setIntegerForKey("cannonType",this->getCannonType());
	//userDefault->setIntegerForKey("multiple",this->getMultiple());
	userDefault->flush();
}

void FishJoyData::alterGold(int delta)
{
	this->setGold(this->getGold()+delta);
	this->flush();
}
void FishJoyData::alterCannonType(int cannon)
{
	//this->setCannonType(cannon);
}