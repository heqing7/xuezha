#include "Hero.h"

bool Hero::init()
{
    m_hero = CCSprite::create("hero/xuezha0.png");
    if (m_hero)
    {
        return true;
    }
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

		CCAnimation* animation = CCAnimation::create();
		CC_BREAK_IF(!animation);
		animation->addSpriteFrameWithFileName("hero/xuezha0.png");
		animation->addSpriteFrameWithFileName("hero/xuezha1.png");
		animation->addSpriteFrameWithFileName("hero/xuezha2.png");
		animation->addSpriteFrameWithFileName("hero/xuezha3.png");
		animation->addSpriteFrameWithFileName("hero/xuezha4.png");
		animation->addSpriteFrameWithFileName("hero/xuezha5.png");
		animation->setDelayPerUnit(0.1f);
		//animation->setLoops(0);
		animation->setRestoreOriginalFrame(true);
		m_hero->runAction(CCRepeatForever::create(CCAnimate::create(animation)));

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

void Hero::hurt()
{
    CCSprite *explode = CCSprite::create("fuck.png");
    ccBlendFunc cb = { GL_SRC_ALPHA, GL_ONE };
    //explode->setBlendFunc(cb);
    explode->setPosition(ccp(getPositionX(), getPositionY()+ getSize().height / 2));
    //explode->setRotation(CCRANDOM_0_1() * 360);
    explode->setScale(0.75);
    CCNode* parent = getParent();
    getParent()->addChild(explode, 99);

    CCCallFuncN *removeExplode = CCCallFuncN::create(explode, callfuncN_selector(Hero::removeExplode));
    explode->runAction(CCScaleBy::create(0.3, 2, 2));
    explode->runAction(CCSequence::create(CCFadeOut::create(0.5), removeExplode, NULL));
}

void Hero::capture()
{
    CCSprite *explode = CCSprite::create("hehe.png");
    ccBlendFunc cb = { GL_SRC_ALPHA, GL_ONE };
    //explode->setBlendFunc(cb);
    explode->setPosition(ccp(getPositionX(), getPositionY() + getSize().height / 2));
    //explode->setRotation(CCRANDOM_0_1() * 360);
    explode->setScale(0.75);
    CCNode* parent = getParent();
    getParent()->addChild(explode, 99);

    CCCallFuncN *removeExplode = CCCallFuncN::create(explode, callfuncN_selector(Hero::removeExplode));
    explode->runAction(CCScaleBy::create(0.3, 2, 2));
    explode->runAction(CCSequence::create(CCFadeOut::create(0.5), removeExplode, NULL));
}

void Hero::removeExplode(CCNode *pSender)
{
    pSender->removeFromParent();
}
