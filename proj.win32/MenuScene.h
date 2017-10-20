#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;
class MenuScene : public CCScene
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    MenuScene(void);
	~MenuScene(void);

	bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    //static cocos2d::CCScene* scene();
    
    // a selector callback
    //void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(MenuScene);
};

#endif  // __HELLOWORLD_SCENE_H__