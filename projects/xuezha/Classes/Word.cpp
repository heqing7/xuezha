#include "Word.h"


Word* Word::CreateWithTrack(int track, std::string& strWord)
{
	Word* pWord = new Word();
	if (pWord && pWord->init(track, strWord))
	{
		pWord->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pWord);
	}
	return pWord;
}

bool Word::init(int track, std::string& strWord)
{
	do 
	{
		CC_BREAK_IF(!CCSprite::init());

		m_track = track;
		m_strWord = strWord;
		m_speed = 4;

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		float unitSize = visibleSize.width / 4 - 25;

		m_layerColorBG = CCLayerColor::create(cocos2d::ccColor4B(ccc4(255,255,255,255)),unitSize, unitSize);
		CC_BREAK_IF(!m_layerColorBG);
		m_labWord = CCLabelTTF::create(CCString::createWithFormat("%s", m_strWord.c_str())->getCString(), "ArialRoundedMTBold", unitSize - 15);
		CC_BREAK_IF(!m_labWord);
		m_labWord->setColor(ccc3(0, 0, 0));
		m_labWord->setPosition(ccp(m_layerColorBG->getContentSize().width / 2, m_layerColorBG->getContentSize().height / 2));
		m_layerColorBG->addChild(m_labWord);

		m_layerColorBG->setPosition(getWordPosition(track));
		m_layerColorBG->setAnchorPoint(ccp(0.5f, 0.5f));
		this->addChild(m_layerColorBG);
		this->scheduleUpdate();
		return true;
	} while (0);
	return false;
}

void Word::update(float delta)
{
    if (m_layerColorBG->getPositionY() < CCDirector::sharedDirector()->getVisibleSize().height / 3 * 2)
    {
        m_speed = 8;
    }
    else if (m_layerColorBG->getPositionY() < CCDirector::sharedDirector()->getVisibleSize().height / 3)
    {
        m_speed = 10;
    }
    else if (m_layerColorBG->getPositionY() < CCDirector::sharedDirector()->getVisibleSize().height / 5)
    {
        m_speed = 14;
    }
	m_layerColorBG->setPosition(m_layerColorBG->getPositionX(), m_layerColorBG->getPositionY() - m_speed);
}

CCPoint Word::getWordPosition(int track)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	switch (track)
	{
	case TRACK_LEFT:
		//return ccp(m_layerColorBG->getContentSize().width / 2, visibleSize.height - m_layerColorBG->getContentSize().height / 2);
		return ccp(0, visibleSize.height - m_layerColorBG->getContentSize().height / 2);
		break;
	case TRACK_MID:
		return ccp(visibleSize.width / 2 - m_layerColorBG->getContentSize().width / 2, visibleSize.height - m_layerColorBG->getContentSize().height / 2);
	case TRACK_RIGHT:
		return ccp(visibleSize.width - m_layerColorBG->getContentSize().width, visibleSize.height - m_layerColorBG->getContentSize().height / 2);
	default:
		CCAssert(0, "error not support!");
		return ccp(0, 0);
	}
}

void Word::miss()
{
    CCSprite *explode = CCSprite::create("fuck.png");
    ccBlendFunc cb = { GL_SRC_ALPHA, GL_ONE };
    //explode->setBlendFunc(cb);
    CCSize size = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint pos;
    if (m_track == TRACK_LEFT)
    {
        pos = ccp(40, 40);
    }
    else if (m_track == TRACK_RIGHT)
    {
        pos = ccp(size.width - 40, 40);
    }
    else
    {
        pos = ccp(size.width / 2, 40);
    }
    explode->setPosition(pos);
    //explode->setRotation(CCRANDOM_0_1() * 360);
    explode->setScale(0.75);
    CCNode* parent = getParent();
    getParent()->addChild(explode, 99);

    CCCallFuncN *removeExplode = CCCallFuncN::create(explode, callfuncN_selector(Word::removeExplode));
    explode->runAction(CCScaleBy::create(0.3, 2, 2));
    explode->runAction(CCSequence::create(CCFadeOut::create(1), removeExplode, NULL));
}

void Word::removeExplode(CCNode *pSender)
{
    pSender->removeFromParent();
}

