#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

#include <iostream>
#include "cocos2d.h"
#include "SystemHeader.h"
//这里可以再私有变量中加一个函数指针，通过函数指针来调用不同函数，但是我不能正确赋值
USING_NS_CC;

using std::string;

class GameData
{
private:
	string order;
	//ValueVector(*func)(Value);

public:
	GameData(const char * _order);
	ValueVector toValueVector(Value value);
};

#endif