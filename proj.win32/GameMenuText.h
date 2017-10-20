#include "Fish.h"
#include "StaticData.h"

USING_NS_CC;

class GameMenuText : public CCSprite{
public:
	//CCArray* GameMenuText_Array;
	CCSprite *Normal;
	CCSprite *Select;
	virtual bool init();
	CREATE_FUNC(GameMenuText);
	//static CCArray* createWithSpriteFrameName
    void createWithSpriteFrameName(const char *pszSpriteFrame_BG_Normal_Name,//普通背景
		                               const char *pszSpriteFrame_Selected_Normal_Name,//选中背景
									   const char *pszSpriteFrame_TX_Name,//Text
									   float w,							  //Text放置在背景的位置width
									   float h);						  //Text放置在背景的位置height
};

