#pragma once
#include <string>
#include "Framework/Factory.h"
#include "Core/Json.h"

#define CLASS_DECLARE(classname) \
virtual const char* GetClassName() {return #classname;}\
virtual void Read(const rapidjson::Value& value);\
virtual std::unique_ptr<Object> Clone() { return std::make_unique<classname>(*this); }\
class Register {\
public:\
	Register()\
	{\
		Factory::Instance().Register<classname>(#classname);\
	}\
};

#define CLASS_DEFINE(classname) classname::Register regist;

namespace bls {

	class Object {

	public:
		Object() = default;
		Object(std::string name) :
			name {name} 
		{}
		virtual ~Object() { OnDestroy(); }

		CLASS_DECLARE(Object)

		virtual bool Initialize() { return true; }
		virtual void OnDestroy() {}

	public:
		std::string name;
		bool active = true;

	};

}