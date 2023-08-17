#include "Object.h"

namespace bls
{
	void Object::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, name);
	}
}