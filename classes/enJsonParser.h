#ifndef __JSON_Parser_SCENE_H_
#define __JSON_Parser_SCENE_H_

#include "cocos2d.h"

#include "document.h"
#include "writer.h"
#include "reader.h"
#include "stringbuffer.h"

#include "Information.h"
//#include "MyUtility.h"

class enJsonParser :public cocos2d::Ref
{
private:
	cocos2d::ValueVector listData;
	std::string content;
public:

	static enJsonParser * createWithArray(cocos2d::ValueVector pListData);

	bool initWithArray(cocos2d::ValueVector pListData);

	void encode(Information information);
};

#endif