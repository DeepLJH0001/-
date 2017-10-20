#include "ScheduleCountDown.h"

ScheduleCountDown* ScheduleCountDown::create(ScheduleCounterDelegate* target, int perimeter, bool loop){
	ScheduleCountDown *counter = new ScheduleCountDown;
	counter->autorelease();
	counter->init(target, perimeter, loop);
	return counter;
}
bool ScheduleCountDown::init(ScheduleCounterDelegate* target, int perimeter, bool loop){
	if(!CCNode::init()){
		return false;
	}
	_target = target;
	_maxTime = _currentTime = perimeter;
	_loop = loop;
	schedule(schedule_selector(ScheduleCountDown::schedulePerSecond), 1.0f);//ע����1.0��Ҫ���õĺ���
	return true;
}
void ScheduleCountDown::schedulePerSecond(float delta){//��ʱ���ص�����
	_target->setScheduleNumber(_currentTime);
	--_currentTime;
	if (_currentTime==0)
	{
		if(_loop){
			_currentTime = _maxTime;
		}
	else
		{
				unschedule(schedule_selector(ScheduleCountDown::schedulePerSecond));
		}
			_target->scheduleTimeUp();
	}
}

