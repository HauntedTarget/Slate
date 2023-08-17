#include "Transform.h"

namespace bls{
	void Transform::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, position);
		READ_DATA(value, rotation);
		bls::Json::Read(value, "scale", scale);
	}
}
