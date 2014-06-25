#ifndef _WELCOME_SCENE_H_
#define _WELCOME_SCENE_H_
#include "cocos2d.h"
USING_NS_CC;

class WelcomeScene : public CCLayer
{
public:
    CREATE_FUNC(WelcomeScene);
    static CCScene* scene();
    virtual bool init();

    void menuNewCallback(CCObject* pSender);
    void menuExitCallback(CCObject* pSender);

};

#endif//_WELCOME_SCENE_H_
