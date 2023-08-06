#pragma once
#include "Resource.h"
#include <map>
#include <memory>
#include <string>

namespace bls
{
	class ResouceManager
	{
	public:
		template<typename T, typename ... TArgs>
		shatr<T> Get(const std::string& filename, TArgs ... args);

	private:
		std::map<std::string, shatr<Resource>> m_resources;
	};

	template<typename T, typename ... TArgs>
	inline shatr<T> ResouceManager::Get(const std::string& filename, TArgs ... args)
	{
		if (m_resources.find(filename) != m_resources.end()) {
			return std::dynamic_pointer_cast<T>(m_resources[filename]);
		}

		shatr<T> resource = std::make_shared<T>();
		resource->Create(filename, args...);

		m_resources[filename] = resource;
		
		return resource;
	}

	extern ResouceManager g_resources;
}