#include "PolyforgedApplication.h"
#include "CoreEngine.h"
#include "../Rendering\Display.h"
#include "../Rendering\Mesh.h"
#include "../Rendering\Shader.h"
#include "ECS\Components\MeshComponent.h"
#include "ECS\Components\MaterialComponent.h"
#include "ECS\Components\TransformComponent.h"
#include "ECS\Components\CameraComponent.h"
#include "ECS\Components\LookAroundComponent.h"
#include "ECS\Components\MovementComponent.h"
#include "ECS\Systems\RenderSystem.h"
#include "ECS\Systems\LookAroundSystem.h"
#include "ECS\Systems\MovementSystem.h"
#include "ECS\Systems\ViewProjectionSystem.h"

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
		pQuad->AddComponent(MeshComponent(pMesh));
		pQuad->AddComponent(MaterialComponent(Material()));
		pQuad->AddComponent(TransformComponent());
		pQuad->GetComponent<TransformComponent>()->transform.Rotate(Vector3f(0.0f, 0.0f, 1.0f), 45.0f);

		Entity* pCamera = new Entity();
		pCamera->AddComponent(TransformComponent());
		pCamera->AddComponent(CameraComponent(70.0f));
		pCamera->AddComponent(MovementComponent(0.1f));
		pCamera->AddComponent(LookAroundComponent(3.0f, INPUT_KEY_ESC));

		AddSystem(new RenderSystem());
		AddSystem(new MovementSystem());
		AddSystem(new LookAroundSystem());
		AddSystem(new ViewProjectionSystem());

		AddEntity(pQuad);
		AddEntity(pCamera);
	}

	void PolyforgedApplication::Shutdown()
	{

	}

} }
