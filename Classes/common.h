#ifndef _COMMON_H_
#define _COMMON_H_
#include "cocos2d.h"
USING_NS_CC;

inline void ScaleToVisibleSize(CCSprite*& item)
{
	CCSize visbleSize = CCDirector::sharedDirector()->getVisibleSize();
	item->setScaleX(visbleSize.width / item->getContentSize().width);
	item->setScaleY(visbleSize.height / item->getContentSize().height);
}



#endif//_COMMON_H_
