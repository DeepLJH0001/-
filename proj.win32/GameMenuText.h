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
    void createWithSpriteFrameName(const char *pszSpriteFrame_BG_Normal_Name,//��ͨ����
		                               const char *pszSpriteFrame_Selected_Normal_Name,//ѡ�б���
									   const char *pszSpriteFrame_TX_Name,//Text
									   float w,							  //Text�����ڱ�����λ��width
									   float h);						  //Text�����ڱ�����λ��height
};

