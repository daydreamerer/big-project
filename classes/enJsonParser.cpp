#include "enJsonParser.h"
USING_NS_CC;
enJsonParser * enJsonParser::createWithArray(ValueVector pListData)
{
	enJsonParser * pRef = new enJsonParser();

	if (pRef->initWithArray(pListData))
	{
		pRef->autorelease();
		return pRef;
	}
	CC_SAFE_DELETE(pRef);
	return nullptr;
}

bool enJsonParser::initWithArray(ValueVector pListData)
{
	listData = pListData;
	return true;
}

void enJsonParser::encode(Information information)
{
	rapidjson::Document document;
	document.SetObject();		//初始化document
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();		//获得内存分配器，包括了分配和销毁内存的方法

	rapidjson::Value array(rapidjson::kArrayType);

	for (auto& v : listData)
	{
		ValueMap row = v.asValueMap();				//这里的v就是字典，Value是一种包装类，可以把很多数据类型包装成类

		rapidjson::Value object(rapidjson::kObjectType);

		rapidjson::Value v_id;
		v_id.SetString(row["ID"].asString().c_str(), allocator);
		object.AddMember("ID", v_id, allocator);

		rapidjson::Value v_Date;
		v_Date.SetString(row["Date"].asString().c_str(), allocator);
		object.AddMember("Date", v_Date, allocator);

		rapidjson::Value v_Content;
		v_Content.SetString(row["Content"].asString().c_str(), allocator);
		object.AddMember("Content", v_Content, allocator);

		rapidjson::Value v_UserID;
		v_UserID.SetString(row["UserID"].asString().c_str(), allocator);
		object.AddMember("UserID", v_UserID, allocator);

		array.PushBack(object, allocator);
	}

	//document.AddMember("change", true, allocator);
	document.AddMember("Record", array, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer < rapidjson:: StringBuffer > writer(buffer);	//声明writer对象，将数据保存到buffer里

	document.Accept(writer);	//通过write将数据写入buffer
	
	information.getSendBuf() = buffer.GetString();

	//log("out: %s", out);
}