#pragma once

#include "Common.h"
#include <json/json.h>

class JsonModule
{
public:
	JsonModule();
	~JsonModule();

	JsonModule(const JsonModule& other) = delete;
	JsonModule(JsonModule&& other) = delete;

	JsonModule& operator=(const JsonModule& other) = delete;
	JsonModule& operator=(JsonModule&& other) = delete;

	Json::Value ParseString(std::string str);
};