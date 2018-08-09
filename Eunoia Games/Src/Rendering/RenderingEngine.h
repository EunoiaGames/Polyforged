#pragma once

#include "LoadedMesh.h"
#include "Shader.h"
#include "Material.h"
#include "../Core/ECS/Components/LightComponent.h"
#include "RenderContext.h"
#include "../Water/WaterTile.h"

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

		void SetCamera(const Math::Matrix4f& view, const Math::Matrix4f& projection, const Math::Vector3f& camPos);
	private:
		void RenderDrawCommands(Shader* pShader, bool lightShader);
	private:
		Shader* m_pAmbientShader;
		Shader* m_pDirectionalLightShader;;

		std::vector<DrawCommand> m_drawCommands;
		std::vector<DirectionalLight> m_directionalLights;

		Math::Matrix4f m_viewMatrix;
		Math::Matrix4f m_projectionMatrix;
		Math::Vector3f m_camPos;

		BlendState m_ambientBlendState;
		BlendState m_forwardBlendState;

		DepthStencilState m_ambientDepthStencilState;
		DepthStencilState m_forwardDepthStencilState;

		Math::Vector3f m_ambientColor;
	};

} }
