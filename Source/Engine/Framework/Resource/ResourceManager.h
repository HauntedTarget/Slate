#pragma once
#include "Resource.h"
#include "Framework/Singleton.h"
#include <map>
#include <memory>
#include <string>

#define GET_RESOURCE(type, filename, ...) bls::ResourceManager::Instance().Get<type>(filename, __VA_ARGS__);

namespace bls
{
	class ResourceManager : public Singleton<ResourceManager>
	{
	public:
		template<typename T, typename ... TArgs>
		shatr<T> Get(const std::string& filename, TArgs ... args);

	private:
		std::map<std::string, shatr<Resource>> m_resources;
	};

	template<typename T, typename ... TArgs>
	inline shatr<T> ResourceManager::Get(const std::string& filename, TArgs ... args)
	{
		if (m_resources.find(filename) != m_resources.end()) {
			return std::dynamic_pointer_cast<T>(m_resources[filename]);
		}

		shatr<T> resource = std::make_shared<T>();
		resource->Create(filename, args...);

		m_resources[filename] = resource;
		
		return resource;
	}

	extern ResourceManager g_resources;
}