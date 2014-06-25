#include "WordSource.h"
#include "conv.h"
using namespace std;

WordSource::WordSource()
{
    m_filepath = "res/word.txt";
}

WordSource::~WordSource()
{

}

bool WordSource::initWiteFilePath(const char* file)
{
    if (file && file != "")
    {
        m_filepath = file;
    }
    string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(m_filepath.c_str());
    
    unsigned char* pBuffer = NULL;
    unsigned long bufferSize = 0;

    pBuffer = CCFileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &bufferSize);
    if (pBuffer && bufferSize > 0)
    {
        for (unsigned i = 0; i < bufferSize; i += 2)
        {
            std::vector<string> words;
            string word = (char*)pBuffer;
             
            CCLOG(word.c_str());
            words.push_back(word);
        }
        CC_SAFE_DELETE_ARRAY(pBuffer);
        return true;
    }
    return false;
}