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
		m_speed = 5;

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		float unitSize = visibleSize.width / 4 - 25;

		m_layerColorBG = CCLayerColor::create(cocos2d::ccColor4B(ccc4(180,170,160,255)),unitSize, unitSize);
		CC_BREAK_IF(!m_layerColorBG);
		m_labWord = CCLabelTTF::create(CCString::createWithFormat("%s", m_strWord.c_str())->getCString(), "ArialRoundedMTBold", unitSize - 15);
		CC_BREAK_IF(!m_labWord);
		m_labWord->setColor(ccc3(20, 20, 20));
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
		CCAssert(FALSE, "error not support!");
		return ccp(0, 0);
	}
}
