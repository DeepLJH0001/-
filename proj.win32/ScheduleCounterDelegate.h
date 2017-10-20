#ifndef __SCHEDULECHONTERDELEGATE_H__
#define __SCHEDULECHONTERDELEGATE_H__
	class ScheduleCounterDelegate
	{
	public:
		virtual void scheduleTimeUp() = 0;
		virtual void setScheduleNumber(int number){
			return ;
		}
	};
#endif