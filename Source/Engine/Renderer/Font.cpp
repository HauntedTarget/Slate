#include "Font.h"
#include <SDL2-2.28.0/include/SDL_ttf.h>
namespace bls
{
	Font::Font(const std::string& filename, int fontSize)
	{
		Load(filename, fontSize);
	}
	Font::~Font()
	{
		if (m_ttfFont) TTF_CloseFont(m_ttfFont);
		//<if m_ttfFont not null, close font(TTF_CloseFont)>
	}
	void Font::Load(const std::string& filename, int fontSize)
	{
		m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);
		/*<call TTF_OpenFont>
			<use filename.c_str() to get the c - style string>
			<assign the return value of TTF_OpenFont to m_ttfFont>*/
	}
}