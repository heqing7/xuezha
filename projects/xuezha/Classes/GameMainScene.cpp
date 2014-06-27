#include "GameMainScene.h"
#include "Word.h"
#include "conv.h"
#include "GameOverScene.h"
#include "WelcomeScene.h"

static const char* g_orgPoem[] = 
{
	"早",
	"发",
	"白",
	"帝",
	"城",
	"李",
	"白",
    "朝",
    "辞",
    "白",
    "帝",
    "彩",
    "云",
    "间",
    "千",
    "里",
    "江",
    "陵",
    "一",
    "日",
    "还",
    "两",
    "岸",
    "猿",
    "声",
    "啼",
    "不",
    "住",
    "轻",
    "舟",
    "已",
    "过",
    "万",
    "重",
    "山",
};

static const char* g_errWords[] = 
{
    "撸",
    "呵",
    "哈",
    "啊",
    "咯",
    "撸",
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

        m_curWordIndex = 0;
        m_genCnt = 0;
        m_poem = NULL;

		CCLayerColor* pBGLayer = CCLayerColor::create(ccColor4B(ccc4(255,255,255,255)));
		CC_BREAK_IF(!pBGLayer);
		this->addChild(pBGLayer);

		m_hero = Hero::create();
		this->addChild(m_hero, 100);

// 		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
// 		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
// 		CCPoint orgPoint = CCDirector::sharedDirector()->getVisibleOrigin();
	
		//m_hero->setPosition(ccp(visibleSize.width / 2, m_hero->getSize().height / 2));

		m_poem = CCArray::createWithCapacity(100);
		m_poem->retain();
         
//         m_content = new WordSource();
//         m_content->initWiteFilePath();

        this->setKeypadEnabled(true);//监听android 按键

		srand(time(0));
		this->scheduleUpdate();
		return true;
	} while (0);
	return false;
}


void GameMainScene::onEnter()
{
	m_correctTimes = 0;
	m_errorTimes = 0;
}

void GameMainScene::onExit()
{
    CC_SAFE_RELEASE(m_poem);
    CCLayer::onExit();
}

void GameMainScene::keyBackClicked()
{
    CCDirector::sharedDirector()->setDepthTest(true);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, WelcomeScene::scene()));
}

//void GameMainScene::updateHeroPos()
//{
	//Todo
// 	if (m_hero->isLeft())
// 	{
// 		m_hero->setPosition(ccp(m_hero->getSize().width / 2, m_hero->getSize().height / 2));
// 	}
// 	else if(m_hero->isRight())
// 	{
// 		m_hero->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width - m_hero->getSize().width / 2, m_hero->getSize().height / 2));
// 	}
// 	else
// 	{
// 		m_hero->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width / 2, m_hero->getSize().height / 2));
// 	}
//}

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
				m_errorTimes++;
				word->miss();
				m_result.push_back(rst);
			}
			
			m_poem->removeObject(word);
		}
		else
		{
			CCPoint p1 = m_hero->getHeroPosition();
			CCSize s1 = m_hero->getHeroSize();
			CCSize s2 = word->getSize();
			if (isCollision(p1, p2, 40,35,18.25,17.75))
			{
				if (word->isEquilWord(base.c_str()))
				{
					m_correctTimes++;
                    m_hero->capture();
					rst = g_orgPoem[m_curWordIndex - 1];
					m_result.push_back(rst);
				}
                else
                {
					m_errorTimes++;
                    m_hero->hurt();
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
    if (m_hero->isDead())
    {
        return true;
    }
	return false;
}

void GameMainScene::autoNewWordObj()
{
	if ((m_genCnt++ % 50) != 0)
	{
		return;
	}
	
	do 
	{
        if (m_genCnt % 3 != 0)
        {
            CC_BREAK_IF(m_curWordIndex >= sizeof(g_orgPoem) / sizeof(char*));
            std::string word = g_orgPoem[m_curWordIndex++];
#ifdef _WIN32
            GBKToUTF(word);
#endif
            int track = (int)(3 * CCRANDOM_0_1());
            CCAssert(track < 3, "error number");
            CCSprite* pWord = Word::CreateWithTrack(track, word);
            CC_BREAK_IF(!pWord);
            m_poem->addObject(pWord);
            this->addChild(pWord, 90);
        }
        else
        {
            std::string word = g_errWords[m_curWordIndex % (sizeof(g_errWords) / sizeof(char*))];
#ifdef _WIN32
            GBKToUTF(word);
#endif
            int track = (int)(3 * CCRANDOM_0_1());
            CCAssert(track < 3, "error number");
            CCSprite* pWord = Word::CreateWithTrack(track, word);
            CC_BREAK_IF(!pWord);
            m_poem->addObject(pWord);
            this->addChild(pWord, 90);
        }

	} while (0);
}

void GameMainScene::autoNewProps()
{
	if (m_correctTimes % 7 == 0)
	{

	}
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
		1.更新hero位置
		2.检测hero与word是否碰撞，有则启动判定逻辑
		3.检测word是否超出界面底部
		4.生成后续word
		5.检测游戏是否结束
	*/
	checkCapturedAndMissed();
	autoNewWordObj();
	autoNewProps();
	if(checkGameOver())
	{
		//跳转结束场景
		int score = getScore();
		CCDirector::sharedDirector()->setDepthTest(true);  
        CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(1.0f, GameOverScene::sceneWithScore(score), true));
	}
}


