#ifndef _FISH_LAYER_H_
#define _FISH_LAYER_H_

#include "cocos2d.h"
#include "Fish.h"
USING_NS_CC;

class FishLayer :
	public CCLayer
{
public:
	FishLayer(void);
	~FishLayer(void);
	bool init();
	CREATE_FUNC(FishLayer);
	CC_SYNTHESIZE_READONLY(cocos2d::CCArray*, _fishes, Fishes);

/*	CCArray* _fishes;*/

	void addFish(float dt);
	void resetFish(Fish* fish);

};

#endif//_FISH_LAYER_H_