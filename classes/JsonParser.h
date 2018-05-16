#ifndef __JSON_Parser_SCENE_H__
#define __JSON_Parser_SCENE_H__

#include "cocos2d.h"

#include "document.h"
#include "writer.h"
#include  "reader.h"
#include "stringbuffer.h"

class JsonParser :public cocos2d::Ref
{
	//声明返回listdata数据
	CC_SYNTHESIZE(cocos2d::ValueVector, list, list);

private:
	cocos2d::ValueMap row;
	//JSON文件内容
	std::string content;
	
public:

	static JsonParser * createWithFile(const char * filename);
	bool initWithFile(const char * JSONName);

	void decode();
};

#endif 