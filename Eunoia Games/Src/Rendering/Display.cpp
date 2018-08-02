#include "Display.h"
#include "../Platform/Windows/Win32Display.h"

namespace Eunoia { namespace Rendering {

	Display* Display::s_pDisplay = NULL;

	Display::Display()
	{
		s_pDisplay = this;
	}

	Display * Display::CreateDisplay(const String & title, uint16 width, uint16 height, GraphicsAPI api)
	{
#ifdef _WIN32
		Display* pDisplay = new Win32Display(title, width, height);
#endif

		bool success = pDisplay->InitDisplay(api);

		if (success)
			return pDisplay;
		else
			return NULL;
	}

	Display * Display::GetDisplay()
	{
		return s_pDisplay;
	}

}}
