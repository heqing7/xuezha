#ifndef _HERO_H_
#define _HERO_H_
#include "cocos2d.h"
#include <cmath>
USING_NS_CC;

class Hero : public CCNode, public CCTargetedTouchDelegate
{
public:

	enum 
	{
		DERICTION_LEFT = 0,
		DERICTION_RIGHT,
	};

	enum
	{
		LOCATION_LEFT = 0,
		LOCATION_MID,
		LOCATION_RIGHT,
	};

	enum 
	{
		STATUS_NORMAL = 0,
		STATUS_CAPTURE,
		STATUS_OVER,
	};
public:
	CREATE_FUNC(Hero);
// 	virtual bool init();
	Hero()
	{
		m_curLocation = LOCATION_MID;
	}

	virtual ~Hero()
	{

	}

    virtual bool init();

	void setStatus(int status)
	{
		
	}

	void moveTo(int direction)
	{
		switch (direction)
		{
		case DERICTION_LEFT:
			{
				if (m_curLocation != LOCATION_LEFT)
				{
					m_curLocation--;
				}
			}
			break;
		case DERICTION_RIGHT:
			{
				if (m_curLocation != LOCATION_RIGHT)
				{
					m_curLocation++;
				}
			}
			break;
		default:
			break;
		}
	}

	CCSize getSize()
	{
		return m_hero->getContentSize();
	}

	bool isLeft()
	{
		return m_curLocation == LOCATION_LEFT;
	}

	bool isMiddle()
	{
		return m_curLocation == LOCATION_MID;
	}

	bool isRight()
	{
		return m_curLocation == LOCATION_RIGHT;
	}

    void hurt();

    void removeExplode(CCNode *pSender);

protected:	

	//CCRect rect();
	virtual void onEnter();
	virtual void onExit();
	bool containsTouchLocation(CCTouch* touch);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

	virtual void touchDelegateRetain();
	virtual void touchDelegateRelease();


	float distance(CCPoint pt1, CCPoint pt2)
	{
		return (float)(sqrt((pt1.x-pt2.x)*(pt1.x-pt2.x)+(pt1.y-pt2.y)*(pt1.y-pt2.y)));
	}


protected:

	int				m_status;
	int				m_curLocation;
	CCSprite*		m_hero;

	CCPoint			touchStartP;
};


#endif//_HERO_H_
