#ifndef _GAME_OVER_SCENE_H_
#define _GAME_OVER_SCENE_H_
#include "cocos2d.h"
USING_NS_CC;


class GameOverScene : public CCLayer
{
public:
	//CREATE_FUNC(GameOverScene);
	static CCScene* sceneWithScore(int score);
	
	bool initWithScore(int score);

	void menuQuitCallback(CCObject* pSender);
	void menuAgainCallback(CCObject* pSender);
};
#endif//_GAME_OVER_SCENE_H_
