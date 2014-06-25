#include "WelcomeScene.h"
#include "GameMainScene.h"
#include "common.h"

CCScene* WelcomeScene::scene()
{
    CCScene* scene = CCScene::create();
    do 
    {
        CC_BREAK_IF(!scene);
        WelcomeScene* layer = WelcomeScene::create();
        CC_BREAK_IF(!layer);
        scene->addChild(layer);
    } while (0);
    return scene;
}

bool WelcomeScene::init()
{
    do 
    {
        CC_BREAK_IF(!CCLayer::init());
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
        
        CCLabelTTF* pLabel = CCLabelTTF::create("Welcmoe", "Arial", 28);
        // position the label on the center of the screen
        pLabel->setColor(ccc3(0, 0, 0));
        pLabel->setPosition(ccp(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - pLabel->getContentSize().height - 60));

        // add the label as a child to this layer
        this->addChild(pLabel, 10);

        //add menu item
        CCMenuItemImage *pNewItem = CCMenuItemImage::create(
            "newgame.png",
            "newgame.png",
            this,
            menu_selector(WelcomeScene::menuNewCallback));

        pNewItem->setPosition(visibleSize.width / 2 + 50, visibleSize.height / 2 + 50);

        CCMenuItemImage *pExitItem = CCMenuItemImage::create(
            "exit.png",
            "exit.png",
            this,
            menu_selector(WelcomeScene::menuExitCallback));

        pExitItem->setPosition(visibleSize.width / 2 + 50, visibleSize.height / 2 - 30);

        CCMenu* pMenu = CCMenu::create(pNewItem, pExitItem, NULL);
        pMenu->setPosition(CCPointZero);
        this->addChild(pMenu, 1);

        // backgroud
        CCSprite* pSprite = CCSprite::create("welcome.jpg");
        pSprite->setPosition(ccp(0, 0));
        pSprite->setAnchorPoint(ccp(0, 0));
        ScaleToVisibleSize(pSprite);
        this->addChild(pSprite, 0);
        return true;
    } while (0);
    return false;
}

void WelcomeScene::menuNewCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->setDepthTest(true);
    CCDirector::sharedDirector()->replaceScene(CCTransitionPageTurn::create(0.5, GameMainScene::scene(), true));
}

void WelcomeScene::menuExitCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
}
