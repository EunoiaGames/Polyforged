#include "Rendering\Display.h"
#include "Rendering\Mesh.h"

int main()
{
	using namespace Eunoia;
	using namespace Rendering;
	using namespace Math;

	Display* pDisplay = Display::CreateDisplay("Polyforged", 1280, 720, GRAPHICS_API_OPENGL);

	RenderContext* pContext = RenderContext::GetRenderContext();
	pContext->SetDisplayAsRenderTarget();

	Vertex vertices[4] = {Vertex(Vector3f(-0.5f, -0.5f, 0.0f)),
		Vertex(Vector3f(-0.5f, 0.5f, 0.0f)),
		Vertex(Vector3f(0.5f, 0.5f, 0.0f)),
		Vertex(Vector3f(0.5f, -0.5f, 0.0f)) };

	uint32 indices[6] = { 0, 1, 2, 0, 2, 3 };

	Mesh* pMesh = Mesh::CreateMesh(vertices, 4, indices, 6, MESH_USAGE_STATIC);

	while (!pDisplay->ShouldClose())
	{
		pContext->Clear();

		pMesh->Render();

		pDisplay->Update();
		pContext->Swap();
	}
}