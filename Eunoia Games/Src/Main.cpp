#include "Rendering\Display.h"
#include "Rendering\Mesh.h"
#include "Rendering\Shader.h"

int main()
{
	using namespace Eunoia;
	using namespace Rendering;
	using namespace Math;

	Display* pDisplay = Display::CreateDisplay("Polyforged", 1280, 720, GRAPHICS_API_D3D11);

	RenderContext* pContext = RenderContext::GetRenderContext();
	pContext->SetDisplayAsRenderTarget();

	Vertex vertices[4] = {Vertex(Vector3f(-0.5f, -0.5f, 0.0f), Vector3f(1.0f, 0.0f, 0.0f)),
		Vertex(Vector3f(-0.5f, 0.5f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f)),
		Vertex(Vector3f(0.5f, 0.5f, 0.0f), Vector3f(0.0f, 0.0f, 1.0f)),
		Vertex(Vector3f(0.5f, -0.5f, 0.0f), Vector3f(1.0f, 1.0f, 0.0f)) };

	uint32 indices[6] = { 0, 1, 2, 0, 2, 3 };

	Mesh* pMesh = Mesh::CreateMesh(vertices, 4, indices, 6, MESH_USAGE_STATIC);
	Shader* pShader = Shader::CreateShader("Test");
	pShader->Bind();

	while (!pDisplay->ShouldClose())
	{
		pContext->Clear();

		pMesh->Render();

		pDisplay->Update();
		pDisplay->GetInput()->Update();
		pContext->Swap();
	}
}