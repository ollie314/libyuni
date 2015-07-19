/*
** YUNI's default license is the GNU Lesser Public License (LGPL), with some
** exclusions (see below). This basically means that you can get the full source
** code for nothing, so long as you adhere to a few rules.
**
** Under the LGPL you may use YUNI for any purpose you wish, and modify it if you
** require, as long as you:
**
** Pass on the (modified) YUNI source code with your software, with original
** copyrights intact :
**  * If you distribute electronically, the source can be a separate download
**    (either from your own site if you modified YUNI, or to the official YUNI
**    website if you used an unmodified version) – just include a link in your
**    documentation
**  * If you distribute physical media, the YUNI source that you used to build
**    your application should be included on that media
** Make it clear where you have customised it.
**
** In addition to the LGPL license text, the following exceptions / clarifications
** to the LGPL conditions apply to YUNI:
**
**  * Making modifications to YUNI configuration files, build scripts and
**    configuration headers such as yuni/platform.h in order to create a
**    customised build setup of YUNI with the otherwise unmodified source code,
**    does not constitute a derived work
**  * Building against YUNI headers which have inlined code does not constitute a
**    derived work
**  * Code which subclasses YUNI classes outside of the YUNI libraries does not
**    form a derived work
**  * Statically linking the YUNI libraries into a user application does not make
**    the user application a derived work.
**  * Using source code obsfucation on the YUNI source code when distributing it
**    is not permitted.
** As per the terms of the LGPL, a "derived work" is one for which you have to
** distribute source code for, so when the clauses above define something as not
** a derived work, it means you don't have to distribute source code for it.
** However, the original YUNI source code with all modifications must always be
** made available.
*/
#include "splitter.h"
#include "../theme.h"
#include <cassert>

namespace Yuni
{
namespace UI
{
namespace Control
{


	void Splitter::draw(DrawingSurface::Ptr& surface, float xOffset, float yOffset) const
	{
		if (!pVisible)
			return;

		auto themeptr = Theme::Current();
		auto& theme = *themeptr;
		Point2D<float> pos(pPosition.x + xOffset, pPosition.y + yOffset);

		surface->beginRectangleClipping(pos.x, pos.y, pSize.x, pSize.y);
		// Draw the children
		drawChildren(surface, pos);

		// Draw the splitter line
		switch (pOrient)
		{
			case soVertical:
				surface->drawLine(theme.borderColor, pos.x + pSplitOffset, pos.y,
					pos.x + pSplitOffset, pos.y + pSize.y, theme.borderWidth);
				break;
			case soHorizontal:
				surface->drawLine(theme.borderColor, pos.x, pos.y + pSplitOffset,
					pos.x + pSize.x, pos.y + pSplitOffset, theme.borderWidth);
				break;
			default:
				assert(false && "UI::Control::Splitter : Invalid enum value for SplitOrientation");
				break;
		}

		surface->endClipping();
		pModified = false;
	}


	void Splitter::resizePanels()
	{
		switch (pOrient)
		{
			case soVertical:
				pChildren[0]->moveTo(0.0f, 0.0f);
				pChildren[0]->size(pSplitOffset, pSize.y);
				pChildren[1]->moveTo(pSplitOffset, 0.0f);
				pChildren[1]->size(pSize.x - pSplitOffset, pSize.y);
				break;
			case soHorizontal:
				pChildren[0]->moveTo(0.0f, 0.0f);
				pChildren[0]->size(pSize.x, pSplitOffset);
				pChildren[1]->moveTo(0.0f, pSplitOffset);
				pChildren[1]->size(pSize.x, pSize.y - pSplitOffset);
				break;
			default:
				assert(false && "UI::Control::Splitter : Invalid enum value for SplitOrientation");
				break;
		}
		if (pChildren[0]->modified() || pChildren[1]->modified())
			invalidate();
	}



} // namespace Control
} // namespace UI
} // namespace Yuni
