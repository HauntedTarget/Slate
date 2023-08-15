#pragma once
#include "Math/Vector2.h"
#include <rapidjson/include/rapidjson/document.h>
#include <string>

#define READ_DATA(value, data) bls::Json::Read(value, #data, data);
#define READ_DATA_REQUIRED(value, data) bls::Json::Read(value, #data, data, true);

namespace bls
{
	class Json
	{
	public:
		static bool Load(const std::string& filename, rapidjson::Document& document);
		static bool Read(const rapidjson::Value& value, const std::string& name, int& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, float& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, bool& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, vec2& data, bool required = false);

	};
}