#ifndef _WORD_H_
#define _WORD_H_
#include "cocos2d.h"
#include <string>
USING_NS_CC;

class Word : public CCSprite
{
public:

	enum 
	{
		TRACK_LEFT = 0,
		TRACK_MID,
		TRACK_RIGHT,
	};

	static Word* CreateWithTrack(int track, std::string& strWord);
	
	void setTrack(int track)
	{
		m_track = track;
	}

	CCSize getSize()
	{
		return m_layerColorBG->getContentSize();
	}

	CCPoint getWordPosition()
	{
		return m_layerColorBG->getPosition();
	}
	
	bool isEquilWord(const char* word)
	{
		return (m_strWord.compare(word) == 0);
	}

	virtual void update(float delta);

protected:
	bool init(int track, std::string& strWord);
	CCPoint getWordPosition(int track);

protected:

	int					m_speed;
	int					m_track;

	std::string			m_strWord;
	CCLayerColor*		m_layerColorBG;
	CCLabelTTF*			m_labWord;
};
#endif//_WORD_H_
