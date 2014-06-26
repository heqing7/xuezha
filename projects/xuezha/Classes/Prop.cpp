#include "Prop.h"

bool Prop::init()
{
	m_prop = CCSprite::create();

	m_prop->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width / 2, CCDirector::sharedDirector()->getVisibleSize().height));

	m_speed = 10;
	this->addChild(m_prop);
	this->scheduleUpdate();
}

void Prop::update(float delta)
{
	m_prop->setPosition(ccp(m_prop->getPositionX(), m_prop->getPositionY() - m_speed));
}

