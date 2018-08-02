#pragma once

#include "../../Core/DisplayInput.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Eunoia { namespace Core {

	class Win32Input : public DisplayInput
	{
	public:
		Win32Input(const HWND& handle);

		Math::Vector2f GetCursorPosition() const override;
		void SetCursorPosition(const Math::Vector2f& pos) const override;
		void SetCursorVisible(bool visible) const override;
		bool IsCursorVisible() const override;

	private:
		HWND m_handle;
		mutable bool m_isCursorVisible;
	};

} }
