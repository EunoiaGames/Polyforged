#include "PolyforgedApplication.h"
#include "CoreEngine.h"
#include "../Rendering\Display.h"
#include "../Rendering\Mesh.h"
#include "../Rendering\Shader.h"
#include "ECS\Components\MeshComponent.h"
#include "ECS\Components\TransformComponent.h"
#include "ECS\Components\CameraComponent.h"
#include "ECS\Components\LookAroundComponent.h"
#include "ECS\Components\MovementComponent.h"
#include "ECS\Systems\RenderSystem.h"
#include "ECS\Systems\LookAroundSystem.h"
#include "ECS\Systems\MovementSystem.h"
#include "ECS\Systems\ViewProjectionSystem.h"
#include "../Rendering/ModelLoader.h"
#include "ECS\Components\LightComponent.h"

namespace Eunoia { namespace Core {

	void PolyforgedApplication::Init()
	{
		using namespace Eunoia;
		using namespace Rendering;
		using namespace Math;
		using namespace Core;
		using namespace Components;
		using namespace Systems;

		Vertex vertices[4] = { Vertex(Vector3f(-0.5f, 0.0f, -0.5f), Vector3f(0.0f, 0.25f, 0.0f)),
			Vertex(Vector3f(-0.5f, 0.0f, 0.5f), Vector3f(0.0f, 0.25f, 0.0f)),
			Vertex(Vector3f(0.5f, 0.0f, 0.5f), Vector3f(0.0f, 0.25f, 0.0f)),
			Vertex(Vector3f(0.5f, 0.2f, -0.5f), Vector3f(0.0f, 0.25f, 0.0f)) };

		uint32 indices[6] = { 0, 1, 2, 0, 2, 3 };

		Mesh* pMesh = Mesh::CreateMesh(vertices, 4, indices, 6, MESH_USAGE_STATIC);

		Entity* pQuad = new Entity();
		pQuad->AddComponent(new MeshComponent(pMesh));
		pQuad->AddComponent(new TransformComponent());
		pQuad->GetComponent<TransformComponent>()->transform.Scale(20.0f);

		Entity* pCamera = new Entity();
		pCamera->AddComponent(new TransformComponent());
		pCamera->AddComponent(new CameraComponent(70.0f));
		pCamera->AddComponent(new MovementComponent(100.0f));
		pCamera->AddComponent(new LookAroundComponent(3.0f, INPUT_KEY_ESC));

		Entity* pTree = new Entity();
		pTree->AddComponent(new TransformComponent());
		pTree->AddComponent(new MeshComponent(ModelLoader::LoadFromFile("Res/Models/knife.dae")));
		//pTree->GetComponent<TransformComponent>()->transform.Translate(Vector3f(0.0f, 1.1f, 0.0f));
		MeshComponent* pComp = pTree->GetComponent<MeshComponent>();

		AddSystem(new RenderSystem());
		AddSystem(new MovementSystem());
		AddSystem(new LookAroundSystem());
		AddSystem(new ViewProjectionSystem());

		//AddEntity(pQuad);
		AddEntity(pCamera);
		AddEntity(pTree);
	}

	void PolyforgedApplication::Shutdown()
	{

	}

} }
