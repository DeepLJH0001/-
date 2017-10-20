#ifndef _LOADING_LAYER_H_
#define _LOADING_LAYER_H_
#include "cocos2d.h"
#include "ProgressBar.h"
class LoadingLayer : public cocos2d::CCLayer, public ProgressDelegate
{
public:
	CREATE_FUNC(LoadingLayer);
	LoadingLayer();
	ProgressBar *_progressBar;
	cocos2d::CCLabelTTF* _progressFg;

	int _numSp;//��Ҫ���ص�ͼƬ������
	int _loadedSp;//�Ѿ����ص�ͼƬ����


	bool init();
	void initProgressBar();
	void progressPercentageSetter(float percent);
	void loadingFinished();
	void cacheInit(float dt);
	void loading(CCObject *sender);
	void loadingPList(CCObject *sender);

protected:

private:
};
#endif