#ifndef _PROP_H_
#define _PROP_H_

#include "cocos2d.h"
USING_NS_CC;

class Prop : public CCNode
{
public:
	CREATE_FUNC(Prop);
	
	virtual bool init();

	virtual void update(float delta);
public:
	CCSprite*		m_prop;
	int				m_speed;
};

#endif//_PROP_H_
