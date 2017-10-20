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
    // * �ڴ治��ʱ����
    // */
    void purge();
    
    /**
     *	 �����ݴ��ڴ汣�浽�ⲿ�ļ���
     */
    void flush();
    

    /**
     *	������Ϸ����ΪĬ����ֵ
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
