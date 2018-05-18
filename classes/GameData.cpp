#include "GameData.h"

GameData::GameData(const char * _order)
{
	order = _order;
}

ValueVector GameData::toValueVector(Value value)
{
	if (order == PLAYERNAME)
	{
		UserDefault* defaults = UserDefault::getInstance();
		std::pair<string, Value> pairname(PLAYERNAME, defaults->getStringForKey("playername"));

		cocos2d::ValueMap temp_map;
		temp_map.insert(pairname);

		Value val(temp_map);		//将map转化为Value
		cocos2d::ValueVector plistdata;
		plistdata.push_back(val);
		return plistdata;
	}
}