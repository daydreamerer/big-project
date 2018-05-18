#ifndef __JSON_PARSER_SCENE_H_
#define __JSON_PARSER_SCENE_H_

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
	ValueVector listData;
	std::string content;
public:

	static enJsonParser * createWithArray(ValueVector pListData);

	bool initWithArray(ValueVector pListData);

	void encode(Information information);
};

#endif