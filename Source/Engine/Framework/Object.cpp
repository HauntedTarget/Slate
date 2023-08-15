#include "Object.h"

namespace bls
{
	bool Object::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, name);

		return true;
	}
}