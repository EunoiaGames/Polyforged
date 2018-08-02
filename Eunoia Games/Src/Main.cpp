#include "Rendering\Display.h"

int main()
{
	using namespace Eunoia;
	using namespace Rendering;

	Display* pDisplay = Display::CreateDisplay("Polyforged", 1280, 720, GRAPHICS_API_D3D11);

	RenderContext* pContext = RenderContext::GetRenderContext();
	pContext->SetDisplayAsRenderTarget();

	while (!pDisplay->ShouldClose())
	{
		pContext->Clear();

		pDisplay->Update();
		pContext->Swap();
	}
}