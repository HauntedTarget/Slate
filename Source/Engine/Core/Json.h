#pragma once
#include <rapidjson/include/rapidjson/document.h>
#include <string>

namespace bls
{
	class Json
	{
	public:
		static bool Load(const std::string& filename, rapidjson::Document& document);
		static bool Read(const rapidjson::Value& value, const std::string& name, int& data, bool required = false);

	};
}