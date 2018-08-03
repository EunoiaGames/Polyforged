#pragma once

#include "LoadedMesh.h"
#include "Shader.h"
#include "Material.h"
#include "../Core/ECS/Components/LightComponent.h"

#include <vector>

namespace Eunoia { namespace Rendering {

	struct DrawCommand
	{
		LoadedMesh mesh;
		Math::Matrix4f worldMatrix;
	};

	class RenderingEngine
	{
	public:
		RenderingEngine();
		~RenderingEngine();

		void Begin();
		void Submit(const DrawCommand& drawCommand);
		void End();
		void Draw();

		void SubmitDirectionalLight(const DirectionalLight& light);

		void SetViewProjection(const Math::Matrix4f& view, const Math::Matrix4f& projection);
	private:
		Shader* m_ambientShader;
		std::vector<DrawCommand> m_drawCommands;
		std::vector<DirectionalLight> m_directionalLights;

		Math::Matrix4f m_viewMatrix;
		Math::Matrix4f m_projectionMatrix;
	};

} }
