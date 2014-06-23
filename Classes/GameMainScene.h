#ifndef _GAME_MAIN_SCENCE_H_
#define _GAME_MAIN_SCENCE_H_

#include "cocos2d.h"
#include "Hero.h"
#include <vector>
USING_NS_CC;

class GameMainScene : public CCLayer
{
public:
	CREATE_FUNC(GameMainScene);

	virtual GameMainScene::~GameMainScene()
	{
		if (m_poem)
		{
			CC_SAFE_RELEASE(m_poem);
		}
	}
	virtual bool init();

	static CCScene* scene();
	
	void update(float delta);

protected:

	void autoNewWordObj();
	void updateHeroPos();
	void checkCapturedAndMissed();
	bool checkGameOver();
	int getScore();


	bool isCollision(CCPoint& p1, CCPoint& p2, int w1, int h1, int w2, int h2)
	{
		if(abs(p1.x - p2.x) < w1 + w2 && abs(p1.y - p2.y) < h1 + h2)
		{
			return true;
		}
		return false;
	}
protected:
	Hero*						m_hero;

	CCArray*					m_poem;

	std::vector<std::string>	m_result;	

	int						m_curWordIndex;
	int						m_genCnt;
};

#endif//_GAME_MAIN_SCENCE_H_
