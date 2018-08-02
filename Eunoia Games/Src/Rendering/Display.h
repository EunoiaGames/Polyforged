#pragma once

#include "../DataStructures/String.h"
#include "../Core/Common.h"
#include "RenderContext.h"
#include "../Core/DisplayInput.h"
#include "../Math/Math.h"

namespace Eunoia { namespace Rendering {

	class Display
	{
	public:
		Display();
		virtual ~Display() {}

		virtual bool InitDisplay(GraphicsAPI api) = 0;

		virtual void Update() const = 0;

		virtual bool ShouldClose() const = 0;

		virtual uint16 GetWidth() const = 0;
		virtual uint16 GetHeight() const = 0;

		inline Math::Vector2f GetSize() const { return Math::Vector2f(GetWidth(), GetHeight()); }

		virtual Core::DisplayInput* GetInput() const = 0;

		static Display* CreateDisplay(const String& title, uint16 width, uint16 height, GraphicsAPI api);
		static Display* GetDisplay();
	private:
		static Display* s_pDisplay;
	};

} }
