#include "FileIO.h"

namespace bls
{
	std::string bls::getFilePath()
	{
		return std::filesystem::current_path().string();
	}
}