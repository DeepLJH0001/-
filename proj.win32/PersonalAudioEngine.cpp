#include "PersonalAudioEngine.h"
#include "FishJoyData.h"
#include "StaticData.h"
PersonalAudioEngine* PersonalAudioEngine::s_sharedEngine = NULL;
//PersonalAudioEngine* PersonalAudioEngine::sharedEngine();
using namespace CocosDenshion;
USING_NS_CC;
void PersonalAudioEngine::setBackgroundMusicVolume(float volume)
{
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
	FishJoyData::sharedFishJoyData()->setisMusic((bool)volume);
	FishJoyData::sharedFishJoyData()->flush();
}
void PersonalAudioEngine::setEffectsVolume(float volume)
{
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
	FishJoyData::sharedFishJoyData()->setisSound((bool)volume);
	FishJoyData::sharedFishJoyData()->flush();
}
PersonalAudioEngine* PersonalAudioEngine::sharedEngine()
{
	if(s_sharedEngine==NULL){
        s_sharedEngine = new PersonalAudioEngine();
        s_sharedEngine->init();
    }
    return s_sharedEngine;
}
bool PersonalAudioEngine::init()
{
	//this->preloadBackgroundMusic(STATIC_DATA_STRING("bg_music"));
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music_1.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music_3.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music_6.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("BK.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("BK2.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("bgm_fire.aif");
	SimpleAudioEngine::sharedEngine()->preloadEffect("bgm_button.aif");
	SimpleAudioEngine::sharedEngine()->preloadEffect("bgm_net.mp3");
	//SimpleAudioEngine::sharedEngine()->preloadEffect("1.mp3");
	bool isMusic = FishJoyData::sharedFishJoyData()->getisMusic();
	bool isSound = FishJoyData::sharedFishJoyData()->getisSound();
	//SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume((float)isMusic);
	//SimpleAudioEngine::sharedEngine()->setEffectsVolume((float)isSound);
	//FishJoyData
	//CCLog(STATIC_DATA_STRING("bg_music"));
 	//this->playEffect(kEffectShoot);
 	//this->playEffect(kEffectButton);
	//this->playEffect(kEffectPause);
	//this->setBackgroundMusicVolume(100/*FishingJoyData::sharedFishingJoyData()->getMusicVolume()*/);
	//this->setEffectsVolume(100/*FishingJoyData::sharedFishingJoyData()->getSoundVolume()*/);

	return true;
}
void PersonalAudioEngine::purge()
{
	CC_SAFE_DELETE(s_sharedEngine);
}
PersonalAudioEngine::PersonalAudioEngine()
{

}
PersonalAudioEngine::~PersonalAudioEngine()
{

}
void PersonalAudioEngine::playEffect(EffectType  type){
	//CCString* fileName = CCString::createWithFormat(STATIC_DATA_STRING("effect_format"),type);
	//SimpleAudioEngine::sharedEngine()->playEffect(STATIC_DATA_STRING(fileName->getCString()));
	switch(type){
		case kEffectFishNet:
			SimpleAudioEngine::sharedEngine()->playEffect("bgm_net.mp3");
			break;
		case kEffectShoot:
			SimpleAudioEngine::sharedEngine()->playEffect("bgm_fire.aif");
			break;
		case kEffectSwitchCannon:
			SimpleAudioEngine::sharedEngine()->playEffect("bgm_button.aif");
			break;
	}
	
}
void PersonalAudioEngine::playBackgroundMusic(int type){
		switch(type){
		case kEffectBK:
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music_3.mp3",true);
			break;
		case kEffectBK1:
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("1.mp3",true);
			break;
		case kEffectBK2:
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic("1.mp3",true);
			break;
		
	}
		
}