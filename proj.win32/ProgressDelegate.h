#ifndef _PROGRESSDELEGATE_H_
#define _PROGRESSDELEGATE_H_
class ProgressDelegate
{
public:
	virtual void loadingFinished() = 0;
	virtual void progressPercentageSetter(float percentage){return;};
};

#endif