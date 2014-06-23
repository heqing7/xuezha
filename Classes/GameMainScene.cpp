#include "GameMainScene.h"
#include "Word.h"
#include "conv.h"
#include "GameOverScene.h"

static char* g_orgPoem[] = 
{
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"ǧ",
	"��",
	"��",
	"��",
	"һ",
	"��",
	"��",
	"��",
	"��",
	"Գ",
	"��",
	"��",
	"��",
	"ס",
	"��",
	"��",
	"��",
	"��",
	"��",
	"��",
	"ɽ",
};

CCScene* GameMainScene::scene()
{
	do 
	{
		CCLayer* pLayer = GameMainScene::create();
		CC_BREAK_IF(!pLayer);
		CCScene* pScene = CCScene::create();
		CC_BREAK_IF(!pScene);
		pScene->addChild(pLayer);
		return pScene;
	} while (0);
	return NULL;
}

bool GameMainScene::init()
{
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		CCLayerColor* pBGLayer = CCLayerColor::create(ccColor4B(ccc4(180,170,160,255)));
		CC_BREAK_IF(!pBGLayer);
		this->addChild(pBGLayer);

		m_hero = Hero::create();
		this->addChild(m_hero, 100);

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCPoint orgPoint = CCDirector::sharedDirector()->getVisibleOrigin();
	
		m_hero->setPosition(ccp(visibleSize.width / 2, m_hero->getSize().height / 2));

		m_curWordIndex = 0;
		m_genCnt = 0;

		m_poem = CCArray::createWithCapacity(100);
		m_poem->retain();

		srand(time(0));
		this->scheduleUpdate();
		return true;
	} while (0);
	return false;
}

void GameMainScene::updateHeroPos()
{
	if (m_hero->isLeft())
	{
		m_hero->setPosition(ccp(m_hero->getSize().width / 2, m_hero->getSize().height / 2));
	}
	else if(m_hero->isRight())
	{
		m_hero->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width - m_hero->getSize().width / 2, m_hero->getSize().height / 2));
	}
	else
	{
		m_hero->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width / 2, m_hero->getSize().height / 2));
	}
}

void GameMainScene::checkCapturedAndMissed()
{
	CCObject*	obj;;
	Word*		word;

	CCLOG("word count %d\n", m_poem->count());
	CCARRAY_FOREACH(m_poem, obj)
	{
		std::string rst = "";

		word = (Word*)obj;
		CCPoint p2 = word->getWordPosition();
		int need = m_result.size();
		std::string base = g_orgPoem[need];
#ifdef _WIN32
		GBKToUTF(base);
#endif//

		if (p2.y <= 0.0)
		{
			if (word->isEquilWord(base.c_str()))
			{
				//rst = "";
				m_result.push_back(rst);
			}
			m_poem->removeObject(word);
		}
		else
		{
			CCPoint p1 = m_hero->getPosition();
			CCSize s1 = m_hero->getSize();
			CCSize s2 = word->getSize();
			if (isCollision(p1, p2, 40,35,18.25,17.75))
			{
				if (word->isEquilWord(base.c_str()))
				{
					rst = g_orgPoem[m_curWordIndex - 1];
					m_result.push_back(rst);
				}
				word->setVisible(false);
				m_poem->removeObject(word);
			}
		}
	}
}


bool GameMainScene::checkGameOver()
{
	if (m_poem->count() == 0)
	{
		return true;
	}
	return false;
}

void GameMainScene::autoNewWordObj()
{
	if ((m_genCnt++ % 25) != 0)
	{
		return;
	}
	
	do 
	{
		CC_BREAK_IF(m_curWordIndex >= sizeof(g_orgPoem) / sizeof(char*));
		std::string word = g_orgPoem[m_curWordIndex++];
#ifdef _WIN32
		GBKToUTF(word);
#endif
		int track = (int)3 * CCRANDOM_0_1();
		CCAssert(track < 3, "error number");
		CCSprite* pWord = Word::CreateWithTrack(track, word);
		CC_BREAK_IF(!pWord);
		m_poem->addObject(pWord);
		this->addChild(pWord);

	} while (0);
}

int GameMainScene::getScore()
{
	int		score = 0;
	int		i = m_result.size() - 1;
	for (; i >= 0; i--)
	{
		if (m_result[i].compare("") != 0)
		{
			score++;
		}
	}
	CCLOG("score:%d", score);
	return score;
}

void GameMainScene::update(float delta)
{
	/*	
		1.����heroλ��
		2.���hero��word�Ƿ���ײ�����������ж��߼�
		3.���word�Ƿ񳬳�����ײ�
		4.���ɺ���word
		5.�����Ϸ�Ƿ����
	*/
	updateHeroPos();	
	checkCapturedAndMissed();
	autoNewWordObj();
	if(checkGameOver())
	{
		//��ת��������
		int score = getScore();
		CCDirector::sharedDirector()->setDepthTest(true);  
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5,GameOverScene::sceneWithScore(score)));
	}
}


