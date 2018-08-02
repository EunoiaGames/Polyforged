#include "Rendering\Display.h"

int main()
{
	using namespace Eunoia;
	using namespace Rendering;

	Display* pDisplay = Display::CreateDisplay("Polyforged", 1280, 720, GraphicsAPI::GRAPHICS_API_OPENGL);

	RenderContext* pContext = RenderContext::GetRenderContext();
	pContext->SetDisplayAsRenderTarget();

	while (!pDisplay->ShouldClose())
	{
		pContext->Clear();

		pDisplay->Update();
		pContext->Swap();
	}
}