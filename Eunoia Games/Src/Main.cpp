#include "Rendering\Display.h"

int main()
{
	using namespace Eunoia;
	using namespace Rendering;

	Display* pDisplay = Display::CreateDisplay("Poly Forged", 1280, 720, GraphicsAPI::GRAPHICS_API_OPENGL);

	RenderContext* pContext = RenderContext::GetRenderContext();
	pContext->SetDisplayAsRenderTarget();

	int i = 0;

	while (!pDisplay->ShouldClose())
	{
		pContext->Clear();

		pDisplay->Update();
		pContext->Swap();
	}
}