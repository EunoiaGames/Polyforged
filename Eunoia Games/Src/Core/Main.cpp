#include "PolyforgedApplication.h"
#include "CoreEngine.h"

int main()
{
	Eunoia::Core::CoreEngine engine(new Eunoia::Core::PolyforgedApplication());
	engine.Init("Polyforged", 1280, 720, Eunoia::Rendering::GRAPHICS_API_D3D11);
	engine.Run();
}