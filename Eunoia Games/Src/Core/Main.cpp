#include "PolyforgedApplication.h"
#include "CoreEngine.h"

int main()
{
	Eunoia::Core::CoreEngine engine(new Eunoia::Core::PolyforgedApplication());
	engine.Init("Polyforged", 1920, 1080, Eunoia::Rendering::GRAPHICS_API_OPENGL);
	engine.Run();
}