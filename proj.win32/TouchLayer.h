#ifndef _TouchLayer_
#define _TouchLayer_
#include "cocos2d.h"

class GameScene;

class TouchLayer : public cocos2d::CCLayer
{
public:
	GameScene *_gamescene;
    CREATE_FUNC(TouchLayer);
    bool init();
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
	void registerWithTouchDispatcher();
    //�������رմ����Ľӿ�
    //void setTouchEnabled(bool flag);
protected:
    GameScene* getGameScene();
    //cocos2d::CCPoint locationFromTouch(cocos2d::CCTouch *touch);
	bool m_bIsTouchEnabled;

};

#endif 
