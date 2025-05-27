#include "JsonModule.h"

JsonModule::JsonModule()
{
}

JsonModule::~JsonModule()
{
}

Json::Value JsonModule::ParseString(std::string str)
{
	std::cout << str << std::endl;

	Json::Reader reader;
	Json::Value data;
	bool bisSuccessful = reader.parse(str, data);

	if (!bisSuccessful)
	{
		std::cout << "Failed to parse JSON string: " << reader.getFormattedErrorMessages() << std::endl;
		return Json::Value();
	}

	return data;
}
