#include "Hero.h"

bool Hero::init()
{
	do 
	{
		//hero
		m_hero = CCSprite::create("hero/xuezha0.png");
		CC_BREAK_IF(!m_hero);

		//blood;
		m_bloodBar = CCProgressTimer::create(CCSprite::create("blood_right.png"));

		CC_BREAK_IF(!m_bloodBar);
		m_bloodBar->setType(kCCProgressTimerTypeBar);
		m_bloodBar->setMidpoint(ccp(0, 0));
		m_bloodBar->setBarChangeRate(ccp(1, 0));
		m_bloodBar->setAnchorPoint(ccp(0, 0));
		m_bloodBar->setPercentage(100.0f);

		m_bloodSprite = CCSprite::create("blood_left.png");
		m_bloodSprite->addChild(m_bloodBar, 2);
		addChild(m_bloodSprite, 10);
		m_bloodSprite->setPosition(ccp(0, m_hero->getContentSize().height - 40));
		m_blood = m_bloodBar->getPercentage();
		return true;
	} while (0);

    return false;
}

void Hero::touchDelegateRelease()
{
	this->release();
}

void Hero::touchDelegateRetain()
{
	this->retain();
}

void Hero::onEnter()
{
	CCNode::onEnter();

	do 
	{
		CCDirector* pDirector = CCDirector::sharedDirector();
		CC_BREAK_IF(!pDirector);
		pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0 ,true);
		
		CC_BREAK_IF(!m_hero);

		CCSprite * obj = CCSprite::create("hero/cao.jpg");
		CC_BREAK_IF(!obj);
		m_error = obj->getTexture();
		obj = CCSprite::create("hero/hehe.jpg");
		m_correct = obj->getTexture();

		setStatus(STATUS_NORMAL);
		
		addChild(m_hero);
	} while (0);
	
}

void Hero::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCNode::onExit();
}

bool Hero::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	touchStartP = touch->getLocation();
	return true;
}

void Hero::ccTouchMoved(CCTouch* touch, CCEvent* event)
{

}

void Hero::ccTouchEnded(CCTouch* touch, CCEvent* event)
{

	CCPoint touchEndP = touch->getLocation();

	double d = distance(touchStartP,touchEndP);
	CCLOG("两点的距离 ：%f",d );
	//如果触摸距离超过20判断手势方向
	if (d > 20)
	{
		if (touchStartP.x-touchEndP.x<0&&touchStartP.x-touchEndP.x<touchStartP.y-touchEndP.y&&touchEndP.x-touchStartP.x>touchStartP.y-touchEndP.y)
		{
			//CCLOG("右");
			moveTo(DERICTION_RIGHT);
		}
		if (touchStartP.x-touchEndP.x>0&&touchStartP.x-touchEndP.x>touchStartP.y-touchEndP.y&&touchEndP.x-touchStartP.x<touchStartP.y-touchEndP.y)
		{
			//CCLOG("左");
			moveTo(DERICTION_LEFT);
		}

		if (touchStartP.y-touchEndP.y<0&&touchStartP.y-touchEndP.y<touchStartP.x-touchEndP.x&&touchEndP.y-touchStartP.y>touchStartP.x-touchEndP.x)
		{
			//CCLOG("上");
		}
		if (touchStartP.y-touchEndP.y>0&&touchStartP.y-touchEndP.y>touchStartP.x-touchEndP.x&&touchEndP.y-touchStartP.y<touchStartP.x-touchEndP.x) 
		{
			//CCLOG("下");
		}
	}
}

void Hero::updateBloodBar()
{
// 	if (isLeft())
// 	{
// 		m_bloodSprite->setPosition(ccp(m_hero->getContentSize().width / 2, m_hero->getContentSize().height));
// 	}
// 	else if(isRight())
// 	{
// 		m_bloodSprite->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width - m_hero->getContentSize().width / 2, m_hero->getContentSize().height));
// 	}
// 	else
// 	{
// 		m_bloodSprite->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width / 2, m_hero->getContentSize().height));
// 	}

	float progressFrom = m_bloodBar->getPercentage();
	CCProgressFromTo *to2 = CCProgressFromTo::create(0.2f, progressFrom, m_blood);
	m_bloodBar->runAction(to2);
}

void Hero::hurt()
{

	setStatus(STATUS_ERROR);
    CCSprite *explode = CCSprite::create("fuck.png");
    ccBlendFunc cb = { GL_SRC_ALPHA, GL_ONE };
    //explode->setBlendFunc(cb);
    explode->setPosition(ccp(getPositionX(), getPositionY()+ getSize().height / 2 + 30));
    //explode->setRotation(CCRANDOM_0_1() * 360);
    explode->setScale(0.75f);
    CCNode* parent = getParent();
    getParent()->addChild(explode, 99);

    CCCallFuncN *removeExplode = CCCallFuncN::create(explode, callfuncN_selector(Hero::removeExplode));
    explode->runAction(CCScaleBy::create(0.3f, 2, 2));
    explode->runAction(CCSequence::create(CCFadeOut::create(0.5f), removeExplode, NULL));
	
	//
	if (m_blood)
	{
		m_blood -= 20.0f;//
	}
	updateBloodBar();

}

void Hero::capture()
{
	setStatus(STATUS_CORRECT);
    CCSprite *explode = CCSprite::create("hehe.png");
    ccBlendFunc cb = { GL_SRC_ALPHA, GL_ONE };
    //explode->setBlendFunc(cb);
    explode->setPosition(ccp(getPositionX(), getPositionY() + getSize().height / 2 + 30));
    //explode->setRotation(CCRANDOM_0_1() * 360);
    explode->setScale(0.75);
    CCNode* parent = getParent();
    getParent()->addChild(explode, 99);

    CCCallFuncN *removeExplode = CCCallFuncN::create(explode, callfuncN_selector(Hero::removeExplode));
    explode->runAction(CCScaleBy::create(0.3f, 2, 2));
    explode->runAction(CCSequence::create(CCFadeOut::create(0.5f), removeExplode, NULL));
}

void Hero::removeExplode(CCNode *pSender)
{
    pSender->removeFromParent();
}

void Hero::setStatus(int status)
{
	if (m_status == status)
	{
		return;
	}
	m_status = status;
	m_hero->stopAllActions();
	if (status == STATUS_ERROR)
	{
		stopAllActions();
		m_hero->setTexture(m_error);
		runAction(CCSequence::create(CCJumpBy::create(0.5,ccp(0,0),0,1),CCCallFuncN::create(this, callfuncN_selector(Hero::statusEnd)),NULL));
	}
	else if(status ==STATUS_CORRECT)
	{
		stopAllActions();
		m_hero->setTexture(m_correct);
		runAction(CCSequence::create(CCJumpBy::create(0.5,ccp(0,0),0,1),CCCallFuncN::create(this, callfuncN_selector(Hero::statusEnd)),NULL));
	}
	else
	{
		CCAnimation* animation = CCAnimation::create();
		animation->addSpriteFrameWithFileName("hero/xuezha0.png");
		animation->addSpriteFrameWithFileName("hero/xuezha1.png");
		animation->addSpriteFrameWithFileName("hero/xuezha2.png");
		animation->addSpriteFrameWithFileName("hero/xuezha3.png");
		animation->addSpriteFrameWithFileName("hero/xuezha4.png");
		animation->addSpriteFrameWithFileName("hero/xuezha5.png");
		animation->setDelayPerUnit(0.1f);
		animation->setRestoreOriginalFrame(true);
		m_hero->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
	}
}

void Hero::statusEnd(CCNode * node)
{
	setStatus(STATUS_NORMAL);
}
