#ifndef _PersonalAudioEngine_
#define _PersonalAudioEngine_
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
typedef enum{
	//kEffectSwichCannon = 0,
	kEffectShoot = 0,
	kEffectButton,
	kEffectCoins,
	kEffectPause,
	kEffectFishNet,
	kEffectSwitchCannon,
	kEffectBK,
	kEffectBK1,
	kEffectBK2
	
}EffectType;

class PersonalAudioEngine : public CocosDenshion::SimpleAudioEngine
{
public:
	static PersonalAudioEngine* sharedEngine();
    void setBackgroundMusicVolume(float volume);
    void setEffectsVolume(float volume);
	
    void playBackgroundMusic(int type);
	void playEffect(EffectType  type);
protected:
	void purge();
    bool init();
    PersonalAudioEngine();
    ~PersonalAudioEngine();
	PersonalAudioEngine(const PersonalAudioEngine& engin);
	static PersonalAudioEngine *s_sharedEngine;
};

#endif 
