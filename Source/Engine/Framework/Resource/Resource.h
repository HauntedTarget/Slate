#pragma once
#include <string>
#include <memory>

namespace bls
{
	class Resource
	{
	public:
		virtual ~Resource() = default;

		virtual bool Create(std::string filename, ...) = 0;
	};

	template<typename T>
	using shatr = std::shared_ptr<T>;
}