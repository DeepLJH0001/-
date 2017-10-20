#ifndef __SCHEDULECOUNTDOWN_H__
#define __SCHEDULECOUNTDOWN_H__
#include "cocos2d.h"
#include "ScheduleCounterDelegate.h"
USING_NS_CC;
class ScheduleCountDown : public CCNode
{
public:
	static ScheduleCountDown* create(ScheduleCounterDelegate *target,int perimeter,bool loop);
	CC_SYNTHESIZE(int,_currentTime,CurrentTime);
	CC_SYNTHESIZE(int,_maxTime,MaxTime)
	CC_SYNTHESIZE(bool,_loop,Loop)
	CC_SYNTHESIZE(ScheduleCounterDelegate *,_target,Target)
protected:
	bool init(ScheduleCounterDelegate *target,int perimeter,bool loop);
	void schedulePerSecond(float delta);
};
#endif