#ifndef __GAMEMENY_LAYER_H__
#define __GAMEMENY_LAYER_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

#include "LoadingLayer.h"

class GameMenuLayer : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    void menuCallbackStartGame(CCObject *sender);
    // a selector callback
    void menuCallbackSelectScene(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(GameMenuLayer); 
	void createMenu();
	LoadingLayer* _loadingLayer;
};

#endif  // __HELLOWORLD_SCENE_H__