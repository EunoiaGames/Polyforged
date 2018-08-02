#pragma once

#include "../../Rendering/Display.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace Eunoia { namespace Rendering {

	class Win32Display : public Display
	{
	public:
		Win32Display(const String& title, uint16 width, uint16 height);

		bool InitDisplay(GraphicsAPI api) override;

		void Update() const override;
		
		uint16 GetWidth() const override;
		uint16 GetHeight() const override;
		//const String& GetTitle() const override;
		Core::DisplayInput* GetInput() const override;

		//void Resize(unsigned int width, unsigned int height) override;

		void UpdateWidthHeightVars(uint16 width, uint16 height);

		const HWND& GetWindowHandle() const;

		bool ShouldClose() const override;

		void SetClose();

	private:
		bool InitRawInputs();

		HWND m_windowHandle;

		String m_title;
		uint16 m_width;
		uint16 m_height;

		Core::DisplayInput* m_pInput;

		bool m_close;
	};

} }
