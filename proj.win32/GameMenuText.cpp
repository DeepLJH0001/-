#include"GameMenuText.h"

bool GameMenuText::init(){
	do 
	{
		CC_BREAK_IF(! CCSprite::init());
	} while (0);
	return true;
}
void GameMenuText::createWithSpriteFrameName(const char *pszSpriteFrame_BG_Normal_Name,
												 const char *pszSpriteFrame_BG_Selected_Name,
	                                             const char *pszSpriteFrame_TX_Name,
												 float w,
												 float h
												 )
{
	Normal = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING(pszSpriteFrame_BG_Normal_Name));
	Select = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING(pszSpriteFrame_BG_Selected_Name));
	CCSprite *pszSpriteFrame_TX_Normal = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING(pszSpriteFrame_TX_Name));
	CCSprite *pszSpriteFrame_TX_Selected = CCSprite::createWithSpriteFrameName(STATIC_DATA_STRING(pszSpriteFrame_TX_Name));
	pszSpriteFrame_TX_Normal->setPosition(ccp(Normal->getContentSize().width*w,Normal->getContentSize().height*h));
	Normal->addChild(pszSpriteFrame_TX_Normal);
	pszSpriteFrame_TX_Selected->setPosition(ccp(Select->getContentSize().width*w,Select->getContentSize().height*h));
	Select->addChild(pszSpriteFrame_TX_Selected);
}