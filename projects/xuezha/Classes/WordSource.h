#ifndef _WORD_SOURCE_H_
#define _WORD_SOURCE_H_
#include "cocos2d.h"
#include <vector>
#include <string>
USING_NS_CC;

typedef std::vector<std::vector<std::string>> VEC_CONTENT;

class WordSource : public CCObject
{
public:

    WordSource();
    ~WordSource();

    bool initWiteFilePath(const char* file = "");

    void getContent(VEC_CONTENT* content)
    {
        content = &m_content;
    }


public:

    VEC_CONTENT       m_content;
    std::string       m_filepath;
};

#endif//_WORD_SOURCE_H_
