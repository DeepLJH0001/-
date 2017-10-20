#ifndef _FishJoyData_
#define _FishJoyData_
#include "cocos2d.h"
class FishJoyData : public cocos2d::CCObject
{
public:
    static FishJoyData* sharedFishJoyData();
   
    CC_SYNTHESIZE(bool, _isBeginner, IsBeginner);
	CC_SYNTHESIZE(int , _gold, Gold);
    CC_SYNTHESIZE(bool,_isMusic, isMusic);
    CC_SYNTHESIZE(bool, _isSound,isSound);
    //CC_SYNTHESIZE(float, _cannonType, CannonType);


    //CC_SYNTHESIZE(float, _multiple, Multiple);

    ///**
    // * 内存不足时调用
    // */
    void purge();
    
    /**
     *	 将数据从内存保存到外部文件中
     */
    void flush();
    

    /**
     *	重置游戏数据为默认数值
     */
    void reset();
	void alterGold(int delta);
	void alterCannonType(int cannon);
protected:
    FishJoyData();
    ~FishJoyData();
    bool init();
};

#endif 
