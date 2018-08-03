#include "PolyforgedApplication.h"
#include "CoreEngine.h"
#include "../Rendering\Display.h"
#include "../Rendering\Mesh.h"
#include "../Rendering\Shader.h"
#include "ECS\Components\MeshComponent.h"
#include "ECS\Components\TransformComponent.h"
#include "ECS\Systems\RenderSystem.h"

namespace Eunoia { namespace Core {

	void PolyforgedApplication::Init()
	{
		using namespace Eunoia;
		using namespace Rendering;
		using namespace Math;
		using namespace Core;
		using namespace Components;
		using namespace Systems;

		Vertex vertices[4] = { Vertex(Vector3f(-0.5f, -0.5f, 0.0f), Vector3f(1.0f, 0.0f, 0.0f)),
			Vertex(Vector3f(-0.5f, 0.5f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f)),
			Vertex(Vector3f(0.5f, 0.5f, 0.0f), Vector3f(0.0f, 0.0f, 1.0f)),
			Vertex(Vector3f(0.5f, -0.5f, 0.0f), Vector3f(1.0f, 1.0f, 0.0f)) };

		uint32 indices[6] = { 0, 1, 2, 0, 2, 3 };

		Mesh* pMesh = Mesh::CreateMesh(vertices, 4, indices, 6, MESH_USAGE_STATIC);

		componentID id = MeshComponent::ID;

		Entity* pQuad = new Entity();
		pQuad->AddComponent(MeshComponent(MaterialMesh(pMesh)));
		pQuad->AddComponent(TransformComponent());

		AddSystem(new RenderSystem());
		AddEntity(pQuad);
	}

	void PolyforgedApplication::Shutdown()
	{

	}

} }
