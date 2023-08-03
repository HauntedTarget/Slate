#pragma once
#include <string>

namespace bls
{
	class Resource
	{
	public:
		virtual ~Resource() = default;

		virtual bool Create(std::string filename, ...) = 0;
	};
}