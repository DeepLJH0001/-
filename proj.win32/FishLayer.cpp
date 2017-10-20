#include "FishLayer.h"
#include "StaticData.h"
#include "Fish.h"

FishLayer::FishLayer(void)
{
}


FishLayer::~FishLayer(void)
{
	CC_SAFE_RELEASE(_fishes);
}

bool FishLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	int _fishes_Max_count = 15;
	_fishes = CCArray::createWithCapacity(_fishes_Max_count);
	CC_SAFE_RETAIN(_fishes);
	for (int i=0;i<_fishes_Max_count;i++)
	{
		int newType = CCRANDOM_0_1()*(k_Fish_Type_Count -1);//鱼的枚举18-1
		Fish *fish = Fish::create((FishType)newType);
		_fishes->addObject(fish);
	}

	this->schedule(schedule_selector(FishLayer::addFish),1.0);

	return true;

}

void FishLayer::addFish(float dt){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	srand((unsigned)time(NULL));

	
	int count = CCRANDOM_0_1()*1+3 ;//不同的场景鱼的随机累加数不同
	CCObject* obj;
	int num = 0;
	CCARRAY_FOREACH(_fishes,obj)
	{
		Fish* fish = (Fish*)obj;
		if(fish->isRunning()==false)
		{
			
			int fish_X = CCRANDOM_0_1()*winSize.width;
 			int fish_Y = CCRANDOM_0_1()*winSize.height*0.6+winSize.height*0.2;//0.8上限不溢出，0.2下限不溢出控制鱼在中间出现
			/*fish->setPosition(ccp(fish_X,fish_Y));
			this->addChild(fish);*/
			resetFish(fish);
			num++;
			//resetFish(fish);
			if(num>=count)
				break;
	
		}
	}
}

void FishLayer::resetFish(Fish* fish){
	//fish->reset();
	int direction = CCRANDOM_0_1()*k_Direction_Count;
	fish->direction = direction;
	float startX,startY,endX,endY;
	addChild(fish);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize fishSize = fish->getSize();
	
	if(direction == k_Direction_Right){
		startX = -fishSize.width/2;
		endX = winSize.width+fishSize.width/2;
		fish->setRotation(180.0f);
	}
	else{
		startX = winSize.width + fishSize.width;
		endX = -fishSize.width/2;
		fish->setRotation(0.0f);
	}
	float maxHeight = winSize.height*0.7 - fishSize.height;//加个系数0.8 不在panelLayer上面好一点
	startY = CCRANDOM_0_1()*maxHeight-fishSize.height/2+300;//鱼尽量在炮台上面
	endY = CCRANDOM_0_1()*maxHeight+ fishSize.height/2+300;

	if (fish->getFishType()==10||fish->getFishType()==12||fish->getFishType()==13||fish->getFishType()==16/*k_Fish_Type_Shark*/ )
	{//设置大的鱼，如鲨鱼的游动方向为直线
		endY = startY;
	}
	fish->setPosition(startX,startY);
	fish->moveTo(ccp(endX,endY));
	
}