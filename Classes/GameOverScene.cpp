#include "GameOverScene.h"
#include "GameMainScene.h"
#include "common.h"
#include "conv.h"

CCScene* GameOverScene::sceneWithScore(int score)
{
	CCScene* scene;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(!scene);	
		GameOverScene* layer = new GameOverScene();
		if(layer && layer->initWithScore(score))
		{
			layer->autorelease();
			scene->addChild(layer);
		}
		else
		{
			CC_SAFE_DELETE(layer);
		}
	} while (0);
	return scene;
}

bool GameOverScene::initWithScore(int score)
{
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		//add menu item
		CCMenuItemImage *pQuitItem = CCMenuItemImage::create(
			"quit.png",
			"quit.png",
			this,
			menu_selector(GameOverScene::menuQuitCallback));

		CCMenuItemImage *pAgainItem = CCMenuItemImage::create(
			"again.png",
			"again.png",
			this,
			menu_selector(GameOverScene::menuAgainCallback));
		CC_BREAK_IF(!pQuitItem && !pAgainItem);

		pAgainItem->setPosition(origin.x + 100, origin.y + 30 + pAgainItem->getContentSize().height / 2);
		pQuitItem->setPosition(origin.x + visibleSize.width - 100, origin.y + 30 + pQuitItem->getContentSize().height / 2);

		CCMenu* pMenu = CCMenu::create(pAgainItem, pQuitItem, NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu, 1);

		//add score
		CCString* strScore = CCString::createWithFormat("才对了%d个字", score);
		CC_BREAK_IF(!score);
		std::string strValue = strScore->getCString();
#ifdef _WIN32
		GBKToUTF(strValue);
#endif//
		CCLabelTTF* pLabel = CCLabelTTF::create(strValue.c_str(), "HiraKakuProN-W6", 28);
		CC_BREAK_IF(!pLabel);
		pLabel->setColor(ccc3(0, 0, 0));
		pLabel->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height - 80));
		this->addChild(pLabel, 1);

		// backgroud
		CCSprite* pSprite = CCSprite::create("gameover.jpg");
		pSprite->setPosition(ccp(0, 0));
		pSprite->setAnchorPoint(ccp(0, 0));
		ScaleToVisibleSize(pSprite);
		this->addChild(pSprite, 0);
		return true;
	} while (0);
	return false;
}

void GameOverScene::menuAgainCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->setDepthTest(true);
	CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.5,GameMainScene::scene(), true));
}

void GameOverScene::menuQuitCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}
